#pragma once

#include "snake.h"

#include "utility/menuutil.h"

typedef struct GameState {

} GameState;

// Intialise Functions
void InitializeGameState(void);
void UnloadGameState(void);

// Logic Functions
void incrementScore(void);
void updateGameState(float deltaTime, GameInfo *gameInfo, MenuStates *menuState);

// Draw Functions
void drawGameState(GameInfo *gameinfo, MenuStates *menuState);

