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
    char *text;
    int numOptions;
    struct _WMenu *options;
    struct _WMenu *next;
    bool isSelected;

    Font *fontNormal;
    Font *fontSelected;
} WMenu;

void drawMenuBar(WMenu *menuBar, Screen *screen);
WMenu *loadMenuBar(SDL_Color *bgColor);
void addNewOption(WMenuBarOption *option, char *text, bool isSelected);
void drawMenu(Screen *screen, WMenu *menuBar);

WMenu *addOption(WMenu *menu, char *text);
WMenu *createOption(char *text);

#endif
