#pragma once

#include "raylib.h"

#include "utility/menuutil.h"

void InitializeGameState(void);
void updateGameState(float deltaTime, GameInfo *gameInfo, MenuStates *menuState);
void incrementScore(void);
void drawGameState(GameInfo *gameinfo, MenuStates *menuState);
void UnloadGameState(void);
