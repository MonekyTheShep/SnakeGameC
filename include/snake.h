#pragma once

#include "linkedlist.h"
#include "utility/gameutil.h"

#include <raylib.h>

typedef enum Direction {
    UP, DOWN, LEFT, RIGHT
} Direction;

typedef struct Snake {
    LinkedList snakeData;
    Direction direction;
    Rectangle snakeHead;
    Vector2 position;
} Snake;


LinkedList createSnake(void);
void initializeSnake(Snake *snake);
int growSnake(LinkedList *snake);
void storePrevSnakePosition(const LinkedList *snake);
void moveSnake(Snake *snake);
