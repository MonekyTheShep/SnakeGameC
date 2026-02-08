#include <stdio.h>
#include <pthread.h>

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "utility/menuutil.h"
#include "utility/gameutil.h"
#include "utility/soundutil.h"

#include "states/game.h"
#include "states/menu.h"

#include "linkedlist.h"
#include "snake.h"
#include "apple.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MOVE_INTERVAL 50

// default menu
MenuStates menuState = MAIN_MENU;

GameInfo gameInfo = {MOVE_INTERVAL, 0};

int gameOver = 0;
int score = 0;

int verboseMode = 0;

void resetGame(LinkedList *snake, const SnakeData *data, GameInfo *info)
{
    // reset snake by freeing and creating new snake
    *snake = clearList(snake);
    *snake = createSnake();

    *data->direction = RIGHT;
    score = 0;
    gameOver = 0;
    changeMenu(info, &menuState, MAIN_MENU);
}

int main(void)
{
    // Initialise SNAKE shit
    LinkedList snake = createSnake();
    enum Direction direction = RIGHT;

    // seed random
    srand(time(NULL));
    SnakeData data = {&direction};

    // Initialise Raylib shit
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake Game");
    InitAudioDevice();

    const int maxSize = (GetScreenWidth()/ (int)gameInfo.moveInterval) * (GetScreenHeight() / (int)gameInfo.moveInterval);
    const int maxSnakeSize = (score + 1 == maxSize);

    // load sounds
    Sound collectSound = LoadSound(ASSETS_PATH "/sounds/collect_sound.ogg");
    Sound explosionSound = LoadSound(ASSETS_PATH "/sounds/explosion_sound.ogg");

    Sound sounds[2];
    sounds[0] = collectSound;
    sounds[1] = explosionSound;

    // load musics
    Music mainMenuSound = LoadMusicStream(ASSETS_PATH "/music/main_menu.ogg");
    Music gameMusicSound = LoadMusicStream(ASSETS_PATH "/music/game_music.ogg");

    Music musics[2];
    musics[0] = mainMenuSound;
    musics[1] = gameMusicSound;

    Music *currentMusic = &mainMenuSound;
    PlayMusicStream(*currentMusic);
    gameInfo.musicPlaying = 1;

    SetTargetFPS(60);

    Rectangle snakeHead = {0, 0, gameInfo.moveInterval, gameInfo.moveInterval}; // x, y, width, height
    RandomPos applePos = moveApple(&snake, (int)gameInfo.moveInterval);
    Rectangle apple = {(float)applePos.x, (float)applePos.y, gameInfo.moveInterval, gameInfo.moveInterval}; // x, y, width, height

    float accumulatedTime = 0.0f; // Total elapsed time
    float accumulatedDebounceTime = 0.0f;
    const float moveTimeInterval = 0.1f;

    while (!WindowShouldClose())
    {

        if (menuState == EXIT_MENU) {
            break;
        }

        UpdateMusicStream(*currentMusic);

        // move all logic outside of draw code

        // music management
        if (!gameInfo.musicPlaying)
            switch (menuState)
            {
            case MAIN_MENU:
                gameInfo.musicPlaying = 1;
                StopMusicStream(*currentMusic);
                currentMusic = &mainMenuSound;
                PlayMusicStream(*currentMusic);
                break;
            case GAME_MENU:
                gameInfo.musicPlaying = 1;
                StopMusicStream(*currentMusic);
                currentMusic = &gameMusicSound;
                PlayMusicStream(*currentMusic);
                break;

            default: break;
            }


        switch (menuState) {
            case MAIN_MENU:
                updateMainMenu(&gameInfo, &menuState);
                break;
            case GAME_MENU:

            default:
                break;
        }

        if (menuState == GAME_MENU)
        {
            float deltaTime = GetFrameTime(); // Time since last frame
            accumulatedTime += deltaTime;     // Add to total
            accumulatedDebounceTime += deltaTime;

            if (maxSnakeSize)
            {
                gameOver = 1;
            }

            // input checking
            if (accumulatedDebounceTime > moveTimeInterval && !gameOver)
            {
                accumulatedDebounceTime = 0.0f;
                if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && direction != LEFT)
                    direction = RIGHT;
                else if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && direction != RIGHT)
                    direction = LEFT;
                else if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && direction != UP)
                    direction = DOWN;
                else if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && direction != DOWN)
                    direction = UP;
            }


            // store prev position then move the snake position x and y
            int beenTimeInterval = accumulatedTime > moveTimeInterval;
            if (beenTimeInterval && !gameOver)
            {
                accumulatedTime = 0.0f;
                storePrevSnakePosition(&snake);
                moveSnake(&snake, &data, gameInfo);

                if (verboseMode)
                {
                    printLinkedList(&snake);
                    printf("%d\n", sizeOfLinkedList(&snake));
                    printf("%d\n", gameOver);
                }
            }

            // move the head
            snakeHead.x = snake.head->snake_node.x;
            snakeHead.y = snake.head->snake_node.y;

            // if the apple is overlapping head.
            const int appleOverlapSnakeX = snake.head->snake_node.x == apple.x;
            const int appleOverlapSnakeY = snake.head->snake_node.y == apple.y;

            if (appleOverlapSnakeX && appleOverlapSnakeY && !gameOver)
            {
                PlaySound(collectSound);
                score += 1;
                growSnake(&snake);

                // new apple pos
                applePos = moveApple(&snake, (int)gameInfo.moveInterval);

                // move the apple
                apple.x = (float)applePos.x;
                apple.y = (float)applePos.y;

            }

            BeginDrawing();
            ClearBackground(RAYWHITE);

            // prev pos stored after the head position
            Node *temp = snake.head->next;
            int length = 0;

            // move tail to previous positions and check if those tails are touching head
            while (temp != NULL)
            {
                length++;

                Rectangle tail = {(float)temp->snake_node.x, (float)temp->snake_node.y, gameInfo.moveInterval, gameInfo.moveInterval};
                DrawRectangleRec(tail, GREEN);

                const int tailOverlapHeadX = temp->snake_node.x == snake.head->snake_node.x;
                const int tailOverlapHeadY = temp->snake_node.y == snake.head->snake_node.y;
                const int hasTails = length > 1;
                // it has to be longer than 1

                // if tail overlaps head then it should game over and play death sound
                if (tailOverlapHeadX && tailOverlapHeadY && hasTails && !gameOver)
                {
                    gameOver = 1;
                    PlaySound(explosionSound);
                    break;
                }

                temp = temp->next;
            }

            DrawRectangleRec(apple, RED);
            DrawRectangleRec(snakeHead, DARKGREEN);

            DrawText(TextFormat("Score: %0i", score), 0, 0, 50, BLACK);

            if (gameOver)
            {
                const float buttonWidth = 100;
                const float buttonHeight = 50;
                const float gameOverButtonX = ((float) GetScreenWidth() - buttonWidth) / 2;
                const float gameOverButtonY = ((float) GetScreenHeight() - buttonHeight) / 2;
                const Rectangle gameOverButton = {gameOverButtonX,gameOverButtonY,buttonWidth,buttonHeight};

                if (GuiButton(gameOverButton, "Reset"))
                {
                    resetGame(&snake, &data, &gameInfo);
                    applePos = moveApple(&snake, (int)gameInfo.moveInterval);
                    apple.x = (float)applePos.x;
                    apple.y = (float)applePos.y;
                }
            }

            EndDrawing();

        }
    }


    const int numOfSound = sizeof(sounds) / sizeof(sounds[0]);
    cleanUpSound(sounds, numOfSound);

    const int numOfMusic = sizeof(musics) / sizeof(musics[0]);
    cleanUpMusic(musics, numOfMusic);

    CloseAudioDevice();
    CloseWindow();

    freeLinkedList(&snake);
    return 0;
}
