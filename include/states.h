#pragma once

#include <stdbool.h>

//----------------------------------------------------------------------------------
// Typedef
//----------------------------------------------------------------------------------
typedef enum States
{
    TITLE_STATE,
    GAME_STATE,
    EXIT
} States;

//----------------------------------------------------------------------------------
// Title State Function Prototypes
//----------------------------------------------------------------------------------
void initializeTitleState(void);
void unloadTitleState(void);
bool finishTitleState(void);
bool exitState(void);
void updateTitleState(void);
void drawTitleState(void);

//----------------------------------------------------------------------------------
// Game State Function Prototypes
//----------------------------------------------------------------------------------
void initializeGameState(void);
void unloadGameState(void);
bool finishGameState(void);
void updateGameState(float deltaTime);
void drawGameState(void);
