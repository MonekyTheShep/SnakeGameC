#pragma once

typedef struct RandomPos {
    int x;
    int y;
} RandomPos;


RandomPos randomApplePos(int screenHeight, int screenWidth, int moveInterval);