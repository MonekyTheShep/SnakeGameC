#pragma once
#include "utility/gameutil.h"

typedef enum MenuStates
{
    MAIN_MENU,
    GAME_MENU,
    EXIT
} MenuStates;

void changeMenu(GameInfo *info, MenuStates *currentState, MenuStates changeState);

