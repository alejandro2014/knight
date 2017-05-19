#ifndef MAP_DRAW_H
#define MAP_DRAW_H

#include <SDL2/SDL.h>

#include "../draw.h"

#include "../api/api.h"
#include "../api/hme_lowlevel.h"

#include "global_map.h"

void drawTerrain(Screen *screen, Terrain *terrain, TerrainVisualParams *params);
void calculateOffset(Terrain *terrain, int *xOffset, int *yOffset, TerrainVisualParams *terrainParams);

void drawBarcodeLine(SDL_Renderer *renderer, int x);
void drawChar(SDL_Renderer *renderer);

#endif
