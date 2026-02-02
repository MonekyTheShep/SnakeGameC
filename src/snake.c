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


void moveSnake(void *arg, int screenWidth, int screenHeight)
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
            tdata->list->head->snake_node.y -= (int) tdata->moveInterval;
            break;
        case DOWN:
            tdata->list->head->snake_node.y += (int) tdata->moveInterval;
            break;
        case LEFT:
            tdata->list->head->snake_node.x -= (int) tdata->moveInterval;
            break;
        case RIGHT:
            tdata->list->head->snake_node.x += (int) tdata->moveInterval;
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

}
