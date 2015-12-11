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

void global_replace() {
    int x,y;
    int cur_height;
    int map_size=WIDTH*HEIGHT;

    if(!terrain_height || !get_cur_x_y())return;

    if(global_tolerance_replace_mode_2==replace_mode_pattern) {
        if(!current_pattern.object_mem) {
            sprintf(error_msg_1,"Pattern filling mode, but there is no pattern!");
            sprintf(error_msg_2,"Please select a pattern!");
            view_error_menu=1;
            return;
        }
    }

    change_cursor(cursor_wait);
    color_2 = *(terrain_height + cur_y * WIDTH + cur_x);	//get the deepth

    for(x = 0; x < WIDTH; x++) {
        for(y = 0; y < HEIGHT; y++) {
            cur_height = *(terrain_height + y * WIDTH + x);

            //check to see if we got a match
            if ((global_tolerance_mode == greater && cur_height>=color_2 && cur_height<=color_2+global_tolerance_value) ||
                (global_tolerance_mode == leaser && cur_height<=color_2 && cur_height>=color_2-global_tolerance_value) ||
                (global_tolerance_mode == greater_or_leaser && cur_height>=color_2 - global_tolerance_value && cur_height<=color_2 + global_tolerance_value)) {

                if(global_tolerance_replace_mode_2 == replace_mode_pattern) {
                    put_pattern(terrain_height, x, y);
                } else {
                    switch(global_tolerance_mode) {
                        case tolerance_replace_equal: setHeight(terrain_height, x, y, color_1); break;
                        case tolerance_replace_plus: risePoint(terrain_height, x, y, color_1); break;
                        case tolerance_replace_minus: sinkPoint(terrain_height, x, y, color_1); break;
                    }
                }
            }
        }
    }
    change_cursor(last_cursor);
}

void flip_z() {
  int i;
  int map_size=WIDTH*HEIGHT;
  if (!terrain_height)return;

  change_cursor(cursor_wait);

  for(x = 0; x < WIDTH; x++) {
      for(y = 0; y < HEIGHT; y++) {
          currentHeight = getHeight(x, y);
          setHeight(x, y, -currentHeight);
      }
  }

  change_cursor(last_cursor);
}

void flip_y() {
    int x,y,map_offset;
    int map_size=WIDTH*HEIGHT;
    if (!terrain_height)return;
    change_cursor(cursor_wait);

    for (y = 0; y<HEIGHT; y++) {
        map_offset=y*WIDTH;

	    for (x = 0; x<WIDTH; x++) {
            map_offset++;
	    }
    }

    change_cursor(last_cursor);
}

void flip_x() {
  int x,y,map_offset;
  int map_size=WIDTH*HEIGHT;
  if (!terrain_height)return;
  change_cursor(cursor_wait);

  for (y = 0; y<HEIGHT; y++) {
		map_offset=y*WIDTH;

		for (x = 0; x<WIDTH; x++) {
			map_offset++;
		}
	}
  change_cursor(last_cursor);
}

void smooth_terrain() {
  if(!terrain_height)return;

  change_cursor(cursor_wait);
  smoothSelection(terrain_height, 1, 1, WIDTH - 1, HEIGHT - 1 , -1);
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

  smoothSelection(terrain_height, start_x, start_y, end_x, end_y, -1);
  change_cursor(last_cursor);
}

void rise_terrain() {
  if(!terrain_height)return;

  change_cursor(cursor_wait);
  riseSelection(terrain_height, 0, 0, WIDTH, HEIGHT, color_1);
  change_cursor(last_cursor);
}

void sink_terrain() {
  if (!terrain_height)return;

  change_cursor(cursor_wait);
  sinkSelection(terrain_height, 0, 0, WIDTH, HEIGHT, color_1);
  change_cursor(last_cursor);
}

void rise_selection () {
  int start_x, start_y, end_x, end_y;
  if (!terrain_height)return;

  change_cursor(cursor_wait);

  setStartAndEndCoords(&start_x, &start_y, &end_y, &end_x);
  riseSelection(terrain_height, start_x, start_y, end_x, end_y, color_1);

  change_cursor(last_cursor);
}

void sink_selection() {
  int start_x, start_y, end_x, end_y;
  if (!terrain_height)return;

  change_cursor(cursor_wait);

  setStartAndEndCoords(&start_x, &start_y, &end_y, &end_x);
  sinkSelection(terrain_height, start_x, start_y, end_x, end_y, color_1);

  change_cursor(last_cursor);
}

void clear_selection() {
  int start_x, start_y, end_x, end_y;
  if (!terrain_height)return;
  change_cursor(cursor_wait);

  setStartAndEndCoords(&start_x, &start_y, &end_y, &end_x);
  setHeightSelection(terrain_height, start_x, start_y, end_x, end_y, color_1);

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

void smoothSelection(Uint8 *terrain, int startX, int startY, int endX, int endY, int uselessParam) {
    int x, y;
    int sum;

    for (y = startY; y < endY; y++) {
        for (x = startX; x < endX; x++) {
            sum = *(terrain + y * WIDTH + x);
            sum += *(terrain + ((y - 1) * WIDTH) + x - 1);
            sum += *(terrain + ((y - 1) * WIDTH) + x);
            sum += *(terrain + ((y - 1) * WIDTH) + x + 1);
            sum += *(terrain + (y * WIDTH) + x - 1);
            sum += *(terrain + (y * WIDTH) + x + 1);
            sum += *(terrain + ((y + 1) * WIDTH) + x - 1);
            sum += *(terrain + ((y + 1) * WIDTH) + x);
            sum += *(terrain + ((y + 1) * WIDTH) + x + 1);

            sum = (sum / 9) + (sum % 9 > 4) ? 1 : 0;

            setHeight(terrain, x, y, sum);
        }
    }
}

void riseSelection(Uint8 *terrain, int startX, int startY, int endX, int endY, int height) {
  int x, y;

  for (y = startY; y < endY; y++) {
    for (x = startX; x < endX; x++) {
        risePoint(terrain, x, y, height);
    }
  }
}

void sinkSelection(Uint8 *terrain, int startX, int startY, int endX, int endY, int height) {
  int x, y;

  for (y = startY; y < endY; y++) {
    for (x = startX; x < endX; x++) {
        sinkPoint(terrain, x, y, height);
    }
  }
}

void setHeightSelection(Uint8 *terrain, int startX, int startY, int endX, int endY, int height) {
  int x, y;

  for (y = startY; y < endY; y++) {
    for (x = startX; x < endX; x++) {
        setHeight(terrain, x, y, height);
    }
  }
}
