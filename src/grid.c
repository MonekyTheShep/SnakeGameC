#include "grid.h"

#include "constants.h"

#include <raylib.h>

void drawGrid(void)
{
    for (int i = 0; i < GetScreenWidth() / MOVE_INTERVAL; i++)
    {
        DrawLine(i * MOVE_INTERVAL,0,i * MOVE_INTERVAL,GetScreenHeight(), Fade(BLACK, 0.5f));
    }

    for (int i = 0; i < GetScreenHeight() / MOVE_INTERVAL; i++)
    {
        DrawLine(0,i * MOVE_INTERVAL,GetScreenWidth(),i * MOVE_INTERVAL, Fade(BLACK, 0.5f));
    }
}
