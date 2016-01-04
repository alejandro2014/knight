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
void updateMinMaxDrawnCoords(int x, int y);
void getTerrainCoords();
void clearTempBuffer();

void new_terrain_menu ();
void generate_menu (int seed);
void do_clear_temp_buffer ();
void smooth_terrain ();
void smooth_selection ();
void clear_selection ();
void global_replace();

#endif
