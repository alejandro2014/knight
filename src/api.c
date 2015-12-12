#include "api.h"
#include "terrain.h"
#include "hme_lowlevel.h"

Terrain *api_rotate(Terrain *oldTerrain, int angle) {
    Terrain *newTerrain = NULL;

    switch(angle) {
        case 90: newTerrain = rotate_90(oldTerrain); break;
        //case 180: rotate_180(terrain); break;
        //case 270: rotate_270(terrain); break;
    }

    return newTerrain;
}

/*
                1 2 3 5 6 7
1 2 3    5 1    5 1 6 2 7 3
5 6 7 -> 6 2
         7 3
*/
Terrain *rotate_90(Terrain *oldTerrain) {
    Point *oldPoint = NULL;
    Point *newPoint = NULL;
    int x,y,map_offset;

    int oldHeight = oldTerrain->height;
    int oldWidth = oldTerrain->width;
    int width = oldHeight;
    int height = oldWidth;

    int newHeight;

    Terrain *newTerrain = generateTerrain(width, height);

    for(x = 0; x < width; x++) {
        for(y = 0; y < height; y++) {
            newHeight = getHeight(oldTerrain, y, 1-x);
            printf("n[%d, %d] = o[%d, %d](%d) - ", x, y, y, x, newHeight);
            setHeight(newTerrain, x, y, newHeight);
            printf("%d\n", getHeight(newTerrain, x, y));
        }
    }

    freeTerrain(oldTerrain);

    return newTerrain;
}

/*void rotate_180(Terrain *terrain) {
  int x,y,map_offset;
  int map_size=WIDTH*HEIGHT;
  if (!terrain_height)return;

  for (y = 0; y<HEIGHT; y++) {
		map_offset=(y+1)*WIDTH-1;

		for (x = 0; x<WIDTH; x++) {
			map_offset--;
		}
	}
}*/

/*void rotate_270(Terrain *terrain) {
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
}*/
