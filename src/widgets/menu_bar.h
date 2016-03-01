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
    Font *fontNormal;
    Font *fontSelected;
    int numOptions;
    struct _WMenu *options;
    int level;
} WMenu;

void setCoordsMenu(int optionNo, int *x, int *y, int level);

void drawMenuBar(WMenu *menuBar, Screen *screen);
WMenu *loadMenuBar(SDL_Color *bgColor);
void drawMenu(Screen *screen, WMenu *menuBar);

void addOption(WMenu *menu, char *text);
WMenu *createOption(WMenu *menu, char *text);

#endif
