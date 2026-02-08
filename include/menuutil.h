#pragma once
#include "raylib.h"

void drawMenu(float screenWidth, float screenHeight, const char *buttonLabels[], int numButtons, void (*buttonCallback[])(void));
