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

int mrandom (int max);

//Memory allocation
void allocate_mem(Terrain **terrains, int width, int height);
void clear_mem();
int allocateMemTerrain(Uint8 **buffer, int map_size);
int allocateMemTerrain2(Uint8 **buffer, int map_size);
void freeMemTerrain(Uint8 *buffer);

void generateRandomTerrain(Terrain * terrain);

void hmeDrawSeed(Terrain *terrain);

#endif
