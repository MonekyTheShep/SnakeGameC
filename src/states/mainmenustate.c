#include "states/mainmenustate.h"

#include <raylib.h>
#include <raygui.h>

#include "utility/menuutil.h"
#include  "utility/gameutil.h"

static void buttonMenuCallback(int buttonIndex, GameInfo *gameInfo, MenuStates *menuState) {
    switch (buttonIndex) {
        case 0:
            changeMenu(gameInfo, menuState, GAME_MENU);
            break;
        case 1:
            changeMenu(gameInfo, menuState, EXIT);
            break;
        default: break;
    }
}

static void drawTitle(void)
{
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


static void drawMenu(const char *buttonLabels[], const int numButtons, GameInfo *info, MenuStates *menuState, void (*buttonCallback)(int, GameInfo*, MenuStates*))
{
    // Button information
    const float buttonWidth = 100;
    const float buttonHeight = 50;
    const float buttonGap = 10;

    // Calculate button position
    const float buttonCenterX = ((float) GetScreenWidth() - buttonWidth) / 2;
    const float buttonCenterY = ((float) GetScreenHeight() - buttonHeight) / 2;

    // Create buttons
    for (int i = 0; i < numButtons; i++)
    {
        // calculate where button is placed
        const float buttonYOffset = (float) i * (buttonHeight + buttonGap);

        const float currentButtonX = buttonCenterX;
        const float currentButtonY = buttonCenterY + buttonYOffset;

        const Rectangle button = { currentButtonX, currentButtonY , buttonWidth , buttonHeight };
        if (GuiButton(button, buttonLabels[i]))
        {
            buttonCallback(i, info, menuState);
        }
    }
}

void updateMainMenu(GameInfo *gameInfo, MenuStates *menuState)
{
    BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the title
        drawTitle();

        // Draw the buttons
        const char *buttonLabels[] = {"Start", "Exit"};
        const char numOfButtons = sizeof(buttonLabels) / sizeof(buttonLabels[0]);

        drawMenu(buttonLabels, numOfButtons, gameInfo, menuState, buttonMenuCallback);
    EndDrawing();
}
