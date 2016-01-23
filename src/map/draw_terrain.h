#ifndef DRAW_TERRAIN_H
#define DRAW_TERRAIN_H

#include <SDL2/SDL.h>

#include "../api/api.h"
#include "../api/hme_lowlevel.h"

void drawTerrain(SDL_Renderer *renderer, Terrain *terrain);
void calculateOffset(Terrain *terrain, int *xOffset, int *yOffset);

#endif
