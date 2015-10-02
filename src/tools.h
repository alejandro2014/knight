#ifndef __TOOLS_H__
#define __TOOLS_H__

#include "global.h"

#define NOT_MODIFIED 0
#define MODIFIED 1

void draw_brush (int cur_x, int cur_y);

#define not_filled 0
#define pending_fill 1
#define already_filled 2

/*
This function gets the x and y of the height that is pointed by the mouse.
It returns 0, in case the mouse points to no pixel, otherwise return 1
*/
int get_cur_x_y ();

void zoom_in ();


//the 'eye drop' tool, get the current pixel, under the mouse.
void pick_height (bool button_l, bool button_r);

//the selection tool
void select_area();

void change_area (short x, short y);


//the fill tool
void pre_change_area ();


///////////////////////////////////////////////////////////////////////////
void flood_area (short x, short y);


//the fill tool
void pre_flood_area ();


///////////////////////////////////////////////////////////////////////////
void draw_brush_line ();


void draw_brush (int this_cur_x, int this_cur_y);

void stamp_object();

int getColour(Uint8 *terrain, int x, int y);
void setColour(Uint8 *terrain, int x, int y, int colour);

void incColour(Uint8 *terrain, int x, int y, int delta);
void decColour(Uint8 *terrain, int x, int y, int delta);
#endif
