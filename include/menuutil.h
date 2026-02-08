#pragma once
#include "raylib.h"

void drawMenu(float screenWidth, float screenHeight, char *buttonLabels[], int numButtons, void (*buttonCallback[])(void));
