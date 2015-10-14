#ifndef ACTIONS_CORE_H
#define ACTIONS_CORE_H

#include <stdio.h>
#include <stdlib.h>

#include "global.h"

typedef struct {
  unsigned int x;
  unsigned int y;
  unsigned int z;
} Point;

typedef struct {
  unsigned int width;
  unsigned int height;
  unsigned int pointsNo;
  Point *points;
} Terrain;

Terrain *generateTerrain(int width, int height);
void freeTerrain(Terrain *terrain);

int getHeight(Point *point);
void setHeight(Point *point, int height);

extern Terrain *terrain;

#endif
