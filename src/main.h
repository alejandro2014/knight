#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"
#include "api/api.h"
#include "api/hme_lowlevel.h"
#include "console/console.h"
#include "console/print.h"

#include "map/window.h"

typedef struct {
    Console *console;
    Terrain *terrain;
    int horSize;
    int verSize;
} HeightMapEditor;

HeightMapEditor *loadHeightMapEditor(int windowWidth, int windowHeight);
SDL_Window *createWindow(char *title, int width, int height);
SDL_Renderer *createRenderer(SDL_Window *window);

void freeResources(HeightMapEditor *hme);

#endif
