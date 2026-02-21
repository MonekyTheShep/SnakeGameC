#include <stdio.h>

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "constants.h"
#include "utility/menuutil.h"
#include "utility/gameutil.h"
#include "utility/soundutil.h"

#include "states/gamemenustate.h"
#include "states/mainmenustate.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define GAME_TITLE "Snake Game"

Music musics[NUM_OF_MUSICS];
Sound sounds[NUM_OF_SOUNDS];

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

    sounds[COLLECT_SOUND] = collectSound;
    sounds[EXPLOSION_SOUND] = explosionSound;

    initializeGame();

    // load musics
    Music mainMenuMusic = LoadMusicStream(ASSETS_PATH "/music/main_menu.ogg");
    Music gameMenuMusic = LoadMusicStream(ASSETS_PATH "/music/game_music.ogg");

    musics[MAIN_MENU_MUSIC] = mainMenuMusic;
    musics[GAME_MENU_MUSIC] = gameMenuMusic;

    Music *currentMusic = &mainMenuMusic;
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
                    currentMusic = &mainMenuMusic;
                    PlayMusicStream(*currentMusic);
                    break;
                case GAME_MENU:
                    gameInfo.musicPlaying = 1;
                    StopMusicStream(*currentMusic);
                    currentMusic = &gameMenuMusic;
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
