#include <stdlib.h>
#include <stdio.h>
#include "apple.h"


RandomPos randomApplePos(int screenWidth, int screenHeight, int moveInterval)
{
    int xCount = screenWidth / moveInterval;
    int xIndex = rand() % xCount;

    int yCount = screenHeight / moveInterval;
    int yIndex = rand() % yCount;

    return (RandomPos){xIndex * moveInterval, yIndex * moveInterval};
};

RandomPos moveApple(LinkedList *snake, int screenWidth, int screenHeight, int moveInterval) {
    int validPosition = 0;
    RandomPos pos = randomApplePos(screenWidth, screenHeight, moveInterval);
    while (!validPosition) {
        // assume valid position until proven not
        validPosition = 1;

        // if new apple overlaps snake head
        int appleOverlapSnakeX = snake->head->snake_node.x == pos.x;
        int appleOverlapSnakeY = snake->head->snake_node.y == pos.y;

        // then set valid position to false
        if (appleOverlapSnakeX && appleOverlapSnakeY) {
            validPosition = 0;
            printf("Moved of the head.\n");
        }

        Node *temp = snake->head->next;

        // if apple is touching any part of the tail
        while (temp != NULL) {
            int tailOverlapAppleX = temp->snake_node.x == pos.x;
            int tailOverlapAppleY = temp->snake_node.y == pos.y;
            int hasTails = temp->next != NULL;

            if (tailOverlapAppleX  && tailOverlapAppleY && hasTails) {
                validPosition = 0;

                printf("Moved of the tail.\n");
            }

            temp = temp->next;
        }

        if (!validPosition) {
            pos = randomApplePos(screenWidth, screenHeight, moveInterval);
        }
    }
    return pos;
}