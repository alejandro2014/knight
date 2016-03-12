//TODO Click on an option only when visible
//TODO Implement states of the menu
//TODO Link clik on an option with the actual action

#include <stdlib.h>
#include <string.h>

#include "menu_bar.h"

#include "../global.h"
#include "../draw.h"

RegisteredOptions registeredOptions;

void drawMenu(WMenu *menuBar, Screen *screen) {
    SDL_Rect rectMenu;
    WMenu *option = NULL;
    Font *currentFont = NULL;
    SDL_Renderer *renderer = screen->renderer;
    int widthOption = 130;
    int heightOption = 23;
    int heightMenuBar = 20;
    int i;

    if(menuBar->numOptions == 0) return;

    if(menuBar->options->level > 0) {
        setRect(&rectMenu, menuBar->options->coords.x, menuBar->options->coords.y, menuBar->options->coords.x + widthOption, menuBar->numOptions * heightOption + heightMenuBar);
        clearSubScreen(renderer, &rectMenu, &(screen->bgColorMenuBar));
    }

    for(i = 0; i < menuBar->numOptions; i++) {
        option = menuBar->options + i;
        if(option->isSelected)
            drawMenu(option, screen);

        currentFont = option->isSelected ? option->fontSelected : option->fontNormal;
        printString(currentFont, renderer, option->text, option->coords.x, option->coords.y);
    }
}

WMenu *loadMenu(SDL_Color *bgColor) {
    int level = 0;
    alloc(menuBar, WMenu, 1);
    allocExist(menuBar->options, WMenu, MAX_OPTIONS);

    SDL_Color fgColor = {160, 160, 40};
    Font *fontNormal = loadFont(FONT_PATH_MAC, 16, &fgColor, bgColor);
    Font *fontSelected = loadFont(FONT_PATH_MAC, 16, bgColor, &fgColor);

    menuBar->fontNormal = fontNormal;
    menuBar->fontSelected = fontSelected;

    addOption(menuBar, "File");
    addOption(menuBar, "Edit");
    addOption(menuBar, "Help");

    addOption(menuBar->options, "Sub-option1");
    addOption(menuBar->options, "Sub-option2");
    addOption(menuBar->options, "Exit");

    addOption(menuBar->options + 1, "Sub-option11");
    addOption(menuBar->options + 1, "Sub-option22");
    addOption(menuBar->options + 1, "Sub-option33");

    return menuBar;
}

void selectOption(WMenu *option) {
    deselectOption(option->parentOption);
    option->parentOption->isSelected = true;
    option->isSelected = true;
}

void deselectOption(WMenu *option) {
    option->isSelected = false;
    if(option->options == NULL) return;

    int optionsNo = option->numOptions;
    WMenu *currentOption = NULL;
    int i;

    for(i = 0; i < optionsNo; i++) {
        currentOption = option->options + i;
        deselectOption(currentOption);
    }
}

void addOption(WMenu *menu, char *text) {
    if(menu->options == NULL)
        allocateSubOptions(menu);

    WMenu *option = menu->options + menu->numOptions;

    option->text = text;
    option->fontNormal = menu->fontNormal;
    option->fontSelected = menu->fontSelected;
    option->parentOption = menu;

    setCoordsOption(option, menu->numOptions);
    menu->numOptions++;
}

void allocateSubOptions(WMenu *menu) {
    int i;

    allocExist(menu->options, WMenu, MAX_OPTIONS);

    for(i = 0; i < MAX_OPTIONS; i++) {
        (menu->options + i)->level = menu->level + 1;
    }
}

void setCoordsOption(WMenu *option, int optionNo) {
    int widthOption = 100;
    int heightOption = 23;
    int x, y;

    if(option->level == 0) {
        x = optionNo * widthOption + 10;
        y = 2;
    } else {
        x = option->parentOption->coords.x;
        y = option->parentOption->coords.y + optionNo * heightOption + 22;
    }

    setRect(&(option->coords), x, y, x + widthOption, y + heightOption);
    registerOption(option);
}

void registerOption(WMenu *option) {
    int currentOption = registeredOptions.numOptions++;
    registeredOptions.options[currentOption] = option;
}

WMenu *getOptionClicked(int x, int y) {
    WMenu *option = NULL;
    int numOptions = registeredOptions.numOptions;
    int i;

    for(i = 0; i < numOptions; i++) {
        option = registeredOptions.options[i];

        if(isCursorInsideOption(x, y, option))
            return option;
    }

    return NULL;
}

bool isCursorInsideOption(int x, int y, WMenu *option) {
    return isPointInsideRectangle(x, y, &(option->coords));
}

bool isPointInsideRectangle(int x, int y, SDL_Rect *rectangle) {
    int x1 = rectangle->x;
    int x2 = rectangle->x + rectangle->w;
    int y1 = rectangle->y;
    int y2 = rectangle->y + rectangle->h;

    return (x > x1 && x < x2 && y > y1 && y < y2) ? true : false;
}
