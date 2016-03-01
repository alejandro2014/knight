#include <stdlib.h>
#include <string.h>

#include "menu_bar.h"

#include "../global.h"
#include "../draw.h"

void setCoordsMenu(int optionNo, int *x, int *y, int level) {
    if(level == 0) {
        *x = optionNo * 100 + 10;
        *y = 2;
    }
}

void drawMenuBar(WMenu *menuBar, Screen *screen) {
    WMenu *option = NULL;
    Font *currentFont = NULL;
    SDL_Renderer *renderer = screen->renderer;
    int x, y;
    int i;

    clearSubScreen(renderer, &(screen->menuBarCoords), &(screen->bgColorMenuBar));

    for(i = 0; i < menuBar->numOptions; i++) {
        option = menuBar->options + i;
        currentFont = option->isSelected ? menuBar->fontSelected : menuBar->fontNormal;
        setCoordsMenu(i, &x, &y, menuBar->level);
        printString(currentFont, renderer, option->text, x, y);

        //drawMenuBar(screen, menuBar->options, level++);
    }
}

void drawMenu(Screen *screen, WMenu *menuBar) {
    /*WMenu *option = NULL;
    Font *currentFont = NULL;
    SDL_Renderer *renderer = screen->renderer;
    int x, y;
    int i;

    int optionSelected = 2;
    int heightOption = 23;
    int xSubMenu = optionSelected * 100 + 10;

    SDL_Rect rectMenu;
    setRect(&rectMenu, xSubMenu, 20, xSubMenu + 130, 20 + 3 * heightOption);
    clearSubScreen(renderer, &rectMenu, &(screen->bgColorMenuBar));

    for(i = 0; i < menuBar->numOptions; i++) {
        option = menuBar->options + i;
        currentFont = option->isSelected ? menuBar->fontSelected : menuBar->fontNormal;
        x = xSubMenu;
        y = i * heightOption + 25;
        printString(currentFont, renderer, option->text, x, y);
    }*/
}

WMenu *loadMenuBar(SDL_Color *bgColor) {
    int level = 0;
    alloc(menuBar, WMenu, 1);
    allocExist(menuBar->options, WMenu, MAX_OPTIONS);
    SDL_Color fgColor = {160, 160, 40};
    menuBar->fontNormal = loadFont(FONT_PATH_MAC, 16, &fgColor, bgColor);
    menuBar->fontSelected = loadFont(FONT_PATH_MAC, 16, bgColor, &fgColor);

    addOption(menuBar, "File");
    addOption(menuBar, "Edit");
    addOption(menuBar, "Help");

    (menuBar->options + 2)->isSelected = true;

    addOption(menuBar->options, "Sub-option1");
    addOption(menuBar->options, "Sub-option2");
    addOption(menuBar->options, "Sub-option3");

    return menuBar;
}

void addOption(WMenu *menu, char *text) {
    int i;
    WMenu *currentOption = menu->options + (menu->numOptions++);

    currentOption->text = text;
    allocExist(currentOption->options, WMenu, MAX_OPTIONS);

    for(i = 0; i < MAX_OPTIONS; i++) {
        (currentOption->options + i)->fontNormal = menu->fontNormal;
        (currentOption->options + i)->fontSelected = menu->fontSelected;
        (currentOption->options + i)->level = menu->level + 1;
    }
}
