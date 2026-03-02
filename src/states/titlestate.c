#include "states/titlestate.h"

#include <raylib.h>
#include <raygui.h>

#include "states.h"

//----------------------------------------------------------------------------------
// Module Local Variables
//----------------------------------------------------------------------------------
static bool finishState = false;
static bool exitAllState = false;

//----------------------------------------------------------------------------------
// Initialise Functions
//----------------------------------------------------------------------------------
void initializeTitleState(void)
{
    finishState = false;
}

bool finishTitleState(void)
{
    return finishState;
}

bool exitState(void)
{
    return exitAllState;
}

void unloadTitleState(void)
{

}

//----------------------------------------------------------------------------------
// Logic Functions
//----------------------------------------------------------------------------------
static void buttonMenuCallback(int buttonIndex)
{
    switch (buttonIndex)
    {
        case 0:
            finishState = true;
            break;
        case 1:
            exitAllState = true;
            break;
        default: break;
    }
}

void updateTitleState(void)
{

}

//----------------------------------------------------------------------------------
// Draw Functions
//----------------------------------------------------------------------------------
static void drawTitle(void)
{
    // Draw the title
    const char titleText[11] = "Snake Game";

    const Font font = GetFontDefault();
    const float fontSize = 50.0f;

    const Vector2 size = MeasureTextEx(font, titleText, fontSize, 0.0f);

    const float textXCenter = ((float)GetScreenWidth() - size.x) / 2.0f;
    const float textYCenter = ((float)GetScreenHeight() - size.y) / 2.0f;
    const float offsetY = -50.0f;

    DrawTextEx(font, titleText, (Vector2){textXCenter, textYCenter + offsetY}, fontSize, 1.0f, BLACK);
}


static void drawMenu(const char *buttonLabels[], const int numButtons, void (*buttonCallback)(int))
{
    // Button information
    const float buttonWidth = 100.0f;
    const float buttonHeight = 50.0f;
    const float buttonGap = 10.0f;

    // Calculate button position
    const float buttonCenterX = ((float) GetScreenWidth() - buttonWidth) / 2.0f;
    const float buttonCenterY = ((float) GetScreenHeight() - buttonHeight) / 2.0f;

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
            buttonCallback(i);
        }
    }
}

void drawTitleState(void)
{
    // Draw the title
    drawTitle();

    // Draw the buttons
    const char *buttonLabels[] = {"Start", "Exit"};
    const char numOfButtons = sizeof(buttonLabels) / sizeof(buttonLabels[0]);

    drawMenu(buttonLabels, numOfButtons, buttonMenuCallback);
}
