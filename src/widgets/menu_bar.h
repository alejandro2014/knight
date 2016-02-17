#ifndef MENU_BAR_H
#define MENU_BAR_H

#include "../map/font.h"

typedef struct {
    Font *font;
} Widget_MenuBar;

Widget_MenuBar *loadMenuBar(SDL_Color *bgColor);

#endif
