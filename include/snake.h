#pragma once
#include "linkedlist.h"
#include "utility/gameutil.h"

enum Direction {
    UP, DOWN, LEFT, RIGHT
};

typedef struct SnakeData {
    enum Direction *direction;
} SnakeData;

LinkedList createSnake(void);
int growSnake(LinkedList *snake);
void storePrevSnakePosition(const LinkedList *snake);
void moveSnake(const LinkedList *snake, const SnakeData *data, GameInfo gameInfo);
