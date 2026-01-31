#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include <raylib.h>

#include "linkedlist.h"
#include "snake.h"
#include "apple.h"


enum Direction {
    UP, DOWN, LEFT, RIGHT
};

typedef struct SnakeData {
    enum Direction *direction;
    LinkedList *list;
    const float *moveInterval;

} SnakeData;

int threadRunning = 0;

void *moveSnake(void *arg)
{
    const SnakeData *tdata=(SnakeData *)arg;

    if (*tdata->direction == RIGHT) tdata->list->head->snake_node.x += *tdata->moveInterval;
    if (*tdata->direction == LEFT) tdata->list->head->snake_node.x -= *tdata->moveInterval;
    if (*tdata->direction== DOWN) tdata->list->head->snake_node.y += *tdata->moveInterval;
    if (*tdata->direction == UP) tdata->list->head->snake_node.y -= *tdata->moveInterval;
    usleep(100000);
    threadRunning = 0;
    pthread_exit(NULL);
}


int main(void) {
    // Initialise SNAKE shit
    enum Direction direction = RIGHT;
    const float moveInterval = 50;

    SnakeNode snake_node;
    snake_node.x = 0;
    snake_node.y = 0;

    LinkedList snake;
    snake = createList(snake_node);

    SnakeData data;
    data.moveInterval = &moveInterval;
    data.direction = &direction;
    data.list = &snake;

    pthread_t moveSnakeThread;


    // Initialise Raylib shit

    const int screenWidth = 800;
    const int screenHeight = 600;

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

        if (IsKeyDown(KEY_RIGHT)) direction = RIGHT;
        if (IsKeyDown(KEY_LEFT)) direction = LEFT;
        if (IsKeyDown(KEY_DOWN)) direction = DOWN;
        if (IsKeyDown(KEY_UP)) direction = UP;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        int appleOverlapSnakeX = snake.head->snake_node.x == apple.x;
        int appleOverlapSnakeY = snake.head->snake_node.y == apple.y;

        if (appleOverlapSnakeX && appleOverlapSnakeY) {
            pos = randomApplePos(screenHeight, screenWidth, (int) moveInterval);
        }


        apple.x = (float) pos.x;
        apple.y = (float) pos.y;


        square.x = snake.head->snake_node.x;
        square.y = snake.head->snake_node.y;

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
    //     list.head->snake_node.x += moveInterval;
    //     list.head->snake_node.y += moveInterval;
    //
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
