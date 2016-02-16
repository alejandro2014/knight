#ifndef DRAW_TERRAIN_H
#define DRAW_TERRAIN_H

#include <SDL2/SDL.h>

#include "../api/api.h"
#include "../api/hme_lowlevel.h"

#include "global_map.h"
#include "draw.h"

void drawTerrain(Screen *screen, Terrain *terrain, TerrainVisualParams *params);
void calculateOffset(Terrain *terrain, int *xOffset, int *yOffset, TerrainVisualParams *terrainParams);

#endif
