/*******************************************************
 * sdlplasma
 * Author: Stefan Hellkvist, stefan@hellkvist.org
 * Copyright: see GPL
 *******************************************************/

#ifndef __GENERATE_TERRAIN_H__
#define __GENERATE_TERRAIN_H__

#include <stdlib.h>
#include "global.h"

int overdraw_terrain ();
int make_terrain ();

void drawSeed (int width, int height);
void drawMap (Point *p1, Point *p2);

int getNewColor (int c1, int c2, int dist);
int getNewColor4 (int c1, int c2, int c3, int c4, int dist);
int getPixel (int x, int y);
int mrandom (int max);
void putPixel (int x, int y, Uint8 color);

//Memory allocation
void allocate_mem();
void clear_mem();
void allocateMemTerrain(Uint8 **buffer, int map_size);
void freeMemTerrain(Uint8 *buffer);

#endif
