#include <stdlib.h>
#include <string.h>

#include "menu_bar.h"

#include "../global.h"
#include "../draw.h"

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
        setRect(&rectMenu, menuBar->options->x, menuBar->options->y, menuBar->options->x + widthOption, menuBar->numOptions * heightOption + heightMenuBar);
        clearSubScreen(renderer, &rectMenu, &(screen->bgColorMenuBar));
    }

    for(i = 0; i < menuBar->numOptions; i++) {
        option = menuBar->options + i;
        if(option->isSelected)
            drawMenu(option, screen);

        currentFont = option->isSelected ? option->fontSelected : option->fontNormal;
        printString(currentFont, renderer, option->text, option->x, option->y);
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
    addOption(menuBar->options, "Sub-option3");

    addOption(menuBar->options + 1, "Sub-option11");
    addOption(menuBar->options + 1, "Sub-option22");
    addOption(menuBar->options + 1, "Sub-option33");

    selectOption(menuBar, 1);
    selectOption(menuBar->options + 1, 1);

    return menuBar;
}

void selectOption(WMenu *menu, int optionNo) {
    WMenu *option = menu->options + optionNo;
    option->isSelected = true;
}

void addOption(WMenu *menu, char *text) {
    int i;
    WMenu *currentOption = menu->options + menu->numOptions;

    currentOption->text = text;
    currentOption->thisOptionPos = menu->numOptions;
    currentOption->fontNormal = menu->fontNormal;
    currentOption->fontSelected = menu->fontSelected;
    setCoordsOption(currentOption, menu->numOptions);

    allocateSubOptions(currentOption, menu);
    menu->numOptions++;
}

void allocateSubOptions(WMenu *currentOption, WMenu *menu) {
    WMenu *option = NULL;
    int i;

    allocExist(currentOption->options, WMenu, MAX_OPTIONS);

    for(i = 0; i < MAX_OPTIONS; i++) {
        option = currentOption->options + i;
        option->level = menu->level + 1;
        option->parentOptionPos = currentOption->thisOptionPos;
        setCoordsOption(option, i);
    }
}

void setCoordsOption(WMenu *option, int optionNo) {
    int widthOption = 100;
    int heightOption = 23;

    if(option->level == 0) {
        option->x = optionNo * widthOption + 10;
        option->y = 2;
    } else {
        option->x = option->parentOptionPos * widthOption + 10;
        option->y = optionNo * heightOption + 22;
    }
}
