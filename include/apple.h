#pragma once
#include "linkedlist.h"

typedef struct RandomPos {
    int x;
    int y;
} RandomPos;


RandomPos randomApplePos(int moveInterval);

RandomPos moveApple(const LinkedList *snake, int moveInterval);
