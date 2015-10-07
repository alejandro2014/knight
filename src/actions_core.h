#ifndef ACTIONS_CORE_H
#define ACTIONS_CORE_H

#include <stdio.h>
#include <stdlib.h>

#include "global.h"

typedef struct {
  float x;
  float y;
  float z;
} Point;

typedef struct {
  int width;
  int height;
  int pointsNo;
  Point *points;
} Terrain;

Terrain *generateTerrain(int width, int height);
void freeTerrain(Terrain *terrain);

int getHeight(Point *point);
void setHeight(Point *point, int height);

#endif
