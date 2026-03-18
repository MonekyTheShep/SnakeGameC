#include "apple.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "constants.h"

#include <raylib.h>

//----------------------------------------------------------------------------------
// Initialise Functions
//----------------------------------------------------------------------------------
void initialiseApple(Apple *apple)
{
    apple->rec = (Rectangle) {
        .x = 0.0f,
        .y = 0.0f,
        .width = (float) MOVE_INTERVAL,
        .height = (float) MOVE_INTERVAL
    };
}

//----------------------------------------------------------------------------------
// Logic Functions
//----------------------------------------------------------------------------------
RandomPos randomApplePos(void)
{
    const int xCount = GetScreenWidth() / MOVE_INTERVAL;
    const int xIndex = GetRandomValue(0, xCount - 1);


    const int yCount = GetScreenHeight() / MOVE_INTERVAL;
    const int yIndex = GetRandomValue(0, yCount - 1);

    return (RandomPos){xIndex * MOVE_INTERVAL, yIndex * MOVE_INTERVAL};
}

//----------------------------------------------------------------------------------
// Handle Functions
//----------------------------------------------------------------------------------
void handleApple(Apple *apple)
{
    apple->rec.x = apple->position.x;
    apple->rec.y = apple->position.y;
}


//----------------------------------------------------------------------------------
// Draw Functions
//----------------------------------------------------------------------------------
void drawApple(Apple *apple)
{
    DrawRectangleRec(apple->rec, RED);
}
