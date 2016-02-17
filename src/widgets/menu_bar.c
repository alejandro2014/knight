#include <stdlib.h>
#include <string.h>

#include "menu_bar.h"

#include "../global.h"

Widget_MenuBar *loadMenuBar(SDL_Color *bgColor) {
    alloc(menuBar, Widget_MenuBar, 1);

    SDL_Color fgColor = {160, 160, 40};
    menuBar->font = loadFont(FONT_PATH_MAC, 16, &fgColor, bgColor);

    return menuBar;
}
