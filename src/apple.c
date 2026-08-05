#include "apple.h"

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
        .width = (float) SNAKE_SQUARE_SIZE,
        .height = (float) SNAKE_SQUARE_SIZE
    };
}

//----------------------------------------------------------------------------------
// Logic Functions
//----------------------------------------------------------------------------------
Vector2 randomApplePos(void)
{
    const int xCount = GetScreenWidth() / SNAKE_SQUARE_SIZE;
    const int xIndex = GetRandomValue(0, xCount - 1);


    const int yCount = GetScreenHeight() / SNAKE_SQUARE_SIZE;
    const int yIndex = GetRandomValue(0, yCount - 1);

    return (Vector2){(float) xIndex * SNAKE_SQUARE_SIZE, (float) yIndex * SNAKE_SQUARE_SIZE};
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
void drawApple(const Apple *apple)
{
    DrawRectangleRec(apple->rec, RED);
}
