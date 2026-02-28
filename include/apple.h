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


// Apple Initialising
void initialiseApple(Apple *apple);

// Apple Handling
RandomPos randomApplePos(int moveInterval);
void moveApple(Apple *apple, const LinkedList *snake);
void handleApple(Apple *apple);

// Draw Functions
void drawApple(Apple *apple);
