#pragma once
#include "linkedlist.h"
#include "raylib.h"

typedef struct RandomPos {
    int x;
    int y;
} RandomPos;

typedef struct Apple {
    Rectangle apple;
    Vector2 position;
} Apple;

RandomPos randomApplePos(int moveInterval);

RandomPos moveApple(const LinkedList *snake);

void drawApple(Rectangle *apple);
