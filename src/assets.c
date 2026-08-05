#include "assets.h"

#include "raylib.h"

#include "utility/soundutil.h"

//----------------------------------------------------------------------------------
// Global Asset Variables
//----------------------------------------------------------------------------------
Music musics[NUM_OF_MUSICS];
Sound sounds[NUM_OF_SOUNDS];

void initAssets(void)
{
    // load sounds
    sounds[COLLECT_SOUND] = LoadSound(ASSETS_PATH "/sounds/collect_sound.ogg");
    sounds[EXPLOSION_SOUND] = LoadSound(ASSETS_PATH "/sounds/explosion_sound.ogg");

    // load musics
    musics[MAIN_MENU_MUSIC] = LoadMusicStream(ASSETS_PATH "/music/main_menu.ogg");
    musics[GAME_MENU_MUSIC] = LoadMusicStream(ASSETS_PATH "/music/game_music.ogg");
}

void cleanUpAssets(void)
{
    cleanUpSound(sounds, NUM_OF_SOUNDS);
    cleanUpMusic(musics, NUM_OF_MUSICS);
}