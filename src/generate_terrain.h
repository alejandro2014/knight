/*******************************************************
 * sdlplasma
 * Author: Stefan Hellkvist, stefan@hellkvist.org
 * Copyright: see GPL
 *******************************************************/

#ifndef __GENERATE_TERRAIN_H__
#define __GENERATE_TERRAIN_H__

#include <stdlib.h>
#include "actions_core.h"
#include "global.h"

unsigned int mrandom (unsigned int max);

//Memory allocation
void allocate_mem(Terrain **terrains, int width, int height);
void clear_mem();
int allocateMemTerrain(Uint8 **buffer, int map_size);
int allocateMemTerrain2(Uint8 **buffer, int map_size);
void freeMemTerrain(Uint8 *buffer);

void generateRandomTerrain(Terrain * terrain);

int hmeDrawSeed(Terrain *terrain);

Point *hmeGetPoint(Terrain *terrain, int x, int y);
Uint32 hmeGetHeight(Terrain *terrain, Uint32 x, Uint32 y);

#endif
