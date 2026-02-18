#include <stdio.h>

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "utility/menuutil.h"
#include "utility/gameutil.h"
#include "utility/soundutil.h"

#include "states/gamestate.h"
#include "states/mainmenustate.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define GAME_TITLE "Snake Game"

Music musics[2];
Sound sounds[2];

int main(void)
{
    // default menu
    MenuStates menuState = MAIN_MENU;
    GameInfo gameInfo = {.musicPlaying = 0};

    // Initialise Raylib
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);
    SetTargetFPS(60);

    InitAudioDevice();

    // load sounds
    const Sound collectSound = LoadSound(ASSETS_PATH "/sounds/collect_sound.ogg");
    const Sound explosionSound = LoadSound(ASSETS_PATH "/sounds/explosion_sound.ogg");

    sounds[0] = collectSound;
    sounds[1] = explosionSound;

    initializeGame();

    // load musics
    Music mainMenuSound = LoadMusicStream(ASSETS_PATH "/music/main_menu.ogg");
    Music gameMusicSound = LoadMusicStream(ASSETS_PATH "/music/game_music.ogg");

    musics[0] = mainMenuSound;
    musics[1] = gameMusicSound;

    Music *currentMusic = &mainMenuSound;
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
                case MAIN_MENU:
                    gameInfo.musicPlaying = 1;
                    StopMusicStream(*currentMusic);
                    currentMusic = &mainMenuSound;
                    PlayMusicStream(*currentMusic);
                    break;
                case GAME_MENU:
                    gameInfo.musicPlaying = 1;
                    StopMusicStream(*currentMusic);
                    currentMusic = &gameMusicSound;
                    PlayMusicStream(*currentMusic);
                    break;

                default: break;
            }
        }

        // Update logic for each state
        switch (menuState)
        {
            case GAME_MENU:
                updateGameMenu(deltaTime, &gameInfo, &menuState);
                break;
            default:
                break;
        }

        // Draw for each state
        BeginDrawing();
            ClearBackground(WHITE);
            switch (menuState)
            {
                case MAIN_MENU:
                    drawMainMenu(&gameInfo, &menuState);
                    break;
                case GAME_MENU:
                    drawGame(&gameInfo, &menuState);
                    break;
                default: break;
            }
        EndDrawing();
    }

    const int numOfSound = sizeof(sounds) / sizeof(sounds[0]);
    CleanUpSound(sounds, numOfSound);

    const int numOfMusic = sizeof(musics) / sizeof(musics[0]);
    CleanUpMusic(musics, numOfMusic);

    CleanUpGameState();

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
