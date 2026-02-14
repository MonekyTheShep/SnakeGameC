#pragma once

#include "raylib.h"

#include "utility/menuutil.h"

void initializeGame(void);
void updateGameMenu(GameInfo *gameInfo, MenuStates *menuState);
void incrementScore(void);
void drawGame(GameInfo *gameinfo, MenuStates *menuState);
void CleanUpGame(void);
