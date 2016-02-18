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

typedef struct _WMenu {
    int numOptions;
    struct _WMenu *options;
    bool isSelected;

    Font *fontNormal;
    Font *fontSelected;
} WMenu;

void drawMenuBar(WMenuBar *menuBar, Screen *screen);
WMenuBar *loadMenuBar(SDL_Color *bgColor);
void addNewOption(WMenuBarOption *option, char *text, bool isSelected);
void drawMenu(Screen *screen, WMenuBar *menuBar);

#endif
