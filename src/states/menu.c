#include "raylib.h"

#include "states/menu.h"
#include "utility/menuutil.h"
#include  "utility/gameutil.h"

void buttonStart(GameInfo *gameInfo, enum MenuStates *menuState) {
    changeMenu(gameInfo, menuState, GAME_MENU);
}

void buttonExit(GameInfo *gameInfo, enum MenuStates *menuState) {
    changeMenu(gameInfo, menuState, EXIT_MENU);
}


void drawTitle(void) {
    // Draw the title
    const char titleText[11] = "Snake Game";

    const Font font = GetFontDefault();
    const float fontSize = 50;

    const Vector2 size = MeasureTextEx(font, titleText, fontSize, 0);

    const float textXCenter = ((float)GetScreenWidth() - size.x) / 2;
    const float textYCenter = ((float)GetScreenHeight() - size.y) / 2;
    const float offsetY = -50;

    DrawTextEx(font, titleText, (Vector2){textXCenter, textYCenter + offsetY}, fontSize, 1, BLACK);
}

void updateMainMenu(GameInfo *gameInfo, MenuStates *menuState) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    // Draw the title
    drawTitle();

    // Draw the buttons
    const char *buttonLabels[] = {"Start", "End"};
    const char numOfButtons = sizeof(buttonLabels) / sizeof(buttonLabels[0]);

    void (*buttonCallbacks[2])(GameInfo*, enum MenuStates*) = {buttonStart, buttonExit};
    drawMenu(buttonLabels, numOfButtons, gameInfo, menuState, buttonCallbacks);
    EndDrawing();
}
