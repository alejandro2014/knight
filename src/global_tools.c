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
  int i,x,y;
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

  for (i = 0; i < map_size; i++) {
  	cur_height=*(terrain_height + i);
  	//check to see if we got a match
		if ((global_tolerance_mode == greater &&
		    cur_height>=color_2 && cur_height<=color_2+global_tolerance_value) ||
		    (global_tolerance_mode == leaser &&
		    cur_height<=color_2 && cur_height>=color_2-global_tolerance_value) ||
		    (global_tolerance_mode == greater_or_leaser &&
		    cur_height>=color_2-global_tolerance_value && cur_height<=color_2+global_tolerance_value))
		{
			if(global_tolerance_replace_mode_2 == replace_mode_pattern) {
				y=i/WIDTH;
				x=i%WIDTH;
				put_pattern(terrain_height+i,x,y);
			}
			else {
			    if(global_tolerance_replace_mode==tolerance_replace_equal)
						 *(terrain_height+i)=color_1;
					else
						if(global_tolerance_replace_mode==tolerance_replace_plus) {
							if(*(terrain_height+i) + color_1 > 255)
                *(terrain_height+i) = 255;
							else
                *(terrain_height+i) += color_1;
						}
						else if(global_tolerance_replace_mode==tolerance_replace_minus) {
							if(*(terrain_height+i)-color_1 < 0)
                *(terrain_height+i) = 0;
							else
                *(terrain_height+i) -= color_1;
						}
					}
			}
	}

  change_cursor(last_cursor);
}

void rise_terrain() {
  int x, y;
  int map_size=WIDTH*HEIGHT;
  if(!terrain_height)return;
  change_cursor(cursor_wait);

  for (y = 0; y < HEIGHT; y++) {
    for (x = 0; x < WIDTH; x++) {
        increaseColor(x, y, color_1);
    }
  }

  change_cursor(last_cursor);
}

void sink_terrain () {
  int x, y;
  int map_size=WIDTH*HEIGHT;
  if (!terrain_height)return;
  change_cursor(cursor_wait);

  for (y = 0; y < HEIGHT; y++) {
    for (x = 0; x < WIDTH; x++) {
        decreaseColor(x, y, color_1);
    }
  }

  change_cursor(last_cursor);
}

void flip_z() {
  int i;
  int map_size=WIDTH*HEIGHT;
  if (!terrain_height)return;

  change_cursor(cursor_wait);

  for (i = 0; i < map_size; i++)
    *(terrain_height + i) = 0 - *(terrain_height + i);

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

void rotate_90_CW() {
  int x,y,map_offset,old_height,old_width;
  int map_size=WIDTH*HEIGHT;
  if (!terrain_height)return;
  change_cursor(cursor_wait);

  old_height=HEIGHT;
  old_width=WIDTH;
  HEIGHT=WIDTH;
  WIDTH=old_height;
  map_offset=0;
  for (y = 0; y<old_height; y++) {
		map_offset=old_height-1-y;

		for (x = 0; x<old_width; x++) {
		  map_offset+=WIDTH;
		}
	}

	undo=total_undo_swap_x_y;
	change_cursor(last_cursor);
}

void rotate_90_CCW() {
  int x,y,map_offset,old_height,old_width;
  int map_size=WIDTH*HEIGHT;
  if (!terrain_height)return;
  change_cursor(cursor_wait);

  old_height=HEIGHT;
  old_width=WIDTH;
  HEIGHT=WIDTH;
  WIDTH=old_height;
  map_offset=0;
  for (y = 0; y<old_height; y++) {
		map_offset=y;

		for (x = 0; x<old_width; x++) {
		  map_offset+=WIDTH;
		}
	}

	change_cursor(last_cursor);
}

void rotate_180() {
  int x,y,map_offset;
  int map_size=WIDTH*HEIGHT;
  if (!terrain_height)return;
  change_cursor(cursor_wait);

  for (y = 0; y<HEIGHT; y++) {
		map_offset=(y+1)*WIDTH-1;

		for (x = 0; x<WIDTH; x++) {
			map_offset--;
		}
	}

  change_cursor(last_cursor);
}

void smooth_terrain() {
  int x, y, sum;
  if(!terrain_height)return;
  change_cursor(cursor_wait);

  for (y = 1; y < HEIGHT - 1; y++)
    for (x = 1; x < WIDTH - 1; x++) {
      sum = *(terrain_height + y * WIDTH + x);
      sum += *(terrain_height + ((y - 1) * WIDTH) + x - 1);
      sum += *(terrain_height + ((y - 1) * WIDTH) + x);
      sum += *(terrain_height + ((y - 1) * WIDTH) + x + 1);
      sum += *(terrain_height + (y * WIDTH) + x - 1);
      sum += *(terrain_height + (y * WIDTH) + x + 1);
      sum += *(terrain_height + ((y + 1) * WIDTH) + x - 1);
      sum += *(terrain_height + ((y + 1) * WIDTH) + x);
      sum += *(terrain_height + ((y + 1) * WIDTH) + x + 1);

      sum = (sum / 9) + (sum % 9 > 4) ? 1 : 0;

      *(terrain_height + y * WIDTH + x) = sum;
    }
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

  for (y = start_y; y < end_y; y++)
    for (x = start_x; x < end_x; x++) {
      sum = *(terrain_height + y * WIDTH + x);
      sum += *(terrain_height + ((y - 1) * WIDTH) + x - 1);
      sum += *(terrain_height + ((y - 1) * WIDTH) + x);
      sum += *(terrain_height + ((y - 1) * WIDTH) + x + 1);
      sum += *(terrain_height + (y * WIDTH) + x - 1);
      sum += *(terrain_height + (y * WIDTH) + x + 1);
      sum += *(terrain_height + ((y + 1) * WIDTH) + x - 1);
      sum += *(terrain_height + ((y + 1) * WIDTH) + x);
      sum += *(terrain_height + ((y + 1) * WIDTH) + x + 1);

      sum = (sum / 9) + (sum % 9 > 4) ? 1 : 0;

      *(terrain_height + y * WIDTH + x) = sum;
    }
	change_cursor(last_cursor);
}

void rise_selection () {
  int x, y, start_x,start_y,end_x,end_y,cur_height;
  if (!terrain_height)return;
  change_cursor(cursor_wait);

  setStartAndEndCoords(&start_x, &start_y, &end_y, &end_x);

  for (y = start_y; y < end_y; y++) {
    for (x = start_x; x < end_x; x++) {
        increaseColor(x, y, color_1);
    }
  }
  change_cursor(last_cursor);
}

void sink_selection() {
  int x, y, start_x,start_y,end_x,end_y,cur_height;
  if (!terrain_height)return;
  change_cursor(cursor_wait);

  setStartAndEndCoords(&start_x, &start_y, &end_y, &end_x);

  for (y = start_y; y < end_y; y++) {
    for (x = start_x; x < end_x; x++) {
        decreaseColor(x, y, color_1);
    }
  }
  change_cursor(last_cursor);
}

void clear_selection() {
  int x, y, start_x,start_y,end_x,end_y,cur_height;
  if (!terrain_height)return;
  change_cursor(cursor_wait);

  setStartAndEndCoords(&start_x, &start_y, &end_y, &end_x);

  for (y = start_y; y < end_y; y++)
    for (x = start_x; x < end_x; x++)
      *(terrain_height + y * WIDTH + x) = color_1;

  change_cursor(last_cursor);
}

void setStartAndEndCoord(int *startX, int *endX, int *startY, int *endY) {
  setStartAndEndCoords(startX, endX, selection_x_1, selection_x_2);
  setStartAndEndCoords(startY, endY, selection_y_1, selection_y_2);
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

void increaseColor(int x, int y, int delta) {
  int *currentPoint = terrain_height + y * WIDTH + x;
  int nextHeight = *currentPoint + delta;

  *currentPoint = (nextHeight < 255) ? nextHeight : 255;
}

void decreaseColor(int x, int y, int delta) {
  int *currentPoint = terrain_height + y * WIDTH + x;
  int nextHeight = *currentPoint - delta;

  *currentPoint = (nextHeight > 0) ? nextHeight : 0;
}
