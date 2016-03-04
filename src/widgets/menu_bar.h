#ifndef MENU_BAR_H
#define MENU_BAR_H

#include "../global.h"
#include "../draw.h"

#include "../map/font.h"
#include "../map/global_map.h"

#define MAX_OPTIONS 10

typedef struct _WMenu {
    char *text;
    bool isSelected;
    int x;
    int y;

    Font *fontNormal;
    Font *fontSelected;
    int numOptions;
    struct _WMenu *options;
    int level;

    int thisOptionPos;
    int parentOptionPos;
} WMenu;

void drawMenu(WMenu *menuBar, Screen *screen);

WMenu *loadMenu(SDL_Color *bgColor);

void addOption(WMenu *menu, char *text);
void allocateSubOptions(WMenu *currentOption, WMenu *menu);

void selectOption(WMenu *menu, int optionNo);
void setCoordsOption(WMenu *option, int optionNo);

#endif
