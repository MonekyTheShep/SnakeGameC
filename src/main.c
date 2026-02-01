#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "linkedlist.h"
#include "snake.h"
#include "apple.h"


const int screenWidth = 800;
const int screenHeight = 600;

// only one thread can run at once
int threadRunning = 0;
int gameOver = 0;

int verboseMode = 0;

pthread_mutex_t snakeMutex;

void resetGame(LinkedList *snake, SnakeData *data) {
    // reset snake by freeing and creating new snake

    *snake = clearList(snake);
    *snake = createSnake();
    *data->direction = RIGHT;
    gameOver = 0;
}
void *moveSnake(void *arg)
{
    const SnakeData *tdata=(SnakeData *)arg;

    // store previous values before moving
    Node *temp = tdata->list->head->next;
    int prevX = tdata->list->head->snake_node.x;
    int prevY = tdata->list->head->snake_node.y;

    while (temp != NULL)
    {
        int tempPrevX = temp->snake_node.x;
        int tempPrevY = temp->snake_node.y;

        temp->snake_node.x = prevX;
        temp->snake_node.y = prevY;

        // set prev for next iteration
        prevX = tempPrevX;
        prevY = tempPrevY;


        temp = temp->next;

    }

    // move the head
    switch (*tdata->direction)
    {
        case UP:
            tdata->list->head->snake_node.y -= (int) *tdata->moveInterval;
            break;
        case DOWN:
            tdata->list->head->snake_node.y += (int) *tdata->moveInterval;
            break;
        case LEFT:
            tdata->list->head->snake_node.x -= (int) *tdata->moveInterval;
            break;
        case RIGHT:
            tdata->list->head->snake_node.x += (int) *tdata->moveInterval;
            break;
    }


    // screen wrapping'
    if (tdata->list->head->snake_node.y < 0)
    {
        tdata->list->head->snake_node.y = screenHeight;
    }
    else if (tdata->list->head->snake_node.y >= screenHeight) {
        tdata->list->head->snake_node.y = 0;
    }
    else if (tdata->list->head->snake_node.x < 0)
    {
        tdata->list->head->snake_node.x = screenWidth;
    }
    else if (tdata->list->head->snake_node.x >= screenWidth) {
        tdata->list->head->snake_node.x = 0;
    }


    usleep(100000);

    pthread_mutex_lock(&snakeMutex);
    threadRunning = 0;
    pthread_mutex_unlock(&snakeMutex);
    pthread_exit(NULL);
}


int main(void)
{
    // Initialise SNAKE shit
    LinkedList snake = createSnake();

    enum Direction direction = RIGHT;
    const float moveInterval = 50;
    int score = 0;

    SnakeData data;
    data.moveInterval = &moveInterval;
    data.direction = &direction;
    data.list = &snake;

    pthread_t moveSnakeThread;
    // Initialize mutex
    pthread_mutex_init(&snakeMutex, NULL);


    // Initialise Raylib shit
    InitWindow(screenWidth, screenHeight, "Snake Game");

    SetTargetFPS(60);

    Rectangle snakeHead = { 0, 0, moveInterval, moveInterval }; // x, y, width, height


    RandomPos applePos = moveApple(&snake, screenWidth, screenHeight, (int) moveInterval);
    Rectangle apple = { (float) applePos.x, (float) applePos.y, moveInterval, moveInterval }; // x, y, width, height

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (gameOver) {
            if (GuiButton((Rectangle){350, 250, 100, 50}, "Reset")) {
                resetGame(&snake, &data);
            }
        }

        // prev pos stored after the head position
        Node *temp = snake.head->next;

        int length = 0;

        // move tail to previous positions and check if those tails are touching head
        while (temp != NULL) {
            length++;

            Rectangle tail = { (float) temp->snake_node.x, (float) temp->snake_node.y,  moveInterval,  moveInterval };
            DrawRectangleRec(tail, GREEN);

            int tailOverlapHeadX = temp->snake_node.x == snake.head->snake_node.x;
            int tailOverlapHeadY = temp->snake_node.y == snake.head->snake_node.y;
            int hasTails = length > 1;
            // it has to be longer than 1

            if (tailOverlapHeadX && tailOverlapHeadY && hasTails) {
                gameOver = 1;

            }

            temp = temp->next;
        }

        // store prev position then move the snake position x and y

        if (!gameOver && !threadRunning)
        {
            pthread_mutex_lock(&snakeMutex);
            threadRunning = true;
            pthread_mutex_unlock(&snakeMutex);

            if (verboseMode) {
                printLinkedList(&snake);
                printf("%d\n", sizeOfLinkedList(&snake));
                printf("%d\n", gameOver);
            }


            pthread_create(&moveSnakeThread, NULL, moveSnake, &data);
        }


        // input checking
        if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && direction != LEFT) direction = RIGHT;
        else if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && direction != RIGHT) direction = LEFT;
        else if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && direction != UP) direction = DOWN;
        else if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && direction != DOWN) direction = UP;

        // if the apple is overlapping head.
        int appleOverlapSnakeX = (float) snake.head->snake_node.x == apple.x;
        int appleOverlapSnakeY = (float) snake.head->snake_node.y == apple.y;

        if (appleOverlapSnakeX && appleOverlapSnakeY)
        {
            score += 1;
            growSnake(&snake);
            applePos = moveApple(&snake, screenWidth, screenHeight, (int) moveInterval);

        }


        apple.x = (float) applePos.x;
        apple.y = (float) applePos.y;

        snakeHead.x = (float) snake.head->snake_node.x;
        snakeHead.y = (float) snake.head->snake_node.y;


        DrawRectangleRec(apple, RED);
        // Draw the snake head as blue square.
        DrawRectangleRec(snakeHead, DARKGREEN);

        DrawText(TextFormat("Score: %0i", score), 0, 0, 50, BLACK);

        EndDrawing();
    }

    CloseWindow();


    if (threadRunning) {
        pthread_join(moveSnakeThread, NULL);
    }

    pthread_mutex_destroy(&snakeMutex);

    freeLinkedList(&snake);
    return 0;
}
