#include <stdio.h>
#include "snake.h"

LinkedList createSnake()
{
    SnakeNode snake_node;
    snake_node.x = 0;
    snake_node.y = 0;
    LinkedList snake = createList(snake_node);

    return snake;
}

SnakeNode createSnakeNode()
{
    SnakeNode snake_node;
    snake_node.x = 0;
    snake_node.y = 0;
    return snake_node;
};

int growSnake(LinkedList *snake)
{
    insertAtTail(snake, createSnakeNode());
    return 0;
};
