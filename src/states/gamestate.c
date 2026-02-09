#include "states/gamestate.h"

#include <stddef.h>

#include <raygui.h>

#include "linkedlist.h"
#include "snake.h"
#include "apple.h"

#define MOVE_INTERVAL 50
#define COLLECT_SOUND 0
#define EXPLOSION_SOUND 1

enum Direction direction = RIGHT;

LinkedList snake;
SnakeData data = {.direction = &direction};

int gameOver = 0;
int score = 0;

Rectangle snakeHead;
RandomPos applePos;
Rectangle apple;

int maxSize;
int maxSnakeSize;

Sound (*sounds);

void resetGame(LinkedList *snake, const SnakeData *data, GameInfo *info, MenuStates *menuState)
{
    // reset snake by freeing and creating new snake
    *snake = clearList(snake);
    *snake = createSnake();

    *data->direction = RIGHT;
    score = 0;
    gameOver = 0;
    // move apple for next game
    applePos = moveApple(snake, MOVE_INTERVAL);
    apple.x = (float)applePos.x;
    apple.y = (float)applePos.y;

    changeMenu(info, menuState, MAIN_MENU);
}


void initializeGame(Sound (*currentSounds))
{
    sounds = currentSounds;

    // Initialise SNAKE
    snakeHead = (Rectangle) {0, 0, MOVE_INTERVAL, MOVE_INTERVAL}; // x, y, width, height
    snake = createSnake();

    maxSize = (GetScreenWidth()/ MOVE_INTERVAL) * (GetScreenHeight() / (int)MOVE_INTERVAL);
    maxSnakeSize = (score + 1 == maxSize);

    // Initialise APPLE
    applePos = moveApple(&snake, MOVE_INTERVAL);
    apple = (Rectangle) {(float)applePos.x, (float)applePos.y, MOVE_INTERVAL, MOVE_INTERVAL}; // x, y, width, height
}


float accumulatedTime = 0.0f; // Total elapsed time
float accumulatedDebounceTime = 0.0f;
const float moveTimeInterval = 0.1f;

static void inputHandling(void)
{
    // input checking
    if (accumulatedDebounceTime > moveTimeInterval && !gameOver)
    {
        accumulatedDebounceTime = 0.0f;
        if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && direction != LEFT)
            direction = RIGHT;
        else if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && direction != RIGHT)
            direction = LEFT;
        else if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && direction != UP)
            direction = DOWN;
        else if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && direction != DOWN)
            direction = UP;
    }
}

static void collisionHandling(void)
{
    // if the apple is overlapping head.
    const int appleOverlapSnakeX = snake.head->snake_node.x == apple.x;
    const int appleOverlapSnakeY = snake.head->snake_node.y == apple.y;

    if (appleOverlapSnakeX && appleOverlapSnakeY && !gameOver)
    {
        PlaySound(sounds[COLLECT_SOUND]);
        score += 1;
        growSnake(&snake);

        // new apple pos
        applePos = moveApple(&snake, MOVE_INTERVAL);

        // move the apple
        apple.x = (float)applePos.x;
        apple.y = (float)applePos.y;

    }
}

static void drawTails(void)
{
    // prev pos stored after the head position
    Node *temp = snake.head->next;
    int length = 0;

    // move tail to previous positions and check if those tails are touching head
    while (temp != NULL)
    {
        length++;

        Rectangle tail = {(float)temp->snake_node.x, (float)temp->snake_node.y, MOVE_INTERVAL, MOVE_INTERVAL};
        DrawRectangleRec(tail, GREEN);

        const int tailOverlapHeadX = temp->snake_node.x == snake.head->snake_node.x;
        const int tailOverlapHeadY = temp->snake_node.y == snake.head->snake_node.y;
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

static void drawSnake(void)
{
    drawTails();

    DrawRectangleRec(apple, RED);
    DrawRectangleRec(snakeHead, DARKGREEN);
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
        resetGame(&snake, &data, gameInfo, menuState);
        applePos = moveApple(&snake, MOVE_INTERVAL);
        apple.x = (float)applePos.x;
        apple.y = (float)applePos.y;
    }
}


static void handleSnake(void)
{
    inputHandling();

    // store prev position
    int beenTimeInterval = accumulatedTime > moveTimeInterval;
    if (beenTimeInterval && !gameOver)
    {
        accumulatedTime = 0.0f;
        storePrevSnakePosition(&snake);
        moveSnake(&snake, &data, MOVE_INTERVAL);
    }

    // move the snake head rectangle
    snakeHead.x = snake.head->snake_node.x;
    snakeHead.y = snake.head->snake_node.y;

    collisionHandling();
}


void updateGameMenu(GameInfo *gameInfo, MenuStates *menuState)
{
    float deltaTime = GetFrameTime(); // Time since last frame
    accumulatedTime += deltaTime;     // Add to total
    accumulatedDebounceTime += deltaTime;

    if (maxSnakeSize)
    {
        gameOver = 1;
    }

    handleSnake();

    BeginDrawing();
            ClearBackground(RAYWHITE);

            drawSnake();
            DrawText(TextFormat("Score: %0i", score), 0, 0, 50, BLACK);

            if (gameOver)
            {
                drawGameOverMenu(gameInfo, menuState);
            }

    EndDrawing();
}

void CleanUpGame(void)
{
    freeLinkedList(&snake);
}

