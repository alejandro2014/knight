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

#include "console/console.h"
#include "console/console_load.h"
#include "console/console_print.h"

#include "map/draw.h"
#include "map/events.h"
#include "map/font.h"

typedef int Layout;
#define LAYOUT_ONLY_CONSOLE 0
#define LAYOUT_ONLY_TERRAIN 1
#define LAYOUT_VER_CONSOLE_TERRAIN 2
#define LAYOUT_VER_TERRAIN_CONSOLE 3
#define LAYOUT_HOR_CONSOLE_TERRAIN 4
#define LAYOUT_HOR_TERRAIN_CONSOLE 5

typedef struct {
    Console *console;
    ConsoleVisualParams *consoleParams;
    Terrain *terrain;
    TerrainVisualParams *terrainParams;
    int height;
    int width;
} HeightMapEditor;

HeightMapEditor *loadHeightMapEditor(int windowWidth, int windowHeight);
ConsoleVisualParams *loadConsoleParams(SDL_Rect *params);
TerrainVisualParams *loadTerrainParams();
SDL_Window *createWindow(char *title, int width, int height);
SDL_Renderer *createRenderer(SDL_Window *window);
void freeResources(HeightMapEditor *hme);

void hmeSetLayout(HeightMapEditor *hme, int windowWidth, int windowHeight, Layout);
void setWindowsLayout(Layout layout, SDL_Rect *consoleRect, SDL_Rect *terrainRect, HeightMapEditor *hme);

void programLoop(SDL_Renderer *renderer);

#endif
