#include "menuutil.h"
#include "raygui.h"
#include "stdio.h"

void drawMenu(const float screenWidth, const float screenHeight, const char *buttonLabels[], const int numButtons, void (*buttonCallback[])(void)) {
    // Button information
    const float buttonWidth = 100;
    const float buttonHeight = 50;
    const float buttonGap = 10;

    // Calculate button position
    const float buttonCenterX = (screenWidth - buttonWidth) / 2;
    const float buttonCenterY = (screenHeight - buttonHeight) / 2;

    // Create buttons
    for (int i = 0; i < numButtons; i++) {
        // calculate where button is placed
        float buttonYOffset = (float) i * (buttonHeight + buttonGap);

        float currentButtonX = buttonCenterX;
        float currentButtonY = buttonCenterY + buttonYOffset;

        Rectangle button = { currentButtonX, currentButtonY , buttonWidth , buttonHeight };
        if (GuiButton(button, buttonLabels[i])) {
            printf("%d", i);
            buttonCallback[i]();
        }
    }
}
