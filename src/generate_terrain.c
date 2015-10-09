/*******************************************************
 * Parts of this code are stolen and modified from sdlplasma,
 * by Stefan Hellkvist, stefan@hellkvist.org
 * Copyright: see GPL
 *******************************************************/
#include "generate_terrain.h"

#include "cursors.h"

#include "actions_core.h"

Point *hmeGetPoint(Terrain *terrain, int x, int y) {
  return terrain->points + (y * terrain->width + x);
}

int hmeGetHeight(Terrain *terrain, int x, int y) {
    return hmeGetPoint(terrain, x, y)->z;
}

void hmeSetHeight(Terrain *terrain, int x, int y, int height) {
  hmeGetPoint(terrain, x, y)->z = height;
}

__inline int mrandom (int max) {
  return (int) ((float) max * rand () / (RAND_MAX + 120.0));
}

void setRandomHeight(Terrain *terrain, int x, int y) {
  int terrainWidth = terrain->width;
  int maximum = 255;

  Point *point = terrain->points + (y * terrain->width + x);
  point->z = mrandom(maximum);
}

int hmeGetNewHeightCorner(int height1, int height2, int diffHeight) {
  const int MAX_HEIGHT = 512;
  int randomDelta = (mrandom(diffHeight) - diffHeight / 2);

  int thisHeight = (height1 + height2 + randomDelta);
  thisHeight =  thisHeight / (thisHeight < MAX_HEIGHT ? 2: 3);

  return thisHeight;
}

int hmeGetNewHeightMiddle(int height1, int height2, int height3, int height4, int diffHeight) {
  const int MAX_HEIGHT = 1024;
  int randomDelta = (mrandom(diffHeight) - diffHeight / 2);

  int thisHeight = (height1 + height2 + height3 + height4 + randomDelta);
  thisHeight =  thisHeight / (thisHeight < MAX_HEIGHT ? 4: 5);

  return thisHeight;
}

void hmeDrawMap(Terrain *terrain, int x1, int y1, int x2, int y2) {
  int midx = (x1 + x2) / 2;
  int midy = (y1 + y2) / 2;

  hmeSetHeight (terrain, midx, y1, hmeGetNewHeightCorner(hmeGetHeight(terrain, x1, y1), hmeGetHeight(terrain, x2, y1), x2 - x1));
  hmeSetHeight (terrain, x2, midy, hmeGetNewHeightCorner(hmeGetHeight(terrain, x2, y1), hmeGetHeight(terrain, x2, y2), y2 - y1));
  hmeSetHeight (terrain, midx, y2, hmeGetNewHeightCorner(hmeGetHeight(terrain, x1, y2), hmeGetHeight(terrain, x2, y2), x2 - x1));
  hmeSetHeight (terrain, x1, midy, hmeGetNewHeightCorner(hmeGetHeight(terrain, x1, y1), hmeGetHeight(terrain, x1, y2), y2 - y1));
  hmeSetHeight (terrain, midx, midy,
    hmeGetNewHeightMiddle(
      hmeGetHeight(terrain, x1, midy),
      hmeGetHeight(terrain, x2, midy),
      hmeGetHeight(terrain, midx, y1),
      hmeGetHeight(terrain, midx, y2),
      y2 - y1));

  if (x2 > x1 + 1 || y2 > y1 + 1) {
    hmeDrawMap(terrain, x1, y1, midx, midy);
    hmeDrawMap(terrain, midx, y1, x2, midy);
    hmeDrawMap(terrain, midx, midy, x2, y2);
    hmeDrawMap(terrain, x1, midy, midx, y2);
  }
}

/*int make_terrain (int width, int height) {

  int map_size = width * height;

  if(!terrain_height)return 0;//we don't have a terrain
  change_cursor(cursor_wait);
  drawSeed_no_overwrite(width - 1, height - 1);
  drawMap (0, 0, width - 1, height - 1);
  change_cursor(last_cursor);
  return 1;
}*/

void hmeDrawSeed(Terrain *terrain) {
  int maxHeight = terrain->height - 1;
  int maxWidth = terrain->width - 1;

  setRandomHeight(terrain, 0, 0);
  setRandomHeight(terrain, 0, maxHeight);
  setRandomHeight(terrain, maxWidth, 0);
  setRandomHeight(terrain, maxWidth, maxHeight);
}

void generateRandomTerrain(Terrain *terrain) {
  hmeDrawSeed(terrain);
  hmeDrawMap(terrain, 0, 0, terrain->width - 1, terrain->height - 1);
}

/*---------------
Memory allocation
---------------*/
void allocate_mem(Terrain **terrains, int width, int height) {
  int map_size = width * height;

  freeMemTerrain(terrain_height);
  freeMemTerrain(temp_buffer);

  freeTerrain(*(terrains + TERRAIN_WORK));
  freeTerrain(*(terrains + TERRAIN_UNDO));
  freeTerrain(*(terrains + TERRAIN_TEMP));

  undo = no_undo;
  clear_temp_buffer = 0;//needed, otherwise it might crash next time you draw something

  *(terrains + TERRAIN_WORK) = generateTerrain(width, height);
  *(terrains + TERRAIN_UNDO) = generateTerrain(width, height);
  *(terrains + TERRAIN_TEMP) = generateTerrain(width, height);

  //TODO Check when the memory couldn't be created

  if(allocateMemTerrain2(&terrain_height, map_size) == -1 ||
     allocateMemTerrain2(&temp_buffer, map_size) == -1) {
    view_error_menu = 1;
    return;
  }
}

int allocateMemTerrain2(Uint8 **buffer, int map_size) {
  if(allocateMemTerrain(buffer, map_size) == -1) {
    sprintf(error_msg_1,"Not enough memory for the height map!");
    sprintf(error_msg_2,"Please use a smaller map size!");
    freeMemTerrain(*buffer);
    return -1;
  }

  return 0;
}

int allocateMemTerrain(Uint8 **buffer, int map_size) {
  *buffer = calloc ( map_size, sizeof(Uint8));

  if(*buffer) {
    memset(*buffer, 0, map_size);
    return 0;
  }

  return -1;
}

void freeMemTerrain(Uint8 *buffer) {
  if (buffer)
    free(buffer);
  buffer = NULL;
}
