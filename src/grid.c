#include "grid.h"

#include "constants.h"

#include <raylib.h>

//----------------------------------------------------------------------------------
// Draw Functions
//----------------------------------------------------------------------------------
void drawGrid(void)
{
    for (int i = 0; i < GetScreenWidth() / SNAKE_SQUARE_SIZE; i++)
    {
        DrawLine(i * SNAKE_SQUARE_SIZE,0,i * SNAKE_SQUARE_SIZE,GetScreenHeight(), Fade(BLACK, 0.5f));
    }

    for (int i = 0; i < GetScreenHeight() / SNAKE_SQUARE_SIZE; i++)
    {
        DrawLine(0,i * SNAKE_SQUARE_SIZE,GetScreenWidth(),i * SNAKE_SQUARE_SIZE, Fade(BLACK, 0.5f));
    }
}
