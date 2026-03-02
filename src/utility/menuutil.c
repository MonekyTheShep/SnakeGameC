#include <utility/menuutil.h>

#include "raygui.h"
#include "raylib.h"

void changeMenu(GameInfo *info, States *currentState, const States changeState)
{
    *currentState = changeState;
    info->musicPlaying = 0;
}
