#pragma once
#include "linkedlist.h"
#include "gameutil.h"

enum Direction {
    UP, DOWN, LEFT, RIGHT
};

typedef struct SnakeData {
    enum Direction *direction;
    LinkedList *list;
} SnakeData;

LinkedList createSnake(void);
int growSnake(LinkedList *snake);
void storePrevSnakePosition(const LinkedList *snake);
void moveSnake(const LinkedList *snake, const SnakeData *data, int screenWidth, int screenHeight, GameInfo info);
