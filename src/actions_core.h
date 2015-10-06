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
  Point **points;
} Terrain;

Terrain *hme_generate_terrain(int width, int height);
Point **hmeAllocatePoints(int width, int height);

void hmeFreeTerrain(Terrain *terrain);

#endif
