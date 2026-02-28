#include "apple.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "constants.h"

#include <raylib.h>

// Apple initialising
void initialiseApple(Apple *apple)
{
    apple->rec = (Rectangle) {0.0f, 0.0f, (float) MOVE_INTERVAL, (float) MOVE_INTERVAL};
}

// Logic Functions
RandomPos randomApplePos(const int moveInterval)
{
    const int xCount = GetScreenWidth() / moveInterval;
    const int xIndex = rand() % xCount;


    const int yCount = GetScreenHeight() / moveInterval;
    const int yIndex = rand() % yCount;

    return (RandomPos){xIndex * moveInterval, yIndex * moveInterval};
}

void moveApple(Apple *apple, const LinkedList *snake)
{
    bool validPosition = false;
    RandomPos pos = randomApplePos(MOVE_INTERVAL);
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
            printf("Moved of the head.\n");
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

                printf("Moved of the tail.\n");
            }

            temp = temp->next;
        }

        if (!validPosition)
        {
            pos = randomApplePos(MOVE_INTERVAL);
        }
    }

    apple->position.x = (float) pos.x;
    apple->position.y = (float) pos.y;
}

// Handle Functions
void handleApple(Apple *apple)
{
    apple->rec.x = apple->position.x;
    apple->rec.y = apple->position.y;
}


// Draw Functions
void drawApple(Apple *apple)
{
    DrawRectangleRec(apple->rec, RED);
}
