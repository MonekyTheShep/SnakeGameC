#include <utility/menuutil.h>

#include "raygui.h"
#include "raylib.h"

void changeMenu(GameInfo *info, MenuStates *currentState, const MenuStates changeState)
{
    *currentState = changeState;
    info->musicPlaying = 0;
}
