#ifndef MENU_BAR_H
#define MENU_BAR_H

#include "../draw.h"

#include "../map/font.h"
#include "../map/global_map.h"

typedef struct {
    char *text;
} WMenuBarOption;

typedef struct {
    Font *font;
    WMenuBarOption *options;
    int numOptions;
} WMenuBar;

void drawMenuBar(WMenuBar *menuBar, Screen *screen);
WMenuBar *loadMenuBar(SDL_Color *bgColor);

#endif
