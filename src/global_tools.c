#include "global_tools.h"

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
    //TODO API call
  /*int start_x, start_y, end_x, end_y;

  setStartAndEndCoords(&start_x, &start_y, &end_y, &end_x);
  riseSelection(terrain_height, start_x, start_y, end_x, end_y, color_1);*/
}

void sink_selection() {
    //TODO API call
  /*int start_x, start_y, end_x, end_y;

  setStartAndEndCoords(&start_x, &start_y, &end_y, &end_x);
  sinkSelection(terrain_height, start_x, start_y, end_x, end_y, color_1);*/
}

void clear_selection() {
    //TODO API call
  /*int start_x, start_y, end_x, end_y;

  setStartAndEndCoords(&start_x, &start_y, &end_y, &end_x);
  setHeightSelection(terrain_height, start_x, start_y, end_x, end_y, color_1);*/
}

void smooth_terrain() {
    /* TODO Api call
  if(!terrain_height)return;

  change_cursor(cursor_wait);
  smoothSelection(terrain_height, 1, 1, WIDTH - 1, HEIGHT - 1 , -1);
  change_cursor(last_cursor);*/
}

void smooth_selection() {
  /*TODO Api call
  int x, y, start_x,start_y,end_x,end_y,sum;
  if (!terrain_height)return;
  change_cursor(cursor_wait);

  setStartAndEndCoords(&start_x, &start_y, &end_y, &end_x);

  if(start_x==0) start_x = 1;
  if(start_y==0) start_y = 1;
  if(end_x==WIDTH) end_x = WIDTH - 1;
  if(end_y==HEIGHT) end_y = HEIGHT - 1;

  smoothSelection(terrain_height, start_x, start_y, end_x, end_y, -1);
  change_cursor(last_cursor);*/
}
