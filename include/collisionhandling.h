#pragma once

#include "apple.h"
#include "snake.h"

void moveApple(Apple *apple, const LinkedList *snake);
void collisionHandling(Snake *snake, Apple *apple);
