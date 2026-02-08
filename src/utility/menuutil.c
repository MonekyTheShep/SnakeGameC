#include <utility/menuutil.h>

#include <stdio.h>

#include "raygui.h"
#include "raylib.h"


void drawMenu(const char *buttonLabels[], const int numButtons, void (*buttonCallback[])(void)) {
    // Button information
    const float buttonWidth = 100;
    const float buttonHeight = 50;
    const float buttonGap = 10;

    // Calculate button position
    const float buttonCenterX = ((float) GetScreenWidth() - buttonWidth) / 2;
    const float buttonCenterY = ((float) GetScreenHeight() - buttonHeight) / 2;

    // Create buttons
    for (int i = 0; i < numButtons; i++) {
        // calculate where button is placed
        const float buttonYOffset = (float) i * (buttonHeight + buttonGap);

        const float currentButtonX = buttonCenterX;
        const float currentButtonY = buttonCenterY + buttonYOffset;

        Rectangle button = { currentButtonX, currentButtonY , buttonWidth , buttonHeight };
        if (GuiButton(button, buttonLabels[i])) {
            printf("%d", i);
            buttonCallback[i]();
        }
    }
}
