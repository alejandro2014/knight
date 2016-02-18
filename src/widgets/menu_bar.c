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

    drawMenu(screen, menuBar);
}

void drawMenu(Screen *screen, WMenuBar *menuBar) {
    SDL_Renderer *renderer = screen->renderer;
    int numOptions = 3;
    char *optionTexts[numOptions];
    optionTexts[0] = "Sub-option 1";
    optionTexts[1] = "Sub-option 2";
    optionTexts[2] = "Sub-option 3";

    int optionSelected = 1;
    int heightOption = 23;
    int xSubMenu = optionSelected * 100 + 10;
    int i;

    SDL_Rect rectMenu;
    setRect(&rectMenu, xSubMenu, 20, xSubMenu + 130, 20 + 3 * heightOption);
    clearSubScreen(renderer, &rectMenu, &(screen->bgColorMenuBar));

    for(i = 0; i < numOptions; i++) {
        //currentFont = (menuBar->options + i)->isSelected ? menuBar->fontSelected : menuBar->fontNormal;
        printString(menuBar->fontNormal, renderer, optionTexts[i], xSubMenu, i * heightOption + 25);
    }
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
