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

void api_floodArea(Terrain *terrain, int cur_x, int cur_y);
void setFillStatusTerrain(Terrain *terrain, FillStatus fillStatus);

void flood_line(Terrain *terrain, int x, int y, int height);
void floodLineHor(Terrain *terrain, int x, int y, int height, Direction direction);
void flood_ver_line(Terrain *terrain, int x, int y, int height, Direction direction);
void floodLineVer(Terrain *terrain, int x, int yIni, int yFin, int height);

#endif
