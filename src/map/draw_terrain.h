#ifndef DRAW_TERRAIN_H
#define DRAW_TERRAIN_H

#include <SDL2/SDL.h>

#include "../api/api.h"
#include "../api/hme_lowlevel.h"

#include "global_map.h"

typedef struct {
    int x, y;
    int width, height;
} TerrainVisualParams;

void drawTerrain(SDL_Renderer *renderer, Terrain *terrain, TerrainVisualParams *terrainParams);
void calculateOffset(Terrain *terrain, int *xOffset, int *yOffset, TerrainVisualParams *terrainParams);

#endif
