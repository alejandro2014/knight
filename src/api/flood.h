#ifndef FLOOD_H
#define FLOOD_H

#include "flood.h"
#include "api.h"

void pre_flood_area(Terrain *terrain, int cur_x, int cur_y);
void setFillStatusTerrain(Terrain *terrain, FillStatus fillStatus);

void flood_line(Terrain *terrain, int x, int y, int height);
void floodLine(Terrain *terrain, int xIni, int xFin, int y, int height);
void flood_ver_line(Terrain *terrain, int x, int y, int height);
void floodVerticalLine(Terrain *terrain, int x, int yIni, int yFin, int height);

#endif
