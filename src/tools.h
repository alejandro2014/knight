#ifndef TOOLS_H
#define TOOLS_H

#include <math.h>
#include "global.h"

#define not_filled 0
#define pending_fill 1
#define already_filled 2

int get_cur_x_y();
void zoom_in();

void pick_height(bool button_l, bool button_r); //the 'eye drop' tool, get the current pixel, under the mouse.

void select_area(); //the selection tool
void change_area(short x, short y);

void pre_change_area(); //the fill tool

void draw_brush_line();
void draw_brush (int this_cur_x, int this_cur_y);

void stamp_object();
int isPointInWindow(int x, int y);

void clearTempBuffer();
void updateMinMaxDrawnCoords(int x, int y);

void calculateRectangleBrush(Rectangle *brush, int xcursor, int ycursor, int size);
void applyBrushInPixel(int x, int y);
#endif
