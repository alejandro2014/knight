#include <stdlib.h>
#include <string.h>

#include "menu_bar.h"

#include "../global.h"
#include "../draw.h"

void drawMenuBar(WMenuBar *menuBar, Screen *screen) {
    Font *currentFont = NULL;
    SDL_Renderer *renderer = screen->renderer;
    int i;

    clearSubScreen(renderer, &(screen->menuBarCoords), &(screen->bgColorMenuBar));

    for(i = 0; i < menuBar->numOptions; i++) {
        currentFont = (menuBar->options + i)->isSelected ? menuBar->fontSelected : menuBar->fontNormal;
        printString(currentFont, renderer, (menuBar->options + i)->text, i * 100 + 10, 2);
    }

    SDL_Rect rectMenu;
    setRect(&rectMenu, 1 * 100 + 10, 20, 1 * 100 + 140, 90);
    clearSubScreen(renderer, &rectMenu, &(screen->bgColorMenuBar));

    printString(menuBar->fontNormal, renderer, "Sub-option 1", 1 * 100 + 10, 25);
    printString(menuBar->fontNormal, renderer, "Sub-option 2", 1 * 100 + 10, 47);
    printString(menuBar->fontNormal, renderer, "Sub-option 3", 1 * 100 + 10, 69);
}

WMenuBar *loadMenuBar(SDL_Color *bgColor) {
    WMenuBarOption *option = NULL;
    alloc(menuBar, WMenuBar, 1);

    menuBar->numOptions = 3;
    allocExist(menuBar->options, WMenuBarOption, menuBar->numOptions);

    addNewOption((menuBar->options + 0), "Option 1", false);
    addNewOption((menuBar->options + 1), "Option 2", true);
    addNewOption((menuBar->options + 2), "Option 3", false);

    SDL_Color fgColor = {160, 160, 40};
    menuBar->fontNormal = loadFont(FONT_PATH_MAC, 16, &fgColor, bgColor);
    menuBar->fontSelected = loadFont(FONT_PATH_MAC, 16, bgColor, &fgColor);

    return menuBar;
}

void addNewOption(WMenuBarOption *option, char *text, bool isSelected) {
    allocExist(option->text, char, 20);
    strcpy(option->text, text);
    option->isSelected = isSelected;
}
