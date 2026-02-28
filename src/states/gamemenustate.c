#include "states/gamemenustate.h"

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

#include <raygui.h>

#include "linkedlist.h"
#include "snake.h"
#include "apple.h"
#include "grid.h"

#include "constants.h"

Snake snake;

bool gameOver = false;
int score = 0;

RandomPos applePos;
Rectangle apple;

int maxSize;

static void resetGame(Snake *snake, GameInfo *info, MenuStates *menuState)
{
    score = 0;
    gameOver = false;

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


void InitializeGame(void)
{

    // Initialise SNAKE
    initializeSnake(&snake);

    maxSize = (GetScreenWidth()/ MOVE_INTERVAL) * (GetScreenHeight() / (int)MOVE_INTERVAL);

    // Initialise APPLE
    applePos = moveApple(&snake.snakeData);
    apple = (Rectangle) {(float)applePos.x, (float)applePos.y, MOVE_INTERVAL, MOVE_INTERVAL}; // x, y, width, height
}

void incrementScore(void)
{
    score++;
}

void updateGameMenu(const float deltaTime, GameInfo *gameInfo, MenuStates *menuState)
{
    const bool maxSnakeSize = maxSize == score + 1;
    if (maxSnakeSize)
    {
        gameOver = true;
    }

    if (!gameOver)
    {
        handleSnake(deltaTime, &snake, &apple);
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

void UnloadGameState(void)
{
    freeLinkedList(&snake.snakeData);
}

