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
}

WMenuBar *loadMenuBar(SDL_Color *bgColor) {
    WMenuBarOption *option = NULL;
    alloc(menuBar, WMenuBar, 1);

    menuBar->numOptions = 3;
    allocExist(menuBar->options, WMenuBarOption, menuBar->numOptions);

    option = (menuBar->options + 0);
    allocExist(option->text, char, 20);
    strcpy(option->text, "Option 1");
    option->isSelected = false;

    option = (menuBar->options + 1);
    allocExist(option->text, char, 20);
    strcpy(option->text, "Option 2");
    option->isSelected = true;

    option = (menuBar->options + 2);
    allocExist(option->text, char, 20);
    strcpy(option->text, "Option 3");
    option->isSelected = false;

    SDL_Color fgColor = {160, 160, 40};
    menuBar->fontNormal = loadFont(FONT_PATH_MAC, 16, &fgColor, bgColor);
    menuBar->fontSelected = loadFont(FONT_PATH_MAC, 16, bgColor, &fgColor);

    return menuBar;
}
