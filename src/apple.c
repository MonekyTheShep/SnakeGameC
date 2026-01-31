#include <stdlib.h>

#include "apple.h"


RandomPos randomApplePos(int screenHeight, int screenWidth, int moveInterval) {

    int xCount = screenWidth / moveInterval;
    int xIndex = rand() % xCount;

    int yCount = screenHeight / moveInterval;
    int yIndex = rand() % yCount;

    return (RandomPos){xIndex * moveInterval, yIndex * moveInterval};
};