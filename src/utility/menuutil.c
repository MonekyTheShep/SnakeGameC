#include <utility/menuutil.h>

#include "raygui.h"
#include "raylib.h"

void changeMenu(GameInfo *info, MenuStates *currentState, const MenuStates changeState)
{
    *currentState = changeState;
    info->musicPlaying = 0;
}

void drawMenu(const char *buttonLabels[], const int numButtons, GameInfo *info, MenuStates *menuState, void (*buttonCallback[])(GameInfo*, MenuStates*))
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
            buttonCallback[i](info, menuState);
        }
    }
}
