#pragma once
#include "utility/gameutil.h"

typedef enum States
{
    TITLE_STATE,
    GAME_STATE,
    EXIT
} States;

void changeMenu(GameInfo *info, States *currentState, States changeState);

