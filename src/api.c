#include "api.h"
#include "terrain.h"
#include "hme_lowlevel.h"

Terrain *api_rotate(Terrain *oldTerrain, int angle) {
    Terrain *newTerrain = NULL;

    switch(angle) {
        case 90: newTerrain = rotate_90(oldTerrain); break;
        case 180: newTerrain = rotate_180(oldTerrain); break;
        //case 270: rotate_270(terrain); break;
    }

    return newTerrain;
}

Terrain *rotate_90(Terrain *oldTerrain) {
    int x, y;
    int width = oldTerrain->height;
    int height = oldTerrain->width;
    int newHeight;

    Terrain *newTerrain = generateTerrain(width, height);

    for(x = 0; x < width; x++) {
        for(y = 0; y < height; y++) {
            newHeight = getHeight(oldTerrain, y, width - x - 1);
            setHeight(newTerrain, x, y, newHeight);
        }
    }

    freeTerrain(oldTerrain);
    oldTerrain = NULL;

    return newTerrain;
}

/*
A      B
0 1 2  5 4 3
3 4 5  2 1 0

*/
Terrain *rotate_180(Terrain *oldTerrain) {
    int x, y;
    int height = oldTerrain->height;
    int width = oldTerrain->width;
    int newHeight;

    Terrain *newTerrain = generateTerrain(width, height);

    for(x = 0; x < width; x++) {
        for(y = 0; y < height; y++) {
            printf("b[%d, %d] = a [%d, %d]\n", x, y, height - y - 1, width - x - 1);
            newHeight = getHeight(oldTerrain, width - x - 1, height - y - 1);
            setHeight(newTerrain, x, y, newHeight);
        }
    }

    freeTerrain(oldTerrain);
    oldTerrain = NULL;

    return newTerrain;
}

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
