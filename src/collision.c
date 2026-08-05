#include "collision.h"

#include <stdlib.h>
#include <stdbool.h>

#include "assets.h"

#include "events.h"

void moveApple(Apple *apple, const LinkedList *snake)
{
    bool validPosition = false;
    Vector2 pos = randomApplePos();
    while (!validPosition)
    {
        // assume valid position until proven not
        validPosition = true;

        // if new apple overlaps snake head
        const bool appleOverlapSnakeX = snake->head->snake_node.x == pos.x;
        const bool appleOverlapSnakeY = snake->head->snake_node.y == pos.y;

        // then set valid position to false
        if (appleOverlapSnakeX && appleOverlapSnakeY)
        {
            validPosition = false;
        }

        Node *temp = snake->head->next;
        // if new apple is touching any part of the tail
        while (temp != NULL)
        {
            const bool tailOverlapAppleX = temp->snake_node.x == pos.x;
            const bool tailOverlapAppleY = temp->snake_node.y == pos.y;

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

void resolveSnakeAppleCollisions(Snake *snake, Apple *apple)
{
    // if the apple is overlapping head.
    const bool appleOverlapSnakeX = snake->snakeData.head->snake_node.x == apple->position.x;
    const bool appleOverlapSnakeY = snake->snakeData.head->snake_node.y == apple->position.y;

    if (appleOverlapSnakeX && appleOverlapSnakeY)
    {
        PlaySound(sounds[COLLECT_SOUND]);
        incrementScore();
        growSnake(snake);
        moveApple(apple, &snake->snakeData);
    }
}
