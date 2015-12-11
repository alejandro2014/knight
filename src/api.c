#include "api.h"

void api_rotate(int angle) {
    switch(angle) {
        case 90: rotate_90(); break;
        case 180: rotate_180(); break;
        case 270: rotate_270(); break;
    }
}

void rotate_90() {
  int x,y,map_offset,old_height,old_width;
  int map_size=WIDTH*HEIGHT;
  if (!terrain_height)return;

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
}

void rotate_180() {
  int x,y,map_offset;
  int map_size=WIDTH*HEIGHT;
  if (!terrain_height)return;

  for (y = 0; y<HEIGHT; y++) {
		map_offset=(y+1)*WIDTH-1;

		for (x = 0; x<WIDTH; x++) {
			map_offset--;
		}
	}
}

void rotate_270() {
  int x,y,map_offset,old_height,old_width;
  int map_size=WIDTH*HEIGHT;
  if (!terrain_height)return;

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
}
