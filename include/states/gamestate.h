#pragma once

#include <stdbool.h>

#include "snake.h"
#include "apple.h"

//----------------------------------------------------------------------------------
// Typedefs
//----------------------------------------------------------------------------------
typedef struct GameState
{
    Snake snake;
    Apple apple;

    int maxSnakeSize;
    int score;
    bool gameOver;

} GameState;
