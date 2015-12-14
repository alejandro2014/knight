#ifndef API_H
#define API_H

#include "terrain.h"
#include "global.h"

#define MAX_HEIGHT 255

typedef int Operation;
#define ROTATE_90 0
#define ROTATE_180 1
#define ROTATE_270 2
#define FLIP_XAXIS 3
#define FLIP_YAXIS 4

void api_invertHeight(Terrain *terrain);

Terrain *api_rotate(Operation operation, Terrain *oldTerrain);
int getHeightForOperation(Operation operation, Terrain *terrain, int x, int y);
void setDimensionsForOperation(Operation operation, Terrain *terrain, int *width, int *height);

#endif
