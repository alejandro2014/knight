#ifndef TOOLS_H
#define TOOLS_H

#include <math.h>
#include "global.h"

#define not_filled 0
#define pending_fill 1
#define already_filled 2

int get_cur_x_y();
void zoom_in();
void pick_height (bool button_l, bool button_r);
void select_area();
void put_pattern(Terrain * terrain, int x, int y);
void replacePoint(Terrain *terrain, int x, int y, int tolerance_mode);
void modifyHeight(Terrain *terrain, int x, int y, int delta, int tolerance_mode);
void updateMinMaxDrawnCoords(int x, int y);
void getTerrainCoords();
void clearTempBuffer();

#endif
