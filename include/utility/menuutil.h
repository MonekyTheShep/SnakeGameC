#pragma once
#include "utility/gameutil.h"

typedef enum MenuStates
{
    TITLE_STATE,
    GAME_STATE,
    EXIT
} MenuStates;

void changeMenu(GameInfo *info, MenuStates *currentState, MenuStates changeState);

