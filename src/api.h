#ifndef API_H
#define API_H

#include "terrain.h"
#include "global.h"

typedef int Operation;
#define ROTATE_90 2
#define ROTATE_180 1
#define ROTATE_270 0

Terrain *api_rotate(Terrain *oldTerrain, int angle);
Terrain *rotatex(Operation operation, Terrain *oldTerrain);

Terrain *api_flip(Terrain *oldTerrain, Axis axis);
Terrain *api_flipX(Terrain *oldTerrain);
Terrain *api_flipY(Terrain *oldTerrain);
Terrain *api_flipZ(Terrain *oldTerrain);

int getHeightForOperation(Operation operation, Terrain *terrain, int x, int y);
void setDimensionsForOperation(Operation operation, Terrain *terrain, int *width, int *height);

#endif
