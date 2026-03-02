#pragma once

#include "snake.h"

typedef struct GameState {
    Snake snake;
    Apple apple;

    int maxSnakeSize;
    int score;
    bool gameOver;

} GameState;

// Logic Functions
void incrementScore(void);

