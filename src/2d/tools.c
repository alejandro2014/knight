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

void new_terrain_menu () {
  show_new_terrain_menu = 1;
  sprintf (numeric_dialog_boxes[x_map_size_dialog].dialog_text, "%d", WIDTH);
  sprintf (numeric_dialog_boxes[y_map_size_dialog].dialog_text, "%d", HEIGHT);
  sprintf (numeric_dialog_boxes[base_height_dialog].dialog_text, "%d",
  numeric_dialog_boxes[base_height_dialog].current_number);
}

void generate_menu (int seed) {
  show_generate_terrain_menu = 1;
  sprintf (numeric_dialog_boxes[seed_dialog].dialog_text, "%d", seed);
  numeric_dialog_boxes[seed_dialog].text_offset = 0;
  change_cursor(cursor_arrow);
}

void do_clear_temp_buffer () {
  int x, y;
  int *temp_buffer_pointer = (int *) temp_buffer;
  temp_buffer_pointer += (WIDTH * min_drawn_y + min_drawn_x) / 4;

  for (y = min_drawn_y; y <= max_drawn_y; y++) {
    for (x = min_drawn_x / 4; x <= max_drawn_x / 4; x++)
      *(temp_buffer_pointer++) = 0;

    temp_buffer_pointer += (WIDTH - (max_drawn_x - min_drawn_x) - 4) / 4;
  }
}

void global_replace(Terrain *terrain) {
    int x, y;
    int cur_height;

    if(global_tolerance_replace_mode_2 == replace_mode_pattern && !current_pattern.object_mem) {
        printf("Pattern filling mode, but there is no pattern!");
        printf("Please select a pattern!");
        view_error_menu=1;
        return;
    }

    change_cursor(cursor_wait);
    color_2 = getHeight(terrain_height, cur_x, cur_y);

    for(x = 0; x < terrain->width; x++) {
        for(y = 0; y < terrain->height; y++) {
            cur_height = getHeight(terrain_height, x, y);

            //check to see if we got a match
            if ((global_tolerance_mode == greater && cur_height>=color_2 && cur_height<=color_2+global_tolerance_value) ||
                (global_tolerance_mode == leaser && cur_height<=color_2 && cur_height>=color_2-global_tolerance_value) ||
                (global_tolerance_mode == greater_or_leaser && cur_height>=color_2 - global_tolerance_value && cur_height<=color_2 + global_tolerance_value)) {

                replacePoint(terrain, x, y, global_tolerance_replace_mode_2);
            }
        }
    }
    change_cursor(last_cursor);
}

void setStartAndEndCoords(int *startX, int *endX, int *startY, int *endY) {
  setStartAndEndCoord(startX, endX, selection_x_1, selection_x_2);
  setStartAndEndCoord(startY, endY, selection_y_1, selection_y_2);
}

void setStartAndEndCoord(int *startValue, int *endValue, int value1, int value2) {
  if(value1 < value2) {
	  *startValue = value1;
	  *endValue = value2;
	} else {
	  *startValue = value2;
	  *endValue = value1;
	}
}

void rise_selection () {
    int start_x, start_y, end_x, end_y;

    setStartAndEndCoords(&start_x, &start_y, &end_y, &end_x);
    api_riseSelection(terrain_height, start_x, start_y, end_x, end_y, color_1);
}

void sink_selection() {
    int start_x, start_y, end_x, end_y;

    setStartAndEndCoords(&start_x, &start_y, &end_y, &end_x);
    api_sinkSelection(terrain_height, start_x, start_y, end_x, end_y, color_1);
}

void clear_selection() {
    int start_x, start_y, end_x, end_y;

    setStartAndEndCoords(&start_x, &start_y, &end_y, &end_x);
    api_setHeightSelection(terrain_height, start_x, start_y, end_x, end_y, color_1);
}

void smooth_terrain() {
  if(!terrain_height)return;

  change_cursor(cursor_wait);
  api_smoothSelection(terrain_height, 1, 1, WIDTH - 1, HEIGHT - 1 , -1);
  change_cursor(last_cursor);
}

void smooth_selection() {
  int x, y, start_x,start_y,end_x,end_y,sum;
  if (!terrain_height)return;
  change_cursor(cursor_wait);

  setStartAndEndCoords(&start_x, &start_y, &end_y, &end_x);

  if(start_x==0) start_x = 1;
  if(start_y==0) start_y = 1;
  if(end_x==WIDTH) end_x = WIDTH - 1;
  if(end_y==HEIGHT) end_y = HEIGHT - 1;

  api_smoothSelection(terrain_height, start_x, start_y, end_x, end_y, -1);
  change_cursor(last_cursor);
}
