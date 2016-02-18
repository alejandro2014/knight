#include <stdlib.h>
#include <string.h>

#include "menu_bar.h"

#include "../global.h"
#include "../draw.h"

void drawMenuBar(WMenu *menuBar, Screen *screen) {
    Font *currentFont = NULL;
    SDL_Renderer *renderer = screen->renderer;
    int x, y;
    int i;

    clearSubScreen(renderer, &(screen->menuBarCoords), &(screen->bgColorMenuBar));

    WMenu *option = menuBar->options;

    for(i = 0; i < menuBar->numOptions; i++) {
        //currentFont = (menuBar->options + i)->isSelected ? menuBar->fontSelected : menuBar->fontNormal;
        x = i * 100 + 10;
        y = 2;
        //printString(currentFont, renderer, (menuBar->options + i)->text, x, y);
        printString(menuBar->fontNormal, renderer, option->text, x, y);
        option = option->next;
    }

    drawMenu(screen, menuBar);
}

void drawMenu(Screen *screen, WMenu *menuBar) {
    SDL_Renderer *renderer = screen->renderer;
    int numOptions = 3;

    alloc(options, WMenu, numOptions);
    (options + 0)->text = "Sub-option 1";
    (options + 1)->text = "Sub-option 2";
    (options + 2)->text = "Sub-option 3";

    int optionSelected = 1;
    int heightOption = 23;
    int xSubMenu = optionSelected * 100 + 10;
    int i;

    SDL_Rect rectMenu;
    setRect(&rectMenu, xSubMenu, 20, xSubMenu + 130, 20 + 3 * heightOption);
    clearSubScreen(renderer, &rectMenu, &(screen->bgColorMenuBar));

    for(i = 0; i < numOptions; i++) {
        //currentFont = (menuBar->options + i)->isSelected ? menuBar->fontSelected : menuBar->fontNormal;
        printString(menuBar->fontNormal, renderer, (options + i)->text, xSubMenu, i * heightOption + 25);
    }
}

WMenu *loadMenuBar(SDL_Color *bgColor) {
    alloc(menuBar, WMenu, 1);
    SDL_Color fgColor = {160, 160, 40};
    menuBar->fontNormal = loadFont(FONT_PATH_MAC, 16, &fgColor, bgColor);
    menuBar->fontSelected = loadFont(FONT_PATH_MAC, 16, bgColor, &fgColor);

    addOption(menuBar, "Option 1");
    addOption(menuBar, "Option 2");
    addOption(menuBar, "Option 3");

    return menuBar;
}

WMenu *addOption(WMenu *menu, char *text) {
    WMenu *newOption = createOption(text);
    WMenu *lastOption = menu->options;

    if(lastOption == NULL) {
        menu->options = newOption;
        menu->numOptions++;
        return newOption;
    }

    while(lastOption->next != NULL) {
        lastOption = lastOption->next;
    }

    lastOption->next = newOption;
    menu->numOptions++;
    return newOption;
}

WMenu *createOption(char *text) {
    alloc(option, WMenu, 1);
    allocExist(option->text, char, 20);
    strcpy(option->text, text);

    return option;
}

void addNewOption(WMenuBarOption *option, char *text, bool isSelected) {
    allocExist(option->text, char, 20);
    strcpy(option->text, text);
    option->isSelected = isSelected;
}
