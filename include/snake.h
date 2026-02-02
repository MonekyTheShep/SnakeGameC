#pragma once
#include "linkedlist.h"


enum Direction {
    UP, DOWN, LEFT, RIGHT
};

typedef struct SnakeData {
    enum Direction *direction;
    LinkedList *list;
    float moveInterval;
} SnakeData;

LinkedList createSnake(void);
int growSnake(LinkedList *snake);
void moveSnake(LinkedList *snake, SnakeData *data, int screenWidth, int screenHeight);
