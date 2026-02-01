#pragma once
#include "raylib.h"
#include "linkedlist.h"

typedef struct RandomPos {
    int x;
    int y;
} RandomPos;


RandomPos randomApplePos(int screenWidth, int screenHeight, int moveInterval);

RandomPos moveApple(LinkedList *snake, int screenWidth, int screenHeight, int moveInterval);