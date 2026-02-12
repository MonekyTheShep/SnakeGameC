#include "apple.h"

#include <stdlib.h>
#include <stdio.h>

#include <raylib.h>


RandomPos randomApplePos(const int moveInterval)
{
    const int xCount = GetScreenWidth() / moveInterval;
    const int xIndex = rand() % xCount;


    const int yCount = GetScreenHeight() / moveInterval;
    const int yIndex = rand() % yCount;

    return (RandomPos){xIndex * moveInterval, yIndex * moveInterval};
}

RandomPos moveApple(const LinkedList *snake, const int moveInterval) {
    int validPosition = 0;
    RandomPos pos = randomApplePos(moveInterval);
    while (!validPosition)
    {
        // assume valid position until proven not
        validPosition = 1;

        // if new apple overlaps snake head
        const int appleOverlapSnakeX = (int) snake->head->snake_node.x == pos.x;
        const int appleOverlapSnakeY = (int) snake->head->snake_node.y == pos.y;

        // then set valid position to false
        if (appleOverlapSnakeX && appleOverlapSnakeY)
        {
            validPosition = 0;
            printf("Moved of the head.\n");
        }

        Node *temp = snake->head->next;

        // if new apple is touching any part of the tail
        while (temp != NULL) {
            const int tailOverlapAppleX = (int) temp->snake_node.x == pos.x;
            const int tailOverlapAppleY = (int) temp->snake_node.y == pos.y;
            const int hasTails = temp->next != NULL;

            if (tailOverlapAppleX  && tailOverlapAppleY && hasTails)
            {
                validPosition = 0;

                printf("Moved of the tail.\n");
            }

            temp = temp->next;
        }

        if (!validPosition)
        {
            pos = randomApplePos(moveInterval);
        }
    }
    return pos;
}

void drawApple(Rectangle *apple) {
    DrawRectangleRec(*apple, RED);
}
