/*******************************************************
 * sdlplasma
 * Author: Stefan Hellkvist, stefan@hellkvist.org
 * Copyright: see GPL
 *******************************************************/

#ifndef __GENERATE_TERRAIN_H__
#define __GENERATE_TERRAIN_H__

#include <stdlib.h>
#include "global.h"

typedef struct {
    int x;
    int y;
} Point;

void drawSeed (int width, int height);

void drawMap (int x1, int y1, int x2, int y2);

int overdraw_terrain(int width, int height);

int make_terrain (int width, int height);

void allocate_mem();

int getNewColor (int c1, int c2, int dist);
int getNewColor4 (int c1, int c2, int c3, int c4, int dist);
int getPixel (int x, int y);
int mrandom (int max);
void putPixel (int x, int y, Uint8 color);

void freeMemTerrain(Uint8 *buffer);
void allocateMemTerrain(Uint8 **buffer);

#endif
