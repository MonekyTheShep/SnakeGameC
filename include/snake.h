#pragma once
#include "linkedlist.h"

enum Direction {
    UP, DOWN, LEFT, RIGHT
};

typedef struct SnakeData {
    enum Direction *direction;
    LinkedList *list;
    const float *moveInterval;

} SnakeData;

LinkedList createSnake(void);
int growSnake(LinkedList *snake);
