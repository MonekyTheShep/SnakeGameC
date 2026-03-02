#pragma once
#include "raylib.h"
#include "gameutil.h"

void cleanUpSound(const Sound *sounds, int numOfSounds);

void cleanUpMusic(const Music *musics, int numOfMusic);

void changeMusic(Music **currentMusic, int musicIndex, Music *musics, GameInfo *gameInfo);
