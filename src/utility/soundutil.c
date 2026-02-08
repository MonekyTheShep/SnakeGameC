#include <utility/soundutil.h>

void cleanUpSound(const Sound *sounds, const int numOfSounds) {
    // unload all sounds in array of Sound

    for (int i = 0; i < numOfSounds; i++)
    {
        UnloadSound(sounds[i]);
    }
}

void cleanUpMusic(const Music *musics, const int numOfMusic) {
    // unload all sounds in array of Sound
    for (int i = 0; i < numOfMusic; i++)
    {
        UnloadMusicStream(musics[i]);
    }
}