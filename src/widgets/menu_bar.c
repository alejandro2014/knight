#include <stdlib.h>
#include <string.h>

#include "menu_bar.h"

#include "../global.h"
#include "../draw.h"

void drawMenuBar(WMenu *menuBar, Screen *screen) {
    SDL_Rect rectMenu;
    WMenu *option = NULL;
    Font *currentFont = NULL;
    SDL_Renderer *renderer = screen->renderer;
    int x, y;
    int i;

    if(menuBar->numOptions == 0) return;

    if(menuBar->options->level > 0) {
        setRect(&rectMenu, menuBar->options->x, menuBar->options->y, menuBar->options->x + 130, 20 + 3 * 23);
        clearSubScreen(renderer, &rectMenu, &(screen->bgColorMenuBar));
    }

    for(i = 0; i < menuBar->numOptions; i++) {
        option = menuBar->options + i;

        if(option->isSelected) {
            currentFont = menuBar->fontSelected;
            drawMenuBar(option, screen);
        } else {
            currentFont = menuBar->fontNormal;
        }

        printString(currentFont, renderer, option->text, option->x, option->y);
    }
}

WMenu *loadMenuBar(SDL_Color *bgColor) {
    int level = 0;
    alloc(menuBar, WMenu, 1);
    allocExist(menuBar->options, WMenu, MAX_OPTIONS);

    SDL_Color fgColor = {160, 160, 40};
    Font *fontNormal = loadFont(FONT_PATH_MAC, 16, &fgColor, bgColor);
    Font *fontSelected = loadFont(FONT_PATH_MAC, 16, bgColor, &fgColor);

    menuBar->fontNormal = fontNormal;
    menuBar->fontSelected = fontSelected;

    addOption(menuBar, "File", fontNormal, fontSelected);
    addOption(menuBar, "Edit", fontNormal, fontSelected);
    addOption(menuBar, "Help", fontNormal, fontSelected);

    addOption(menuBar->options, "Sub-option1", fontNormal, fontSelected);
    addOption(menuBar->options, "Sub-option2", fontNormal, fontSelected);
    addOption(menuBar->options, "Sub-option3", fontNormal, fontSelected);

    addOption(menuBar->options + 1, "Sub-option11", fontNormal, fontSelected);
    addOption(menuBar->options + 1, "Sub-option22", fontNormal, fontSelected);
    addOption(menuBar->options + 1, "Sub-option33", fontNormal, fontSelected);

    selectOption(menuBar, 2);

    return menuBar;
}

void selectOption(WMenu *menu, int optionNo) {
    int i;
    WMenu *option = menu->options + optionNo;
    WMenu *suboption = NULL;
    option->isSelected = true;

    for(i = 0; i < menu->numOptions; i++) {
        suboption = option->options + i;
        suboption->parentOptionPos = optionNo;
    }
}

void addOption(WMenu *menu, char *text, Font *fontNormal, Font *fontSelected) {
    int i;
    WMenu *currentOption = menu->options + menu->numOptions;
    WMenu *option = NULL;

    setCoordsOption(currentOption, menu->numOptions);

    currentOption->text = text;
    currentOption->fontNormal = fontNormal;
    currentOption->fontSelected = fontSelected;
    currentOption->thisOptionPos = menu->numOptions;

    allocExist(currentOption->options, WMenu, MAX_OPTIONS);

    for(i = 0; i < MAX_OPTIONS; i++) {
        option = currentOption->options + i;
        option->level = menu->level + 1;
        option->parentOptionPos = currentOption->thisOptionPos;
        setCoordsOption(option, i);
    }

    menu->numOptions++;
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
