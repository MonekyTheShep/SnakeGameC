#include <stdio.h>
#include "snake.h"

LinkedList createSnake(void)
{
    SnakeNode snake_node = {0, 0};
    LinkedList snake = createList(snake_node);

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
    int prevX = snake->head->snake_node.x;
    int prevY = snake->head->snake_node.y;

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
}


void moveSnake(const LinkedList *snake, SnakeData *data, const int screenWidth, const int screenHeight, GameInfo gameInfo)
{

    // move the head
    switch (*data->direction)
    {
        case UP:
            snake->head->snake_node.y -= gameInfo.moveInterval;
            break;
        case DOWN:
            snake->head->snake_node.y += gameInfo.moveInterval;
            break;
        case LEFT:
            snake->head->snake_node.x -= gameInfo.moveInterval;
            break;
        case RIGHT:
            snake->head->snake_node.x += gameInfo.moveInterval;
            break;
    }


    // screen wrapping'
    if (snake->head->snake_node.y < 0)
    {
        snake->head->snake_node.y = (float) screenHeight;
    }
    else if (snake->head->snake_node.y >= (float) screenHeight) {
        snake->head->snake_node.y = 0;
    }
    else if (snake->head->snake_node.x < 0)
    {
        snake->head->snake_node.x = (float) screenWidth;
    }
    else if (snake->head->snake_node.x >= (float) screenWidth) {
        snake->head->snake_node.x = 0;
    }

}
