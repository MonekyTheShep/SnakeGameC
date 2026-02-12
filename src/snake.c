#include "snake.h"

#include "constants.h"

#include <stdio.h>

#include <raylib.h>

#include "apple.h"

extern Sound sounds[];
extern int gameOver;
extern int score;


LinkedList createSnake(void)
{
    const SnakeNode snake_node = {0, 0};
    const LinkedList snake = createList(snake_node);

    return snake;
}

void initializeSnake(Snake *snake) {
    snake->direction = RIGHT;
    snake->snakeData = createSnake();
    snake->snakeHead = (Rectangle) {0, 0, MOVE_INTERVAL, MOVE_INTERVAL}; // x, y, width, height
}

int growSnake(LinkedList *snake)
{
    SnakeNode snake_node = {0,0};
    snake_node.x = snake->tail->snake_node.x;
    snake_node.y = snake->tail->snake_node.y;
    insertAtTail(snake, snake_node);
    return 0;
}


void storePrevSnakePosition(const LinkedList *snake)
{
    // store previous values before moving
    Node *temp = snake->head->next;
    float prevX = snake->head->snake_node.x;
    float prevY = snake->head->snake_node.y;

    while (temp != NULL)
    {
        float tempPrevX = temp->snake_node.x;
        float tempPrevY = temp->snake_node.y;

        temp->snake_node.x = prevX;
        temp->snake_node.y = prevY;

        // set prev for next iteration
        prevX = tempPrevX;
        prevY = tempPrevY;


        temp = temp->next;

    }
}


void moveSnake(Snake *snake)
{

    // move the head
    switch (snake->direction)
    {
        case UP:
            snake->snakeData.head->snake_node.y -= MOVE_INTERVAL;
            break;
        case DOWN:
            snake->snakeData.head->snake_node.y += MOVE_INTERVAL;
            break;
        case LEFT:
            snake->snakeData.head->snake_node.x -= MOVE_INTERVAL;
            break;
        case RIGHT:
            snake->snakeData.head->snake_node.x += MOVE_INTERVAL;
            break;
    }


    // screen wrapping'
    if (snake->snakeData.head->snake_node.y  < 0)
    {
        snake->snakeData.head->snake_node.y  = (float) GetScreenHeight();
    }
    else if (snake->snakeData.head->snake_node.y  >= (float) GetScreenHeight())
    {
        snake->snakeData.head->snake_node.y  = 0;
    }
    else if (snake->snakeData.head->snake_node.x < 0)
    {
       snake->snakeData.head->snake_node.x  = (float) GetScreenWidth();
    }
    else if (snake->snakeData.head->snake_node.x  >= (float) GetScreenWidth())
    {
        snake->snakeData.head->snake_node.x = 0;
    }
}


static void collisionHandling(Snake *snake, Rectangle *apple)
{
    // if the apple is overlapping head.
    const int appleOverlapSnakeX = snake->snakeData.head->snake_node.x == apple->x;
    const int appleOverlapSnakeY = snake->snakeData.head->snake_node.y == apple->y;

    if (appleOverlapSnakeX && appleOverlapSnakeY)
    {
        PlaySound(sounds[COLLECT_SOUND]);
        score += 1;
        growSnake(&snake->snakeData);

        // new apple pos
        const RandomPos applePos = moveApple(&snake->snakeData);

        // move the apple
        apple->x = (float)applePos.x;
        apple->y = (float)applePos.y;

    }
}


float accumulatedTime = 0.0f; // Total elapsed time
float accumulatedDebounceTime = 0.0f;
const float moveTimeInterval = 0.1f;

static void inputHandling(Snake *snake)
{
    // input checking
    if (accumulatedDebounceTime > moveTimeInterval) {
        accumulatedDebounceTime = 0.0f;
        if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && snake->direction != LEFT)
        {
            snake->direction = RIGHT;
        }
        else if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && snake->direction != RIGHT)
        {
            snake->direction = LEFT;
        }
        else if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && snake->direction != UP)
        {
            snake->direction = DOWN;
        }
        else if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && snake->direction != DOWN)
        {
            snake->direction = UP;
        }
    }
}


static void updateSnakePosition(Snake *snake) {
    // store prev position
    int beenTimeInterval = accumulatedTime > moveTimeInterval;
    if (beenTimeInterval)
    {
        accumulatedTime = 0.0f;
        storePrevSnakePosition(&snake->snakeData);
        moveSnake(snake);
    }

    // move the snake head rectangle
    snake->snakeHead.x = snake->snakeData.head->snake_node.x;
    snake->snakeHead.y =snake->snakeData.head->snake_node.y;
}

void handleSnake(const float deltaTime, Snake *snake, Rectangle *apple)
{
    accumulatedTime += deltaTime;     // Add to total
    accumulatedDebounceTime += deltaTime;

    inputHandling(snake);
    updateSnakePosition(snake);
    collisionHandling(snake, apple);
}



// All draw functions

static void drawTails(Snake *snake)
{
    // prev pos stored after the head position
    Node *temp = snake->snakeData.head->next;
    int length = 0;

    // move tail to previous positions and check if those tails are touching head
    while (temp != NULL)
    {
        length++;

        Rectangle tail = {(float)temp->snake_node.x, (float)temp->snake_node.y, MOVE_INTERVAL, MOVE_INTERVAL};
        DrawRectangleRec(tail, GREEN);

        const int tailOverlapHeadX = temp->snake_node.x == snake->snakeData.head->snake_node.x;
        const int tailOverlapHeadY = temp->snake_node.y == snake->snakeData.head->snake_node.y;
        const int hasTails = length > 1;
        // it has to be longer than 1

        // if tail overlaps head then it should game over and play death sound
        if (tailOverlapHeadX && tailOverlapHeadY && hasTails && !gameOver)
        {
            gameOver = 1;
            PlaySound(sounds[EXPLOSION_SOUND]);
            break;
        }

        temp = temp->next;
    }
}

static void drawHead(Snake *snake) {
    DrawRectangleRec(snake->snakeHead, DARKGREEN);
}

void drawSnake(Snake *snake)
{
    drawTails(snake);
    drawHead(snake);
}
