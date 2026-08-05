#pragma once

#include "linkedlist.h"

#include <raylib.h>

//----------------------------------------------------------------------------------
// Typedefs
//----------------------------------------------------------------------------------
typedef enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef struct Snake
{
    LinkedList snakeData;
    Direction direction;
    int length;
} Snake;

//----------------------------------------------------------------------------------
// Initialise Functions
//----------------------------------------------------------------------------------
LinkedList createSnake(void);
void initializeSnake(Snake *snake);
void cleanUpSnake(Snake *snake);

//----------------------------------------------------------------------------------
// Logic Functions
//----------------------------------------------------------------------------------
int growSnake(Snake *snake);
void storePrevSnakePosition(const LinkedList *snake);
void moveSnake(Snake *snake);

//----------------------------------------------------------------------------------
// Handle Functions
//----------------------------------------------------------------------------------
void handleSnake(float deltaTime, Snake *snake);

//----------------------------------------------------------------------------------
// Draw Functions
//----------------------------------------------------------------------------------
void drawSnake(const Snake *snake);
