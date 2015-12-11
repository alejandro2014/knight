#ifndef ACTIONS_CORE_H
#define ACTIONS_CORE_H

#include <stdio.h>
#include <stdlib.h>

#include "global.h"

typedef struct {
  int x;
  int y;
  int z;
  bool isHeightSetted;
} Point;

typedef struct {
  int width;
  int height;
  int pointsNo;
  Point *points;
} Terrain;

Terrain *generateTerrain(int width, int height);
void freeTerrain(Terrain *terrain);

#endif
