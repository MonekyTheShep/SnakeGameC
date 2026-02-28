#pragma once

#include "raylib.h"

#include "utility/menuutil.h"

void InitializeGameState(void);
void updateGameMenu(float deltaTime, GameInfo *gameInfo, MenuStates *menuState);
void incrementScore(void);
void drawGame(GameInfo *gameinfo, MenuStates *menuState);
void UnloadGameState(void);
