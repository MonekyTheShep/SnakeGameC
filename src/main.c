#include <stdio.h>

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "constants.h"
#include "assets.h"

#include "utility/soundutil.h"

#include "states.h"

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (600)
#define GAME_TITLE ("Snake Game")

//----------------------------------------------------------------------------------
// Main Module Variables
//----------------------------------------------------------------------------------
States menuState = TITLE_STATE;
Music *currentMusic = NULL;

//----------------------------------------------------------------------------------
// Function Prototypes
//----------------------------------------------------------------------------------
static void unloadCurrentState(void);
static void changeState(States changeState);
static void updateDrawFrame(void);
static void changeMusic(const int musicIndex);

int main(void)
{
    // Initialise Raylib
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);
    SetTargetFPS(60);

    InitAudioDevice();

    initAssets();
    initializeTitleState();
    changeMusic(MAIN_MENU_MUSIC);

    while (!WindowShouldClose())
    {
        if (menuState == EXIT)
        {
            break;
        }

        updateDrawFrame();
    }
    unloadCurrentState();

    cleanUpAssets();
    CloseAudioDevice();
    CloseWindow();

    return 0;
}

//----------------------------------------------------------------------------------
// Function Implementation
//----------------------------------------------------------------------------------
static void changeMusic(const int musicIndex)
{
    if (currentMusic) StopMusicStream(*currentMusic);
    currentMusic = &musics[musicIndex];
    PlayMusicStream(*currentMusic);
}

static void unloadCurrentState(void)
{
    switch (menuState)
    {
        case TITLE_STATE:
            unloadTitleState();
            break;
        case GAME_STATE:
            unloadGameState();
            break;
        default:
            break;
    }
}

static void changeState(States changeState)
{
    unloadCurrentState();

    switch (changeState)
    {
        case TITLE_STATE:
            initializeTitleState();
            changeMusic(MAIN_MENU_MUSIC);
            break;
        case GAME_STATE:
            initializeGameState();
            changeMusic(GAME_MENU_MUSIC);
        default:
            break;
    }

    menuState = changeState;
}

static void updateDrawFrame(void)
{
    const float deltaTime = GetFrameTime();
    UpdateMusicStream(*currentMusic);

    // Update logic for each state
    switch (menuState)
    {
        case TITLE_STATE:
            updateTitleState();
            if (finishTitleState()) changeState(GAME_STATE);
            if (exitState()) changeState(EXIT);
            break;
        case GAME_STATE:
            updateGameState(deltaTime);
            if (finishGameState()) changeState(TITLE_STATE);
            break;
        default:
            break;
    }

    // Draw for each state
    BeginDrawing();
    ClearBackground(WHITE);
    switch (menuState)
    {
        case TITLE_STATE:
            drawTitleState();
            break;
        case GAME_STATE:
            drawGameState();
            break;
        default: break;
    }
    EndDrawing();
}
