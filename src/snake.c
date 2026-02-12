#include "snake.h"

#include "constants.h"

#include <stdio.h>

#include <raylib.h>

LinkedList createSnake(void)
{
    const SnakeNode snake_node = {0, 0};
    const LinkedList snake = createList(snake_node);

    return snake;
}

void initializeSnake(Snake *snake) {
    snake->direction = RIGHT;
    snake->snakeData = createSnake();
    snake->snakeHead = (Rectangle) {0, 0, MOVE_INTERVAL, MOVE_INTERVAL}; // x, y, width, height
}

int growSnake(LinkedList *snake)
{
    SnakeNode snake_node = {0,0};
    snake_node.x = snake->tail->snake_node.x;
    snake_node.y = snake->tail->snake_node.y;
    insertAtTail(snake, snake_node);
    return 0;
}


void storePrevSnakePosition(const LinkedList *snake)
{
    // store previous values before moving
    Node *temp = snake->head->next;
    float prevX = snake->head->snake_node.x;
    float prevY = snake->head->snake_node.y;

    while (temp != NULL)
    {
        float tempPrevX = temp->snake_node.x;
        float tempPrevY = temp->snake_node.y;

        temp->snake_node.x = prevX;
        temp->snake_node.y = prevY;

        // set prev for next iteration
        prevX = tempPrevX;
        prevY = tempPrevY;


        temp = temp->next;

    }
}


void moveSnake(Snake *snake)
{

    // move the head
    switch (snake->direction)
    {
        case UP:
            snake->snakeData.head->snake_node.y -= MOVE_INTERVAL;
            break;
        case DOWN:
            snake->snakeData.head->snake_node.y += MOVE_INTERVAL;
            break;
        case LEFT:
            snake->snakeData.head->snake_node.x -= MOVE_INTERVAL;
            break;
        case RIGHT:
            snake->snakeData.head->snake_node.x += MOVE_INTERVAL;
            break;
    }


    // screen wrapping'
    if (snake->snakeData.head->snake_node.y  < 0)
    {
        snake->snakeData.head->snake_node.y  = (float) GetScreenHeight();
    }
    else if (snake->snakeData.head->snake_node.y  >= (float) GetScreenHeight())
    {
        snake->snakeData.head->snake_node.y  = 0;
    }
    else if (snake->snakeData.head->snake_node.x < 0)
    {
       snake->snakeData.head->snake_node.x  = (float) GetScreenWidth();
    }
    else if (snake->snakeData.head->snake_node.x  >= (float) GetScreenWidth())
    {
        snake->snakeData.head->snake_node.x = 0;
    }

}
