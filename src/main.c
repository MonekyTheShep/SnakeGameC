#include <stdio.h>

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "constants.h"
#include "assets.h"

#include "utility/menuutil.h"
#include "utility/gameutil.h"
#include "utility/soundutil.h"

#include "states/gamestate.h"
#include "states/titlestate.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define GAME_TITLE "Snake Game"

// default menu
MenuStates menuState = TITLE_STATE;
GameInfo gameInfo = {.musicPlaying = 0};

int main(void)
{
    // Initialise Raylib
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);
    SetTargetFPS(60);

    InitAudioDevice();
    InitializeGameState();

    // load sounds
    sounds[COLLECT_SOUND] = LoadSound(ASSETS_PATH "/sounds/collect_sound.ogg");
    sounds[EXPLOSION_SOUND] =  LoadSound(ASSETS_PATH "/sounds/explosion_sound.ogg");

    // load musics
    musics[MAIN_MENU_MUSIC] = LoadMusicStream(ASSETS_PATH "/music/main_menu.ogg");
    musics[GAME_MENU_MUSIC] = LoadMusicStream(ASSETS_PATH "/music/game_music.ogg");

    Music *currentMusic = &musics[MAIN_MENU_MUSIC];
    PlayMusicStream(*currentMusic);
    gameInfo.musicPlaying = 1;

    while (!WindowShouldClose())
    {
        if (menuState == EXIT)
        {
            break;
        }

        const float deltaTime = GetFrameTime();
        UpdateMusicStream(*currentMusic);

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

        // Update logic for each state
        switch (menuState)
        {
            case GAME_STATE:
                updateGameState(deltaTime, &gameInfo, &menuState);
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
                    drawMainState(&gameInfo, &menuState);
                    break;
                case GAME_STATE:
                    drawGameState(&gameInfo, &menuState);
                    break;
                default: break;
            }
        EndDrawing();
    }

    const int numOfSound = sizeof(sounds) / sizeof(sounds[0]);
    CleanUpSound(sounds, numOfSound);

    const int numOfMusic = sizeof(musics) / sizeof(musics[0]);
    CleanUpMusic(musics, numOfMusic);

    UnloadGameState();

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
