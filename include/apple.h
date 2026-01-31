#pragma once

typedef struct Apple {
    float x;
    float y;
} Apple;

typedef struct RandomPos {
    int x;
    int y;
} RandomPos;

Apple *initApple();
Apple *moveApple(Apple *apple);
RandomPos randomApplePos(int screenHeight, int screenWidth, int moveInterval);