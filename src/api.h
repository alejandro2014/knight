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

void api_riseTerrain(Terrain *terrain, int delta);
void api_sinkTerrain(Terrain *terrain, int delta);
void api_setHeightTerrain(Terrain *terrain, int height);
void api_smoothTerrain(Terrain *terrain);

void api_riseSelection(Terrain *terrain, int startX, int startY, int endX, int endY, int delta);
void api_sinkSelection(Terrain *terrain, int startX, int startY, int endX, int endY, int delta);
void api_setHeightSelection(Terrain *terrain, int startX, int startY, int endX, int endY, int height);
void api_smoothSelection(Terrain *terrain, int startX, int startY, int endX, int endY);

Terrain *api_rotate(Operation operation, Terrain *oldTerrain);
int getHeightForOperation(Operation operation, Terrain *terrain, int x, int y);
void setDimensionsForOperation(Operation operation, Terrain *terrain, int *width, int *height);

#endif
