#pragma once

#include "linkedlist.h"
#include "apple.h"
#include "utility/gameutil.h"


#include <raylib.h>

typedef enum Direction {
    UP, DOWN, LEFT, RIGHT
} Direction;

typedef struct Snake {
    LinkedList snakeData;
    Rectangle snakeHead;
    Direction direction;
} Snake;


// Snake Initialising
LinkedList createSnake(void);
void initializeSnake(Snake *snake);

// Snake Handling
int growSnake(LinkedList *snake);
void storePrevSnakePosition(const LinkedList *snake);
void moveSnake(Snake *snake);
void handleSnake(float deltaTime, Snake *snake, Apple *apple);

// Draw Functions
void drawSnake(Snake *snake);
