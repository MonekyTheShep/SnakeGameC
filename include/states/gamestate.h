#pragma once

#include "snake.h"

#include "utility/menuutil.h"

typedef struct GameState {

} GameState;

void InitializeGameState(void);
void updateGameState(float deltaTime, GameInfo *gameInfo, MenuStates *menuState);
void incrementScore(void);
void drawGameState(GameInfo *gameinfo, MenuStates *menuState);
void UnloadGameState(void);
