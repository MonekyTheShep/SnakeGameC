#pragma once

enum MenuStates
{
    MAIN_MENU,
    GAME_MENU,
    EXIT_MENU
};

void drawMenu(const char *buttonLabels[], int numButtons, void (*buttonCallback[])(void));

