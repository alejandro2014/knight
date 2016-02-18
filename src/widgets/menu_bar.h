#ifndef MENU_BAR_H
#define MENU_BAR_H

#include "../global.h"
#include "../draw.h"

#include "../map/font.h"
#include "../map/global_map.h"

typedef struct {
    char *text;
    bool isSelected;
} WMenuBarOption;

typedef struct {
    Font *fontNormal;
    Font *fontSelected;
    WMenuBarOption *options;
    int numOptions;
} WMenuBar;

void drawMenuBar(WMenuBar *menuBar, Screen *screen);
WMenuBar *loadMenuBar(SDL_Color *bgColor);

#endif
