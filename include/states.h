#pragma once
#include <stdbool.h>

typedef enum States
{
    TITLE_STATE,
    GAME_STATE,
    EXIT
} States;

// Title State
// Initialise Functions
void initializeTitleState(void);
bool finishTitleState(void);
bool exitState(void);
void unloadTitleState(void);
void updateTitleState(void);

// Draw Functions
void drawTitleState(void);

// GameState
// Initialise Functions
void initializeGameState(void);
void unloadGameState(void);
bool finishGameState(void);
void updateGameState(float deltaTime);

// Draw Functions
void drawGameState(void);


