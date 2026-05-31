#include "states/gamestate.h"
#include "states.h"

#include <stdbool.h>

#include <raylib.h>
#include <raygui.h>

#include "grid.h"
#include "snake.h"
#include "apple.h"
#include "collision.h"

#include "events.h"

#include "constants.h"

//----------------------------------------------------------------------------------
// Module Local Variables
//----------------------------------------------------------------------------------
static bool finishState = false;

static GameState gameState =
{
    .apple = {0},
    .snake = {0},
    .maxSnakeSize = 0,
    .score = 0,
    .gameOver = false
};

//----------------------------------------------------------------------------------
// Initialise Functions
//----------------------------------------------------------------------------------
void initializeGameState(void)
{
    finishState = false;

    gameState.score = 0;
    gameState.gameOver = false;

    // Initialise SNAKE
    initializeSnake(&gameState.snake);
    gameState.maxSnakeSize = (GetScreenWidth()/ MOVE_INTERVAL) * (GetScreenHeight() / MOVE_INTERVAL);

    // Initialise APPLE
    initialiseApple(&gameState.apple);
    moveApple(&gameState.apple, &gameState.snake.snakeData);
}

void unloadGameState(void)
{
    cleanUpSnake(&gameState.snake);
}

bool finishGameState(void)
{
    return finishState;
}

//----------------------------------------------------------------------------------
// Logic Functions
//----------------------------------------------------------------------------------
void incrementScore(void)
{
    gameState.score++;
}

void gameOver(void)
{
    gameState.gameOver = true;
}

bool isGameOver(void)
{
    return gameState.gameOver;
}

void updateGameState(const float deltaTime)
{
    if (gameState.snake.length == gameState.maxSnakeSize)
    {
        gameState.gameOver = true;
    }

    if (!gameState.gameOver)
    {
        handleApple(&gameState.apple);
        handleSnake(deltaTime, &gameState.snake);
        resolveSnakeAppleCollisions(&gameState.snake, &gameState.apple);
    }
}

//----------------------------------------------------------------------------------
// Draw Functions
//----------------------------------------------------------------------------------
static void drawGameOverMenu(void)
{
    const float buttonWidth = 100.0f;
    const float buttonHeight = 50.0f;
    const float gameOverButtonX = ((float) GetScreenWidth() - buttonWidth) / 2.0f;
    const float gameOverButtonY = ((float) GetScreenHeight() - buttonHeight) / 2.0f;

    const Rectangle gameOverButton = {
            .x = gameOverButtonX,
            .y =gameOverButtonY,
            .width =buttonWidth,
            .height = buttonHeight
    };

    if (GuiButton(gameOverButton, "Reset"))
    {
       finishState = true;
    }
}

void drawGameState(void)
{
    drawGrid();
    drawSnake(&gameState.snake);
    drawApple(&gameState.apple);

    DrawText(TextFormat("Score: %0i", gameState.score), 0, 0, 50, BLACK);

    if (gameState.gameOver)
    {
        drawGameOverMenu();
    }
}

