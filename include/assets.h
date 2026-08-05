#pragma once

#include "raylib.h"

//----------------------------------------------------------------------------------
// Global Asset Variables
//----------------------------------------------------------------------------------
enum Sounds
{
    COLLECT_SOUND = 0,
    EXPLOSION_SOUND,
    NUM_OF_SOUNDS
};

enum Musics
{
    MAIN_MENU_MUSIC = 0,
    GAME_MENU_MUSIC,
    NUM_OF_MUSICS
};

extern Music musics[NUM_OF_MUSICS];
extern Sound sounds[NUM_OF_SOUNDS];
