#include "tools.h"

/*
This function gets the x and y of the height that is pointed by the mouse.
It returns 0, in case the mouse points to no pixel, otherwise return 1
*/
int get_cur_x_y () {
  if(!terrain_height)return 0;//we don't have a terrain
  cur_x = (x_mouse_pos - x_screen_offset) / terrain_ratio + xoffset;
  cur_y = (y_mouse_pos - y_screen_offset) / terrain_ratio + yoffset;

  if (cur_x >= 0 && cur_x < WIDTH && cur_y >= 0 && cur_y < HEIGHT)
    return 1;

  last_drawn_x = -1;
  last_drawn_y = -1;
  return 0;
}

void zoom_in () {
  if (terrain_ratio > 15) return;
  if (!get_cur_x_y ()) return;

  int some_x_lenght = (window_width / (terrain_ratio + 1)) / 2;
  int some_y_lenght = (window_height / (terrain_ratio + 1)) / 2;

  xoffset = (cur_x - some_x_lenght);
  yoffset = (cur_y - some_y_lenght);
  terrain_ratio++;
}

//the 'eye drop' tool, get the current pixel, under the mouse.
void pick_height (bool button_l, bool button_r) {
    if (!get_cur_x_y ()) return;

    color_1 = getHeight(terrain_height, cur_x, cur_y);
}

void select_area() {
	if (!get_cur_x_y ())return;

    //we already have a selection, kill it
	if(long_pressed_button_l==1 && selection_x_1!=-1) {
		selection_x_1=-1;
		selection_y_1=-1;
		selection_x_2=-1;
		selection_y_2=-1;
		return;
	}

	if(long_pressed_button_l==1 && selection_x_1==-1 && selection_y_1==-1) {
		selection_x_1=cur_x;
		selection_y_1=cur_y;
		return;
	}

	if(long_pressed_button_l!=0 && selection_x_1!=-1) {
		selection_x_2=cur_x;
		selection_y_2=cur_y;
	}
}

void put_pattern(Terrain * terrain, int x, int y) {
	int x_pattern = x % current_pattern.object_x_len;
	int y_pattern = y % current_pattern.object_y_len;
	int pattern_height = *(current_pattern.object_mem + y_pattern * current_pattern.object_x_len + x_pattern);

    if(pattern_height)
        modifyHeight(terrain, x, y, pattern_height, tolerance_replace_mode);
}

void replacePoint(Terrain *terrain, int x, int y, int tolerance_mode) {
    if(tolerance_mode == replace_mode_pattern)
        put_pattern(terrain, x, y);
    else
        modifyHeight(terrain, x, y, color_1, tolerance_replace_mode);
}

void modifyHeight(Terrain *terrain, int x, int y, int delta, int tolerance_mode) {
    switch(tolerance_mode) {
        case tolerance_replace_equal: api_setHeight(terrain, x, y, delta); break;
        case tolerance_replace_plus:  incHeight(terrain, x, y, delta); break;
        case tolerance_replace_minus: decHeight(terrain, x, y, delta); break;
    }
}

void updateMinMaxDrawnCoords(int x, int y) {
  //now, update the min and max drawn
  if (x < min_drawn_x) min_drawn_x = x;
  if (y < min_drawn_y) min_drawn_y = y;
  if (x > max_drawn_x) max_drawn_x = x;
  if (y > max_drawn_y) max_drawn_y = y;

  //11111111 11111111 11111111 11111100 wtf??
  //00000000 00000000 00000000 00000011 wtf??
  max_drawn_x = max_drawn_x & 0xfffc;
  min_drawn_x = min_drawn_x | 3;
}

void getTerrainCoords() {
    object_x_terrain_start = ((x_mouse_pos-x_screen_offset)-(current_object.object_x_len/2*terrain_ratio))/ terrain_ratio + xoffset;
    object_y_terrain_start = ((y_mouse_pos-y_screen_offset)-(current_object.object_y_len/2*terrain_ratio))/ terrain_ratio + yoffset;
    object_x_terrain_end = ((x_mouse_pos-x_screen_offset)+(current_object.object_x_len/2*terrain_ratio))/ terrain_ratio + xoffset;
    object_y_terrain_end = ((y_mouse_pos-y_screen_offset)+(current_object.object_y_len/2*terrain_ratio))/ terrain_ratio + yoffset;

    if(object_x_terrain_start<0) object_x_start=object_x_terrain_start * -1;
    if(object_y_terrain_start<0) object_y_start=object_y_terrain_start * -1;

    if(object_x_terrain_start<0) object_x_terrain_start = 0;
    if(object_y_terrain_start<0) object_y_terrain_start = 0;
    if(object_x_terrain_end>WIDTH) object_x_terrain_end = WIDTH;
    if(object_y_terrain_end>HEIGHT) object_y_terrain_end = HEIGHT;
}

void clearTempBuffer() {
  //see if we have to clear the temp buffer
  if(clear_temp_buffer && long_pressed_button_l == 1) {
		do_clear_temp_buffer ();
		clear_temp_buffer = 0;
		min_drawn_x = 0xffff;
		min_drawn_y = 0xffff;
		max_drawn_x = 0;
		max_drawn_y = 0;
  }
}
