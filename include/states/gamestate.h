#pragma once

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

//----------------------------------------------------------------------------------
// Logic Functions
//----------------------------------------------------------------------------------
void incrementScore(void);
void gameOver(void);
bool isGameOver(void);
