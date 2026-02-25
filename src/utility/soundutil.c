#include <utility/soundutil.h>
#include "constants.h"

void CleanUpSound(const Sound *sounds, const int numOfSounds)
{
    // unload all sounds in array of Sound

    for (int i = 0; i < numOfSounds; i++)
    {
        UnloadSound(sounds[i]);
    }
}

void CleanUpMusic(const Music *musics, const int numOfMusic)
{
    // unload all sounds in array of Sound
    for (int i = 0; i < numOfMusic; i++)
    {
        UnloadMusicStream(musics[i]);
    }
}

void changeMusic(Music **currentMusic, const int musicIndex, Music *musics, GameInfo *gameInfo)
{
    gameInfo->musicPlaying = 1;
    StopMusicStream(**currentMusic);
    *currentMusic = &musics[musicIndex];
    PlayMusicStream(**currentMusic);
}
