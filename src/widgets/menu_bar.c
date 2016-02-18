#include <stdlib.h>
#include <string.h>

#include "menu_bar.h"

#include "../global.h"
#include "../draw.h"

void drawMenuBar(WMenuBar *menuBar, Screen *screen) {
    SDL_Renderer *renderer = screen->renderer;
    int i;

    clearSubScreen(renderer, &(screen->menuBarCoords), &(screen->bgColorMenuBar));

    for(i = 0; i < menuBar->numOptions; i++) {
        printString(menuBar->font, renderer, (menuBar->options + i)->text, i * 100 + 10, 2);
    }
}

WMenuBar *loadMenuBar(SDL_Color *bgColor) {
    alloc(menuBar, WMenuBar, 1);

    menuBar->numOptions = 1;
    allocExist(menuBar->options, WMenuBarOption, menuBar->numOptions);

    allocExist((menuBar->options + 0)->text, char, 20);
    strcpy((menuBar->options + 0)->text, "Option 1");

    SDL_Color fgColor = {160, 160, 40};
    menuBar->font = loadFont(FONT_PATH_MAC, 16, &fgColor, bgColor);

    return menuBar;
}
