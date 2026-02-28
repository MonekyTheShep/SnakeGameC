#pragma once
#include "linkedlist.h"
#include "raylib.h"

typedef struct RandomPos {
    int x;
    int y;
} RandomPos;

typedef struct Apple {
    Rectangle rec;
    Vector2 position;
} Apple;

RandomPos randomApplePos(int moveInterval);

void moveApple(Apple *apple, const LinkedList *snake);

void initialiseApple(Apple *apple);
void handleApple(Apple *apple);
void drawApple(Apple *apple);
