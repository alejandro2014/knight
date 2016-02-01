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
#include "console/load_console.h"
#include "console/print.h"

#include "map/draw.h"
#include "map/events.h"
#include "map/font.h"

typedef struct {
    Console *console;
    ConsoleVisualParams *consoleParams;
    Terrain *terrain;
    TerrainVisualParams *terrainParams;
    int height;
    int width;
} HeightMapEditor;

HeightMapEditor *loadHeightMapEditor(int windowWidth, int windowHeight);
void hmeSetLayout(HeightMapEditor *hme, int windowWidth, int windowHeight);
SDL_Window *createWindow(char *title, int width, int height);
SDL_Renderer *createRenderer(SDL_Window *window);

void freeResources(HeightMapEditor *hme);

void programLoop(SDL_Renderer *renderer);

ConsoleVisualParams *loadConsoleParams(int windowWidth, int windowHeight);
TerrainVisualParams *loadTerrainParams();

#endif
