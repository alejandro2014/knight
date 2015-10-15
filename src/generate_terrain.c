/*******************************************************
 * Parts of this code are stolen and modified from sdlplasma,
 * by Stefan Hellkvist, stefan@hellkvist.org
 * Copyright: see GPL
 *******************************************************/
#include "generate_terrain.h"

#include "cursors.h"

#include "actions_core.h"

int maxIterations = 10;
int iterator = 0;

Point *hmeGetPoint(Terrain *terrain, unsigned int x, unsigned int y) {
  return terrain->points + (y * terrain->width + x);
}

unsigned int hmeGetHeight(Terrain *terrain, unsigned int x, unsigned int y) {
    return (unsigned int) hmeGetPoint(terrain, x, y)->z;
}

void hmeSetHeight(Terrain *terrain, unsigned int x, unsigned int y, unsigned int height) {
  hmeGetPoint(terrain, x, y)->z = height;
}

__inline unsigned int mrandom (unsigned int max) {
  return (unsigned int) (rand() % max);
}

void setRandomHeight(Terrain *terrain, unsigned int x, unsigned y) {
  unsigned int terrainWidth = terrain->width;
  unsigned int maximum = 10;

  Point *point = terrain->points + (y * terrain->width + x);
  point->z = mrandom(maximum);
}

int getRandomHeightOffset(int diffHeight) {
  return (rand() % diffHeight) - diffHeight / 2u;
}

int getNewHeight2(int height1, int height2, int diffHeight) {
  int randomDelta = getRandomHeightOffset(diffHeight);
  return (height1 + height2) / 2 + randomDelta;
}

int getNewHeight4(int height1, int height2, int height3, int height4, int diffHeight) {
  int randomDelta = getRandomHeightOffset(diffHeight);
  return (height1 + height2 + height3 + height4) / 4 + randomDelta;
}

void hmeDrawMap(Terrain *terrain, unsigned int xtop, unsigned int ytop, unsigned int xbottom, unsigned int ybottom) {
  int midx = (xtop + xbottom) / 2u;
  int midy = (ytop + ybottom) / 2u;
  int difx = xbottom - xtop;
  int dify = ybottom - ytop;

  if (difx == 1 || dify == 1) return;

  int hTopLeft = hmeGetHeight(terrain, xtop, ytop);
  int hTopRight = hmeGetHeight(terrain, xbottom, ytop);
  int hBottomLeft = hmeGetHeight(terrain, xtop, ybottom);
  int hBottomRight = hmeGetHeight(terrain, xbottom, ybottom);

  int hMidTop = hmeGetHeight(terrain, midx, ytop);
  int hMidBottom = hmeGetHeight(terrain, midx, ybottom);
  int hMidLeft = hmeGetHeight(terrain, xtop, midy);
  int hMidRight = hmeGetHeight(terrain, xbottom, midy);

  hmeSetHeight(terrain, xtop, midy, getNewHeight2(hTopLeft, hBottomLeft, dify));
  hmeSetHeight(terrain, xbottom, midy, getNewHeight2(hTopRight, hBottomRight, dify));
  hmeSetHeight(terrain, midx, ytop, getNewHeight2(hTopLeft, hTopRight, difx));
  hmeSetHeight(terrain, midx, ybottom, getNewHeight2(hBottomLeft, hBottomRight, difx));

  hmeSetHeight(terrain, midx, midy, getNewHeight4(hMidLeft, hMidRight, hMidTop, hMidBottom, dify));

  hmeDrawMap(terrain, xtop, ytop, midx, midy);
  hmeDrawMap(terrain, midx, ytop, xbottom, midy);
  hmeDrawMap(terrain, midx, midy, xbottom, ybottom);
  hmeDrawMap(terrain, xtop, midy, midx, ybottom);
}

int hmeDrawSeed(Terrain *terrain) {
  if(terrain->height < 2 || terrain->width < 2) {
      printf("[ERROR] The dimensions of the terrain are too small (%u x %u)\n", terrain->width, terrain->height);
      return 1;
  }

  int width = terrain->height - 1;
  int height = terrain->width - 1;

  setRandomHeight(terrain, 0, 0);
  setRandomHeight(terrain, 0, height);
  setRandomHeight(terrain, width, 0);
  setRandomHeight(terrain, width, height);

  return 0;
}
/*
set four corners
calculate mid point
add random displacement
*/
void printLine(int width) {
  int i;

  for(i = 0; i < width; i++) printf("+---");
  printf("+\n");
}

unsigned int valueCell(Terrain *terrain, int x, int y) {
  return hmeGetHeight(terrain, x, y);;
}

void showTerrainCmd(Terrain *terrain) {
  int i, j;
  int columns = terrain->width;
  int rows = terrain->height;

  for(i = 0; i < rows; i++) {
    printLine(columns);
    for(j = 0; j < columns; j++) {
      printf("| %d ", valueCell(terrain, j, i));
    }
    printf("|\n");
  }
  printLine(columns);

  Point *point;
  int pointsNo = terrain->pointsNo;

  for(i = 0; i < pointsNo; i++) {
    point = terrain->points + i;
    printf("points(%u) = (%d, %d, %d)\n", i, point->x, point->y, point->z);
  }
}

int calculateHeightMiddlePoint(int x, int y, int randomInterval) {
    int height;

    return height;
}

/*void diamond(Terrain *terrain, int x, int y, int size, int offset) {
  int top = hmeGetHeight(terrain, x, y - size);
  int right = hmeGetHeight(terrain, x + size, y);
  int bottom = hmeGetHeight(terrain, x, y + size);
  int left = hmeGetHeight(terrain, x - size, y);

  var ave = average([
    self.get(x, y - size),      // top
    self.get(x + size, y),      // right
    self.get(x, y + size),      // bottom
    self.get(x - size, y)       // left
  ]);

  self.set(x, y, ave + offset);
}*/

/*void divide(size) {
  int x, y, half = size / 2;
  int scale = roughness * size;
  if (half < 1) return;

  for (y = half; y < 4; y += size) {
    for (x = half; x < 4; x += size) {
      square(x, y, half, Math.random() * scale * 2 - scale);
    }
  }
  for (y = 0; y <= self.max; y += half) {
    for (x = (y + half) % size; x <= self.max; x += size) {
      diamond(x, y, half, Math.random() * scale * 2 - scale);
    }
  }
  divide(size / 2);
}*/

void generateRandomTerrain(Terrain *terrain) {
  int seedG = hmeDrawSeed(terrain);

  if(seedG == 0) {
    hmeDrawMap(terrain, 0, 0, terrain->width - 1, terrain->height - 1);
    //showTerrainCmd(terrain);
  }
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
