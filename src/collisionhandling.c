#include "collisionhandling.h"

#include "assets.h"

#include "events.h"

#include <stdlib.h>

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


void collisionHandling(Snake *snake, Apple *apple)
{
    // if the apple is overlapping head.
    const bool appleOverlapSnakeX = snake->snakeData.head->snake_node.x == apple->position.x;
    const bool appleOverlapSnakeY = snake->snakeData.head->snake_node.y == apple->position.y;

    if (appleOverlapSnakeX && appleOverlapSnakeY)
    {
        PlaySound(sounds[COLLECT_SOUND]);
        incrementScore();
        growSnake(&snake->snakeData);

        moveApple(apple, &snake->snakeData);
    }

    // Tail Collision Handling
    Node *temp = snake->snakeData.head->next;
    int length = 0;

    while (temp != NULL)
    {
        length++;
        const bool tailOverlapHeadX = temp->snake_node.x == snake->snakeData.head->snake_node.x;
        const bool tailOverlapHeadY = temp->snake_node.y == snake->snakeData.head->snake_node.y;
        // it has to be longer than 1
        const bool hasTails = length > 1;

        // if tail overlaps head then it should game over and play death sound
        if (tailOverlapHeadX && tailOverlapHeadY && hasTails && !isGameOver())
        {
            gameOver();
            PlaySound(sounds[EXPLOSION_SOUND]);
        }

        temp = temp->next;
    }
}

