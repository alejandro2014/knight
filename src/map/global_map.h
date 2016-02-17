#ifndef GLOBAL_MAP_H
#define GLOBAL_MAP_H

#include <SDL2/SDL.h>

#include "../global.h"

typedef int Layout;
#define LAYOUT_ONLY_CONSOLE 0
#define LAYOUT_ONLY_TERRAIN 1
#define LAYOUT_VER_CONSOLE_TERRAIN 2
#define LAYOUT_VER_TERRAIN_CONSOLE 3
#define LAYOUT_HOR_CONSOLE_TERRAIN 4
#define LAYOUT_HOR_TERRAIN_CONSOLE 5

#define NORTHWEST 0,menuHeight
#define NORTH width/2,menuHeight
#define NORTHEAST width-1,menuHeight
#define WEST 0,(menuHeight+height)/2
#define CENTER width/2,(menuHeight+height)/2
#define EAST width-1,(menuHeight+height)/2
#define SOUTHWEST 0,height-1
#define SOUTH width/2,height-1
#define SOUTHEAST width-1,height-1

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;

    Layout layout;
    SDL_Rect menuBarCoords;
    SDL_Rect consoleCoords;
    SDL_Rect terrainCoords;

    SDL_Color bgColorMenuBar;
    SDL_Color bgColorConsole;
    SDL_Color bgColorTerrain;

    int height;
    int width;
    int menuHeight;
} Screen;

typedef struct {
    int x, y;
    int width, height;
} TerrainVisualParams;

#endif
