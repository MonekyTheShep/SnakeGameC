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

void moveApple(Apple *apple, const LinkedList *snake)
{
    bool validPosition = false;
    RandomPos pos = randomApplePos();
    while (!validPosition)
    {
        // assume valid position until proven not
        validPosition = true;

        // if new apple overlaps snake head
        const bool appleOverlapSnakeX = (int) snake->head->snake_node.x == pos.x;
        const bool appleOverlapSnakeY = (int) snake->head->snake_node.y == pos.y;

        // then set valid position to false
        if (appleOverlapSnakeX && appleOverlapSnakeY)
        {
            validPosition = false;
        }

        Node *temp = snake->head->next;

        // if new apple is touching any part of the tail
        while (temp != NULL)
        {
            const bool tailOverlapAppleX = (int) temp->snake_node.x == pos.x;
            const bool tailOverlapAppleY = (int) temp->snake_node.y == pos.y;

            if (tailOverlapAppleX  && tailOverlapAppleY)
            {
                validPosition = false;
            }

            temp = temp->next;
        }

        if (!validPosition)
        {
            pos = randomApplePos();
        }
    }

    apple->position.x = (float) pos.x;
    apple->position.y = (float) pos.y;
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
