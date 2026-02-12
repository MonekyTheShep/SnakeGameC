#include "states/gamestate.h"

#include <stddef.h>

#include <raygui.h>

#include "linkedlist.h"
#include "snake.h"
#include "apple.h"
#include "grid.h"

#include "constants.h"

#define COLLECT_SOUND 0
#define EXPLOSION_SOUND 1


Snake snake;

int gameOver = 0;
int score = 0;

RandomPos applePos;
Rectangle apple;

int maxSize;
int maxSnakeSize;

Sound (*sounds);

static void resetGame(Snake *snake, GameInfo *info, MenuStates *menuState)
{
    score = 0;
    gameOver = 0;

    // reset snake by freeing and creating new snake
    snake->snakeData = clearList(&snake->snakeData);
    snake->snakeData = createSnake();

    snake->direction = RIGHT;

    // move apple for next game
    applePos = moveApple(&snake->snakeData);
    apple.x = (float)applePos.x;
    apple.y = (float)applePos.y;

    changeMenu(info, menuState, MAIN_MENU);
}


void initializeGame(Sound (*currentSounds))
{
    sounds = currentSounds;

    // Initialise SNAKE
    initializeSnake(&snake);

    maxSize = (GetScreenWidth()/ MOVE_INTERVAL) * (GetScreenHeight() / (int)MOVE_INTERVAL);
    maxSnakeSize = (score + 1 == maxSize);

    // Initialise APPLE
    applePos = moveApple(&snake.snakeData);
    apple = (Rectangle) {(float)applePos.x, (float)applePos.y, MOVE_INTERVAL, MOVE_INTERVAL}; // x, y, width, height
}


float accumulatedTime = 0.0f; // Total elapsed time
float accumulatedDebounceTime = 0.0f;
const float moveTimeInterval = 0.1f;

static void inputHandling(Snake *snake)
{
    // input checking
    if (accumulatedDebounceTime > moveTimeInterval)
    {
        accumulatedDebounceTime = 0.0f;
        if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && snake->direction != LEFT)
            snake->direction = RIGHT;
        else if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && snake->direction != RIGHT)
            snake->direction = LEFT;
        else if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && snake->direction != UP)
            snake->direction = DOWN;
        else if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && snake->direction != DOWN)
            snake->direction = UP;
    }
}

static void collisionHandling(Snake *snake)
{
    // if the apple is overlapping head.
    const int appleOverlapSnakeX = snake->snakeData.head->snake_node.x == apple.x;
    const int appleOverlapSnakeY = snake->snakeData.head->snake_node.y == apple.y;

    if (appleOverlapSnakeX && appleOverlapSnakeY)
    {
        PlaySound(sounds[COLLECT_SOUND]);
        score += 1;
        growSnake(&snake->snakeData);

        // new apple pos
        applePos = moveApple(&snake->snakeData);

        // move the apple
        apple.x = (float)applePos.x;
        apple.y = (float)applePos.y;

    }
}

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

static void drawSnake(Snake *snake)
{
    drawTails(snake);
    drawHead(snake);
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

static void handleSnake(void)
{
    inputHandling(&snake);
    updateSnakePosition(&snake);
    collisionHandling(&snake);
}


void updateGameMenu(GameInfo *gameInfo, MenuStates *menuState)
{
    const float deltaTime = GetFrameTime(); // Time since last frame
    accumulatedTime += deltaTime;     // Add to total
    accumulatedDebounceTime += deltaTime;

    if (maxSnakeSize)
    {
        gameOver = 1;
    }

    if (!gameOver) {
        handleSnake();
    }
}


static void drawGameOverMenu(GameInfo *gameInfo, MenuStates *menuState)
{
    const float buttonWidth = 100;
    const float buttonHeight = 50;
    const float gameOverButtonX = ((float) GetScreenWidth() - buttonWidth) / 2;
    const float gameOverButtonY = ((float) GetScreenHeight() - buttonHeight) / 2;
    const Rectangle gameOverButton = {gameOverButtonX,gameOverButtonY,buttonWidth,buttonHeight};

    if (GuiButton(gameOverButton, "Reset"))
    {
        resetGame(&snake, gameInfo, menuState);
    }
}


void drawGame(GameInfo *gameInfo, MenuStates *menuState)
{
    drawGrid();
    drawSnake(&snake);
    drawApple(&apple);

    DrawText(TextFormat("Score: %0i", score), 0, 0, 50, BLACK);

    if (gameOver)
    {
        drawGameOverMenu(gameInfo, menuState);
    }
}

void CleanUpGame(void)
{
    freeLinkedList(&snake.snakeData);
}

