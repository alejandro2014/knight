#include "api.h"

void api_rotate(Terrain *terrain, int angle) {
    switch(angle) {
        case 90: rotate_90(terrain); break;
        case 180: rotate_180(terrain); break;
        case 270: rotate_270(terrain); break;
    }
}

/*
  0 1 2      0 1    1 2 3 5 6 7
0 1 2 3    0 5 1    5 1 6 2 7 3
1 5 6 7 -> 1 6 2
           2 7 3
*/
void rotate_90(Terrain *terrain) {
    Point *point = NULL;
    int x,y,map_offset;

    int oldVerSize = terrain->verSize;
    int oldHorSize = terrain->horSize;
    int verSize = oldHorSize;
    int horSize = oldVerSize;

    Terrain *newTerrain = generateTerrain(horSize, verSize);

    for(x = 0; x < horSize; x++) {
        for(y = 0; y < verSize; y++) {
            oldPoint = getPoint(oldTerrain, y, x);
            newPoint = getPoint(newTerrain, x, y);
            newPoint->height = oldPoint->height;
        }
    }

    free(terrain);
    terrain = newTerrain;
}

void rotate_180(Terrain *terrain) {
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

void rotate_270(Terrain *terrain) {
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
