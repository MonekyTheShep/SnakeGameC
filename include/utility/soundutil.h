#pragma once
#include "raylib.h"
#include "gameutil.h"

void CleanUpSound(const Sound *sounds, int numOfSounds);

void CleanUpMusic(const Music *musics, int numOfMusic);

void changeMusic(Music **currentMusic, int musicIndex, Music *musics, GameInfo *gameInfo);
