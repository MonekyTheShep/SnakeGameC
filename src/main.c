#include <stdio.h>
#include <pthread.h>

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "linkedlist.h"
#include "snake.h"
#include "apple.h"


enum MenuStates {
    MAIN_MENU, GAME
};

const int screenWidth = 800;
const int screenHeight = 600;
const float moveInterval = 50;

int gameOver = 0;
int score = 0;

int verboseMode = 0;

void resetGame(LinkedList *snake, SnakeData *data)
{
    // reset snake by freeing and creating new snake

    *snake = clearList(snake);
    *snake = createSnake();

    *data->direction = RIGHT;
    score = 0;
    gameOver = 0;
}

int main(void)
{
    // Initialise SNAKE shit
    LinkedList snake = createSnake();
    enum Direction direction = RIGHT;
    enum MenuStates menuState = MAIN_MENU;

    SnakeData data;
    data.moveInterval = &moveInterval;
    data.direction = &direction;
    data.list = &snake;

    // Initialise Raylib shit
    InitWindow(screenWidth, screenHeight, "Snake Game");
    InitAudioDevice();


    Sound collectSound = LoadSound(ASSETS_PATH"collectsound.ogg");
    Sound explosionSound = LoadSound(ASSETS_PATH"explosionsound.ogg");

    Music mainMenuSound = LoadMusicStream(ASSETS_PATH"mainmenu.ogg");
    Music gameMusicSound = LoadMusicStream(ASSETS_PATH"gamemusic.ogg");

    Music *currentMusic = &mainMenuSound;

    PlayMusicStream(*currentMusic);

    SetTargetFPS(60);

    Rectangle snakeHead = { 0, 0, moveInterval, moveInterval }; // x, y, width, height


    float accumulatedTime = 0.0f; // Total elapsed time
    float accumulatedDebounceTime = 0.0f;

    RandomPos applePos = moveApple(&snake, screenWidth, screenHeight, (int) moveInterval);
    Rectangle apple = { (float) applePos.x, (float) applePos.y, moveInterval, moveInterval }; // x, y, width, height

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime(); // Time since last frame
        accumulatedTime += deltaTime;      // Add to total
        accumulatedDebounceTime += deltaTime;

        UpdateMusicStream(*currentMusic);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (menuState == MAIN_MENU)
        {
            const float buttonWidth = 100;
            const float buttonHeight = 50;
            if (GuiButton((Rectangle){ ((float) screenWidth - buttonWidth) / 2, ((float) screenHeight - buttonHeight) / 2, buttonWidth, buttonHeight}, "Start"))
            {
                menuState = GAME;
                StopMusicStream(*currentMusic);
                currentMusic = &gameMusicSound;
                PlayMusicStream(*currentMusic);

            }
            EndDrawing();
            continue;
        }



        // store prev position then move the snake position x and y
        int beenTimeInterval = accumulatedTime > 0.1f;
        if (!gameOver && beenTimeInterval)
        {
            accumulatedTime = 0.0f;
            moveSnake(&data, screenWidth, screenHeight);

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

            Rectangle tail = { (float) temp->snake_node.x, (float) temp->snake_node.y,  moveInterval,  moveInterval };
            DrawRectangleRec(tail, GREEN);

            int tailOverlapHeadX = temp->snake_node.x == snake.head->snake_node.x;
            int tailOverlapHeadY = temp->snake_node.y == snake.head->snake_node.y;
            int hasTails = length > 1;
            // it has to be longer than 1

            if (tailOverlapHeadX && tailOverlapHeadY && hasTails && !gameOver)
            {
                gameOver = 1;
                PlaySound(explosionSound);
                break;
            }

            temp = temp->next;
        }

        if (accumulatedDebounceTime > 0.1f  && !gameOver) {
            accumulatedDebounceTime = 0.0f;
            // input checking
            if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && direction != LEFT) direction = RIGHT;
            else if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && direction != RIGHT) direction = LEFT;
            else if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && direction != UP) direction = DOWN;
            else if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && direction != DOWN) direction = UP;
        }


        // if the apple is overlapping head.
        int appleOverlapSnakeX = (float) snake.head->snake_node.x == apple.x;
        int appleOverlapSnakeY = (float) snake.head->snake_node.y == apple.y;

        if (appleOverlapSnakeX && appleOverlapSnakeY && !gameOver)
        {
            PlaySound(collectSound);
            score += 1;
            growSnake(&snake);
            applePos = moveApple(&snake, screenWidth, screenHeight, (int) moveInterval);
        }


        apple.x = (float) applePos.x;
        apple.y = (float) applePos.y;

        snakeHead.x = (float) snake.head->snake_node.x;
        snakeHead.y = (float) snake.head->snake_node.y;


        DrawRectangleRec(apple, RED);
        // Draw the snake head as dark green square.
        DrawRectangleRec(snakeHead, DARKGREEN);

        if (gameOver)
        {
            if (GuiButton((Rectangle){350, 250, 100, 50}, "Reset"))
            {
                resetGame(&snake, &data);
                applePos = moveApple(&snake, screenWidth, screenHeight, (int) moveInterval);
                apple.x = (float) applePos.x;
                apple.y = (float) applePos.y;
            }
        }


        DrawText(TextFormat("Score: %0i", score), 0, 0, 50, BLACK);

        EndDrawing();
    }

    UnloadSound(explosionSound);
    UnloadSound(collectSound);
    UnloadMusicStream(gameMusicSound);
    UnloadMusicStream(mainMenuSound);

    CloseAudioDevice();
    CloseWindow();

    freeLinkedList(&snake);
    return 0;
}
