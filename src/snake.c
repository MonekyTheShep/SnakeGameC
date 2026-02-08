#include <stdio.h>
#include "snake.h"
#include "raylib.h"

LinkedList createSnake(void)
{
    const SnakeNode snake_node = {0, 0};
    const LinkedList snake = createList(snake_node);

    return snake;
}

int growSnake(LinkedList *snake)
{
    SnakeNode snake_node = {0,0};
    snake_node.x = snake->tail->snake_node.x;
    snake_node.y = snake->tail->snake_node.y;
    insertAtTail(snake, snake_node);
    return 0;
}


void storePrevSnakePosition(const LinkedList *snake) {
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


void moveSnake(const LinkedList *snake, const SnakeData *data, const float moveInterval)
{

    // move the head
    switch (*data->direction)
    {
        case UP:
            snake->head->snake_node.y -= moveInterval;
            break;
        case DOWN:
            snake->head->snake_node.y += moveInterval;
            break;
        case LEFT:
            snake->head->snake_node.x -= moveInterval;
            break;
        case RIGHT:
            snake->head->snake_node.x += moveInterval;
            break;
    }


    // screen wrapping'
    if (snake->head->snake_node.y < 0)
    {
        snake->head->snake_node.y = (float) GetScreenHeight();
    }
    else if (snake->head->snake_node.y >= (float) GetScreenHeight()) {
        snake->head->snake_node.y = 0;
    }
    else if (snake->head->snake_node.x < 0)
    {
        snake->head->snake_node.x = (float) GetScreenWidth();
    }
    else if (snake->head->snake_node.x >= (float) GetScreenWidth()) {
        snake->head->snake_node.x = 0;
    }

}
