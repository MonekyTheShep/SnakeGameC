#pragma once

#include "raylib.h"

#include "utility/menuutil.h"

void initializeGame(Sound (*currentSounds));
void updateGameMenu(GameInfo *gameInfo, MenuStates *menuState);
void drawGame(GameInfo *gameinfo, MenuStates *menuState);
void CleanUpGame(void);
