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
