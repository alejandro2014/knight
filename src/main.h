#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "global.h"

#include "api/api.h"
#include "api/hme_lowlevel.h"
#include "api/generate_terrain.h"

#include "console/console_lang.h"
#include "console/console_load.h"
#include "console/console_print.h"

#include "map/draw.h"
#include "map/events.h"
#include "map/font.h"
#include "map/map_draw.h"

#include "widgets/menu_bar.h"

typedef struct {
    Console *console;
    Terrain *terrain;
    TerrainVisualParams *terrainParams;
    Screen *screen;
    Widget_MenuBar *menuBar; //TODO
} HeightMapEditor;

HeightMapEditor *loadHeightMapEditor();
TerrainVisualParams *loadTerrainParams();
SDL_Window *createWindow(char *title, int width, int height);
SDL_Renderer *createRenderer(SDL_Window *window);
void freeResources(HeightMapEditor *hme);

void hmeSetLayout(Screen *screen, Layout layout, Console *console);
void setWindowsLayout(Screen *screen, Layout layout);

void programLoop(HeightMapEditor *hme);

#endif
