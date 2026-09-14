#include "collision.h"

#include <_stdlib.h>
#include <stdlib.h>
#include <stdbool.h>

#include "raylib.h"

#include "apple.h"
#include "linkedlist.h"
#include "assets.h"
#include "events.h"
#include "snake.h"

void moveApple(Apple *apple, const LinkedList *snake)
{
    bool validPosition = true;
    Vector2 pos = randomApplePos();
    
    do
    {
        validPosition = true;

        // if new apple overlaps snake head
        const bool appleOverlapSnakeHeadX = (snake->head->snake_node.x == pos.x);
        const bool appleOverlapSnakeHeadY = (snake->head->snake_node.y == pos.y);

        const bool appleOverSnakeHead = (appleOverlapSnakeHeadX && appleOverlapSnakeHeadY);
        validPosition = !appleOverSnakeHead;

        Node *temp = snake->head->next;
        // if new apple is touching any part of the tail
        while (temp != NULL)
        {
            const bool appleOverlapTailX = (temp->snake_node.x == pos.x);
            const bool appleOverlapTailY = (temp->snake_node.y == pos.y);
            const bool appleOverlapTail = (appleOverlapTailX  && appleOverlapTailY);
            
            validPosition = !appleOverlapTail;

            temp = temp->next;
        }

        if (!validPosition)
        {
            pos = randomApplePos();
        }
    } while (!validPosition);
        
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
