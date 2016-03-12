#ifndef MENU_BAR_H
#define MENU_BAR_H

#include "../global.h"
#include "../draw.h"

#include "../map/font.h"
#include "../map/global_map.h"

#define MAX_OPTIONS 10

typedef struct _WMenu {
    char *text;
    bool isVisible;
    bool isSelected;

    Font *fontNormal;
    Font *fontSelected;
    SDL_Rect coords;
    int numOptions;
    struct _WMenu *options;
    struct _WMenu *parentOption;
    int level;
} WMenu;

typedef struct {
    WMenu *options[100];
    int numOptions;
} RegisteredOptions;

void drawMenu(WMenu *menuBar, Screen *screen);

WMenu *loadMenu(SDL_Color *bgColor);

void addOption(WMenu *menu, char *text);
void allocateSubOptions(WMenu *menu);

void selectOption(WMenu *option);
void deselectOption(WMenu *option);

void setCoordsOption(WMenu *option, int optionNo);
void registerOption(WMenu *option);

WMenu *getOptionClicked(int x, int y);
bool isCursorInsideOption(int x, int y, WMenu *option);
bool isPointInsideRectangle(int x, int y, SDL_Rect *rectangle);

#endif
