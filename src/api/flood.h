#ifndef FLOOD_H
#define FLOOD_H

#include "flood.h"
#include "api.h"

#define STEP_LEFT -1
#define STEP_RIGHT 1
#define STEP_UP -1
#define STEP_DOWN 1

typedef int Direction;
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

char *api_floodArea(Terrain **terrain, int x, int y, int height);
void setFillStatusTerrain(Terrain *terrain, FillStatus fillStatus);

void floodLineHor(Terrain *terrain, int x, int y, int height, Direction direction);
void floodLineVer(Terrain *terrain, int x, int yIni, int yFin, int height);

void api_MergeTerrains(Terrain *srcTerrain, Terrain *destTerrain, int startX, int startY, Operation operation);

#endif
