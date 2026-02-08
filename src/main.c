#include <stdio.h>
#include <pthread.h>

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "gameutil.h"

#include "linkedlist.h"
#include "snake.h"
#include "apple.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MOVE_INTERVAL 50


enum MenuStates
{
    MAIN_MENU,
    GAME_MENU,
    EXIT_STATE
};

void changeMenu(GameInfo *info, enum MenuStates *menuState, const enum MenuStates changeState)
{
    *menuState = changeState;
    info->musicPlaying = 0;
}

// default menu
enum MenuStates menuState = MAIN_MENU;

int gameOver = 0;
int score = 0;

int verboseMode = 0;

void resetGame(LinkedList *snake, SnakeData *data, GameInfo *info)
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
    GameInfo gameInfo = {SCREEN_WIDTH, SCREEN_HEIGHT, MOVE_INTERVAL, 0};

    // Initialise SNAKE shit
    LinkedList snake = createSnake();
    enum Direction direction = RIGHT;

    // seed random
    srand(time(NULL));
    SnakeData data = {&direction};

    const int maxSize = (gameInfo.screenHeight / (int)gameInfo.moveInterval) * (gameInfo.screenWidth / (int)gameInfo.moveInterval);
    const int maxSnakeSize = (score + 1 == maxSize);

    // Initialise Raylib shit
    InitWindow(gameInfo.screenWidth, gameInfo.screenHeight, "Snake Game");
    InitAudioDevice();

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
    RandomPos applePos = moveApple(&snake, GetScreenWidth(), GetScreenHeight(), (int)gameInfo.moveInterval);
    Rectangle apple = {(float)applePos.x, (float)applePos.y, gameInfo.moveInterval, gameInfo.moveInterval}; // x, y, width, height

    float accumulatedTime = 0.0f; // Total elapsed time
    float accumulatedDebounceTime = 0.0f;
    const float moveTimeInterval = 0.1f;

    while (!WindowShouldClose())
    {
        UpdateMusicStream(*currentMusic);

        BeginDrawing();
        ClearBackground(RAYWHITE);

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
            }

        if (menuState == MAIN_MENU)
        {
            // Draw the title
            const char titleText[11] = "Snake Game";

            const Font font = GetFontDefault();
            const float fontSize = 50;

            const Vector2 size = MeasureTextEx(font, titleText, fontSize, 0);

            const float textXCenter = ((float)GetScreenWidth() - size.x) / 2;
            const float textYCenter = ((float)GetScreenHeight() - size.y) / 2;
            const float offsetY = -50;

            DrawTextEx(font, TextFormat(titleText, score), (Vector2){textXCenter, textYCenter + offsetY}, fontSize, 1, BLACK);


            // Draw the buttons
            const char *buttonLabels[] = {"Start", "End", "Test"};
            const int numButtons = sizeof(buttonLabels) / sizeof(buttonLabels[0]);

            // Button information
            const float buttonWidth = 100;
            const float buttonHeight = 50;
            const float buttonGap = 10;

            // Calculate button position
            const float buttonCenterX = (SCREEN_WIDTH - buttonWidth) / 2;
            const float buttonCenterY = (SCREEN_HEIGHT - buttonHeight) / 2;

            // Create buttons
            for (int i = 0; i < numButtons; i++) {
                // calculate where button is placed
                float buttonOffset = (float) i * (buttonHeight + buttonGap);

                float currentButtonX = buttonCenterX;
                float currentButtonY = buttonCenterY + buttonOffset;

                Rectangle button = { currentButtonX, currentButtonY , buttonWidth , buttonHeight };
                if (GuiButton(button, buttonLabels[i])) {
                    switch (i) {
                        case 0:
                            changeMenu(&gameInfo, &menuState, GAME_MENU);
                            break;
                        case 1:
                            changeMenu(&gameInfo, &menuState, EXIT_STATE);
                            break;
                        default: break;
                    }
                }
            }
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

            // store prev position then move the snake position x and y
            int beenTimeInterval = accumulatedTime > moveTimeInterval;
            if (!gameOver && beenTimeInterval)
            {
                accumulatedTime = 0.0f;
                storePrevSnakePosition(&snake);
                moveSnake(&snake, &data, GetScreenWidth(), GetScreenHeight(), gameInfo);

                if (verboseMode)
                {
                    printLinkedList(&snake);
                    printf("%d\n", sizeOfLinkedList(&snake));
                    printf("%d\n", gameOver);
                }
            }

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

            // if the apple is overlapping head.
            const int appleOverlapSnakeX = (float)snake.head->snake_node.x == apple.x;
            const int appleOverlapSnakeY = (float)snake.head->snake_node.y == apple.y;

            if (appleOverlapSnakeX && appleOverlapSnakeY && !gameOver)
            {
                PlaySound(collectSound);
                score += 1;
                growSnake(&snake);
                applePos = moveApple(&snake, GetScreenWidth(), GetScreenHeight(), (int)gameInfo.moveInterval);
            }

            apple.x = (float)applePos.x;
            apple.y = (float)applePos.y;

            snakeHead.x = (float)snake.head->snake_node.x;
            snakeHead.y = (float)snake.head->snake_node.y;

            DrawRectangleRec(apple, RED);
            // Draw the snake head as dark green square.
            DrawRectangleRec(snakeHead, DARKGREEN);


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

            if (gameOver)
            {
                if (GuiButton((Rectangle){350, 250, 100, 50}, "Reset"))
                {
                    resetGame(&snake, &data, &gameInfo);
                    applePos = moveApple(&snake, GetScreenWidth(), GetScreenHeight(), (int)gameInfo.moveInterval);
                    apple.x = (float)applePos.x;
                    apple.y = (float)applePos.y;
                }
            }

            DrawText(TextFormat("Score: %0i", score), 0, 0, 50, BLACK);
        }

        if (menuState == EXIT_STATE) {
            break;
        }

        EndDrawing();
    }

    // unload all sounds in array of Sound
    int lengthOfSound = sizeof(sounds) / sizeof(sounds[0]);

    for (int i = 0; i < lengthOfSound; i++)
    {
        UnloadSound(sounds[i]);
    }

    // unload all music in array of Music
    int lengthOfMusic = sizeof(musics) / sizeof(musics[0]);
    for (int i = 0; i < lengthOfMusic; i++)
    {
        UnloadMusicStream(musics[i]);
    }

    CloseAudioDevice();
    CloseWindow();

    freeLinkedList(&snake);
    return 0;
}
