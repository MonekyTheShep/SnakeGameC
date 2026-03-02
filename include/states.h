#pragma once
#include <stdbool.h>
#include <utility/menuutil.h>

// GameState
// Initialise Functions
void initializeGameState(void);
void unloadGameState(void);
bool finishGameState(void);
void updateGameState(float deltaTime, GameInfo *gameInfo, States *menuState);

// Draw Functions
void drawGameState(GameInfo *gameinfo, States *menuState);


// Title State
// Initialise Functions
void initializeTitleState(void);
bool finishTitleState(void);
void unloadTitleState(void);
void updateTitleState(void);

// Draw Functions
void drawTitleState(GameInfo *gameInfo, States *menuState);