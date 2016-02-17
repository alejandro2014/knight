#ifndef MENU_BAR_H
#define MENU_BAR_H

#include "../map/font.h"
#include "../map/draw.h"

typedef struct {
    Font *font;
} Widget_MenuBar;

void drawMenuBar(Widget_MenuBar *menuBar, Screen *screen);
Widget_MenuBar *loadMenuBar(SDL_Color *bgColor);

#endif
