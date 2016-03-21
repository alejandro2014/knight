//TODO Link click on an option with the actual action
//TODO Implement states of the menu
//TODO Change event type, from click to hover over

#include <stdlib.h>
#include <string.h>

#include "menu_bar.h"

#include "../global.h"
#include "../draw.h"

RegisteredOptions registeredOptions;

void drawMenu(WMenu *menu, Screen *screen) {
    WMenu *option = NULL;
    int i;

    if(menu->options == 0) return;

    drawMenuBox(screen, menu);

    for(i = 0; i < menu->numOptions; i++) {
        option = menu->options + i;

        if(option->isVisible)
            drawMenu(option, screen);

        drawTextOption(screen, option);
    }
}

void drawMenuBox(Screen *screen, WMenu *menu) {
    SDL_Renderer *renderer = screen->renderer;
    SDL_Rect coords = menu->options->coords;
    SDL_Rect rectMenu;
    int widthOption = 130;
    int heightOption = 23;
    int heightMenuBar = 20;

    if(menu->options->level > 0) {
        setRect(&rectMenu, coords.x, coords.y, coords.x + widthOption, menu->numOptions * heightOption + heightMenuBar);
        clearSubScreen(renderer, &rectMenu, &(screen->bgColorMenuBar));
    }
}

void drawTextOption(Screen *screen, WMenu *option) {
    SDL_Renderer *renderer = screen->renderer;
    Font *currentFont = option->isSelected ? option->fontSelected : option->fontNormal;

    printString(currentFont, renderer, option->text, option->coords.x, option->coords.y);
}

void openOption(WMenu *option) {
    WMenu *subOption = NULL;
    int i;

    closeBrotherOptions(option);

    for(i = 0; i < option->numOptions; i++) {
        subOption = option->options + i;
        subOption->isVisible = true;
    }

    option->isSelected = true;
    option->isVisible = true;
}

void closeOption(WMenu *option) {
    WMenu *subOption = NULL;
    int i;

    for(i = 0; i < option->numOptions; i++) {
        subOption = option->options + i;
        subOption->isVisible = false;
        subOption->isSelected = false;

        closeOption(subOption);
    }

    option->isVisible = false;
    option->isSelected = false;
}

void closeBrotherOptions(WMenu *option) {
    WMenu *parentOption = option->parentOption;
    WMenu *currentOption = NULL;
    int i;

    for(i = 0; i < parentOption->numOptions; i++) {
        currentOption = parentOption->options + i;
        closeOption(currentOption);
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
