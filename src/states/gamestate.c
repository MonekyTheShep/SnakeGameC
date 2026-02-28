#include "states/gamestate.h"

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
int maxSize;
Apple apple;

bool gameOver = false;
int score = 0;


static void resetGame(GameInfo *info, MenuStates *menuState)
{
    score = 0;
    gameOver = false;

    // reset snake by freeing and creating new snake
    snake.snakeData = clearList(&snake.snakeData);
    snake.snakeData = createSnake();
    snake.direction = RIGHT;

    // move apple for next game
    moveApple(&apple, &snake.snakeData);

    changeMenu(info, menuState, TITLE_STATE);
}


void InitializeGameState(void)
{
    // Initialise SNAKE
    initializeSnake(&snake);
    maxSize = (GetScreenWidth()/ MOVE_INTERVAL) * (GetScreenHeight() / (int)MOVE_INTERVAL);

    // Initialise APPLE
    initialiseApple(&apple);
    moveApple(&apple, &snake.snakeData);
}

void incrementScore(void)
{
    score++;
}

void updateGameState(const float deltaTime, GameInfo *gameInfo, MenuStates *menuState)
{
    const bool maxSnakeSize = maxSize == score + 1;
    if (maxSnakeSize)
    {
        gameOver = true;
    }

    if (!gameOver)
    {
        handleApple(&apple);
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
        resetGame(gameInfo, menuState);
    }
}


void drawGameState(GameInfo *gameInfo, MenuStates *menuState)
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

