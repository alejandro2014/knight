#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "global.h"
#include "draw.h"
#include "font.h"

#include "api/api.h"
#include "api/hme_lowlevel.h"
#include "api/generate_terrain.h"

#include "console/console_draw.h"
#include "console/console_lang.h"
#include "console/console_load.h"
#include "console/console_print.h"
#include "console/console_types.h"

#include "map/events.h"
#include "map/map_draw.h"

#include "widgets/menu_bar.h"
#include "widgets/widgets.h"
#include "widgets/menus.h"

typedef struct {
    Console *console;
    Terrain *terrain;
    TerrainVisualParams *terrainParams;
    Screen *screen;
    WMenu *menuBar;
    Dialog **dialogs;

    Font *fontDialogsTitle;
    Font *fontConsole;
    Font *fontMenusNormal;
    Font *fontMenusSelected;
} HeightMapEditor;

void hmeSetLayout(Screen *screen, Layout layout, Console *console);
void setWindowsLayout(Screen *screen, Layout layout);

void programLoop(HeightMapEditor *hme);
void drawScreen(HeightMapEditor *hme);

#endif
