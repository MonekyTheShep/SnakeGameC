#include "snake.h"

#include <stdio.h>

#include <raylib.h>

#include "constants.h"

//----------------------------------------------------------------------------------
// Initialise Functions
//----------------------------------------------------------------------------------
LinkedList createSnake(void)
{
    const SnakeNode snake_node = {
            .x = 0.0f,
            .y = 0.0f
    };
    const LinkedList snake = createList(snake_node);

    return snake;
}

void initializeSnake(Snake *snake)
{
    snake->direction = RIGHT;
    snake->snakeData = createSnake();
    snake->snakeHead = (Rectangle){
        .x = 0.0f,
        .y = 0.0f,
        .width = (float) MOVE_INTERVAL,
        .height = (float) MOVE_INTERVAL
    }; // x, y, width, height
}

void cleanUpSnake(Snake *snake)
{
    snake->snakeData = clearList(&snake->snakeData);
}

//----------------------------------------------------------------------------------
// Logic Functions
//----------------------------------------------------------------------------------
int growSnake(LinkedList *snake)
{
    SnakeNode snake_node = {
            .x = 0.0f,
            .y = 0.0f
    };
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
            snake->snakeData.head->snake_node.y -= (float) MOVE_INTERVAL;
            break;
        case DOWN:
            snake->snakeData.head->snake_node.y += (float) MOVE_INTERVAL;
            break;
        case LEFT:
            snake->snakeData.head->snake_node.x -= (float) MOVE_INTERVAL;
            break;
        case RIGHT:
            snake->snakeData.head->snake_node.x += (float) MOVE_INTERVAL;
            break;
    }

    // screen wrapping'
    if (snake->snakeData.head->snake_node.y < 0.0f)
    {
        snake->snakeData.head->snake_node.y = (float) GetScreenHeight();
    }
    else if (snake->snakeData.head->snake_node.y >= (float) GetScreenHeight())
    {
        snake->snakeData.head->snake_node.y = 0.0f;
    }
    else if (snake->snakeData.head->snake_node.x < 0.0f)
    {
       snake->snakeData.head->snake_node.x = (float) GetScreenWidth();
    }
    else if (snake->snakeData.head->snake_node.x >= (float) GetScreenWidth())
    {
        snake->snakeData.head->snake_node.x = 0.0f;
    }
}

static float accumulatedTime = 0.0f; // Total elapsed time
static float accumulatedDebounceTime = 0.0f;

static void inputHandling(Snake *snake)
{
    // input checking
    if (accumulatedDebounceTime > SNAKE_TIME_INTERVAL)
    {
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

static void updateSnakePosition(Snake *snake)
{
    // store prev position and move
    if (accumulatedTime > SNAKE_TIME_INTERVAL)
    {
        accumulatedTime = 0.0f;
        storePrevSnakePosition(&snake->snakeData);
        moveSnake(snake);
    }

    // move the snake head rectangle
    snake->snakeHead.x = snake->snakeData.head->snake_node.x;
    snake->snakeHead.y = snake->snakeData.head->snake_node.y;
}

//----------------------------------------------------------------------------------
// Handle Functions
//----------------------------------------------------------------------------------
void handleSnake(const float deltaTime, Snake *snake)
{
    accumulatedTime += deltaTime;     // Add to total
    accumulatedDebounceTime += deltaTime;

    inputHandling(snake);
    updateSnakePosition(snake);
}


//----------------------------------------------------------------------------------
// Draw Functions
//----------------------------------------------------------------------------------
static void drawTails(Snake *snake)
{
    // prev pos stored after the head position
    Node *temp = snake->snakeData.head->next;

    // Draw Tails
    while (temp != NULL)
    {
        const Rectangle tail = {
                .x = (float)temp->snake_node.x,
                .y = (float)temp->snake_node.y,
                .width = (float) MOVE_INTERVAL,
                .height = (float) MOVE_INTERVAL
        };

        DrawRectangleRec(tail, GREEN);

        temp = temp->next;
    }
}

static void drawHead(Snake *snake)
{
    DrawRectangleRec(snake->snakeHead, DARKGREEN);
}

void drawSnake(Snake *snake)
{
    drawTails(snake);
    drawHead(snake);
}
