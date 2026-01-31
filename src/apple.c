#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "apple.h"

Apple *initApple() {
    Apple *apple = malloc(sizeof(Apple));
    if (apple == NULL)
    {
        fprintf(stderr, "Memory Allocation failed");
        return NULL;
    }
    return apple;
}

Apple *moveApple(Apple *apple) {
    return NULL;
}

RandomPos randomApplePos(int screenHeight, int screenWidth, int moveInterval) {

    int xCount = screenWidth / moveInterval;
    int Xindex = rand() % xCount;

    int yCount = screenHeight / moveInterval;
    int yIndex = rand() % yCount;

    return (RandomPos){Xindex * moveInterval, yIndex * moveInterval};
};