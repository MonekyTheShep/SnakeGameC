#include <stdio.h>

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "constants.h"
#include "assets.h"

#include "utility/gameutil.h"
#include "utility/soundutil.h"

#include "states.h"

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (600)
#define GAME_TITLE ("Snake Game")

//----------------------------------------------------------------------------------
// Main Module Variables
//----------------------------------------------------------------------------------
States menuState = TITLE_STATE;
GameInfo gameInfo = {.musicPlaying = 0};
Music *currentMusic;

//----------------------------------------------------------------------------------
// Function Prototypes
//----------------------------------------------------------------------------------
static void changeState(States changeState);
static void checkMusicStatus(void);
static void updateDrawFrame(void);

int main(void)
{
    // Initialise Raylib
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);
    SetTargetFPS(60);

    InitAudioDevice();

    initializeTitleState();

    // load sounds
    sounds[COLLECT_SOUND] = LoadSound(ASSETS_PATH "/sounds/collect_sound.ogg");
    sounds[EXPLOSION_SOUND] =  LoadSound(ASSETS_PATH "/sounds/explosion_sound.ogg");

    // load musics
    musics[MAIN_MENU_MUSIC] = LoadMusicStream(ASSETS_PATH "/music/main_menu.ogg");
    musics[GAME_MENU_MUSIC] = LoadMusicStream(ASSETS_PATH "/music/game_music.ogg");

    currentMusic = &musics[MAIN_MENU_MUSIC];
    PlayMusicStream(*currentMusic);
    gameInfo.musicPlaying = 1;

    while (!WindowShouldClose())
    {
        if (menuState == EXIT)
        {
            break;
        }

        checkMusicStatus();
        updateDrawFrame();
    }

    // Unload Current State before closing window.
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

    const int numOfSound = sizeof(sounds) / sizeof(sounds[0]);
    cleanUpSound(sounds, numOfSound);

    const int numOfMusic = sizeof(musics) / sizeof(musics[0]);
    cleanUpMusic(musics, numOfMusic);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}

//----------------------------------------------------------------------------------
// Function Implementation
//----------------------------------------------------------------------------------
static void changeState(States changeState)
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

    switch (changeState)
    {
        case TITLE_STATE:
            initializeTitleState();
            break;
        case GAME_STATE:
            initializeGameState();
        default:
            break;
    }

    gameInfo.musicPlaying = 0;
    menuState = changeState;
}

static void checkMusicStatus(void)
{
    // music management
    if (!gameInfo.musicPlaying)
    {
        switch (menuState)
        {
            case TITLE_STATE:
                changeMusic(&currentMusic, MAIN_MENU_MUSIC, musics, &gameInfo);
                break;
            case GAME_STATE:
                changeMusic(&currentMusic, GAME_MENU_MUSIC, musics, &gameInfo);
                break;

            default: break;
        }
    }
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
