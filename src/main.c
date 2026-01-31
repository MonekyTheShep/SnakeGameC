#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include <raylib.h>

#include "linkedlist.h"
#include "snake.h"
#include "apple.h"


const int screenWidth = 800;
const int screenHeight = 600;

int threadRunning = 0;

void *moveSnake(void *arg)
{
    const SnakeData *tdata=(SnakeData *)arg;

    switch (*tdata->direction) {
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

    // screen wrapping
    if (tdata->list->head->snake_node.y < 0) tdata->list->head->snake_node.y = screenHeight;
    if (tdata->list->head->snake_node.x < 0) tdata->list->head->snake_node.x = screenWidth;
    if (tdata->list->head->snake_node.y > screenHeight) tdata->list->head->snake_node.y = 0;
    if (tdata->list->head->snake_node.x > screenWidth) tdata->list->head->snake_node.x = 0;

    usleep(100000);
    threadRunning = 0;
    pthread_exit(NULL);
}


int main(void) {
    // Initialise SNAKE shit
    LinkedList snake = createSnake();

    enum Direction direction = RIGHT;
    const float moveInterval = 50;

    SnakeData data;
    data.moveInterval = &moveInterval;
    data.direction = &direction;
    data.list = &snake;

    pthread_t moveSnakeThread;

    // Initialise Raylib shit
    InitWindow(screenWidth, screenHeight, "Snake Game");

    SetTargetFPS(60);

    Rectangle square = { 0, 0, moveInterval, moveInterval }; // x, y, width, height
    Rectangle apple = { 0, 0, moveInterval, moveInterval }; // x, y, width, height

    RandomPos pos = randomApplePos(screenHeight, screenWidth, (int) moveInterval);

    while (!WindowShouldClose()) {
        if (!threadRunning) {
            threadRunning = true;
            pthread_create(&moveSnakeThread, NULL, moveSnake, (void *)&data);
        }

        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D) && direction != LEFT) direction = RIGHT;
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)  && direction != RIGHT) direction = LEFT;
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)  && direction != UP) direction = DOWN;
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)  && direction != DOWN) direction = UP;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        int appleOverlapSnakeX = (float) snake.head->snake_node.x == apple.x;
        int appleOverlapSnakeY = (float) snake.head->snake_node.y == apple.y;

        if (appleOverlapSnakeX && appleOverlapSnakeY) {
            pos = randomApplePos(screenHeight, screenWidth, (int) moveInterval);
        }


        apple.x = (float) pos.x;
        apple.y = (float) pos.y;


        square.x = (float) snake.head->snake_node.x;
        square.y = (float) snake.head->snake_node.y;

        // Draw the snake head as blue square.
        DrawRectangleRec(square, BLUE);
        DrawRectangleRec(apple, RED);

        EndDrawing();
    }

    CloseWindow();

    if (threadRunning) {
        pthread_join(moveSnakeThread, NULL);
    }


    // ignore this it will be used to move tails based on head
    // while (1) {
    //     Node *temp = list.head->next;
    //     int prevX = list.head->snake_node.x;
    //     int prevY = list.head->snake_node.y;
    //
    //     while (temp != NULL)
    //     {
    //         int tempPrevX = temp->snake_node.x;
    //         int tempPrevY = temp->snake_node.y;
    //
    //         temp->snake_node.x = prevX;
    //         temp->snake_node.y = prevY;
    //
    //         prevX = tempPrevX;
    //         prevY = tempPrevY;
    //
    //         temp = temp->next;
    //
    //     }
    //
    //     printLinkedList(&list);
    //
    //     sleep(1);
    // }

    freeLinkedList(&snake);
    return 0;
}
