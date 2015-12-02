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
int countPoints = 0;

__inline unsigned int mrandom (unsigned int max) {
  int value = (rand() % max);
  unsigned int value2 = (unsigned int) (rand() % max);
  return value2;
}

void setRandomHeight(Terrain *terrain, Uint32 x, Uint32 y) {
  Uint32 randomValue = mrandom(255);
  hmeSetHeight(terrain, x, y, randomValue);
}

int getRandomHeightOffset(int diffHeight) {
  if(diffHeight < 2) return 0;
  return rand() % (diffHeight / 2);
}

Uint32 getNewHeight2(int height1, int height2) {
  int diffHeight = abs(height1 - height2);
  int randomDelta = getRandomHeightOffset(diffHeight);
  int calculation = (height1 + height2) / 2 + randomDelta;

  return calculation;
}

int heightDifference(int h1, int h2, int h3, int h4) {
    int min = 256;
    int max = -1;

    if(h1 > max) max = h1; if(h2 > max) max = h2;
    if(h3 > max) max = h3; if(h4 > max) max = h4;
    if(h1 < min) min = h1; if(h2 < min) min = h2;
    if(h3 < min) min = h3; if(h4 < min) min = h4;

    return abs(max - min);
}

Uint32 getNewHeight4(int height1, int height2, int height3, int height4) {
  int diffHeight = heightDifference(height1, height2, height3, height4);
  int randomDelta = getRandomHeightOffset(diffHeight);
  int calculation = (height1 + height2 + height3 + height4) / 4 + randomDelta;

  return calculation;
}

void hmeDrawMap(Terrain *terrain, int xtop, int ytop, int xbottom, int ybottom) {
  int midx = (xtop + xbottom) / 2;
  int midy = (ytop + ybottom) / 2;
  int difx = xbottom - xtop;
  int dify = ybottom - ytop;

  if (difx == 1 || dify == 1) return;

  int hTopLeft = hmeGetHeight(terrain, xtop, ytop);
  int hTopRight = hmeGetHeight(terrain, xbottom, ytop);
  int hBottomLeft = hmeGetHeight(terrain, xtop, ybottom);
  int hBottomRight = hmeGetHeight(terrain, xbottom, ybottom);

  hmeSetHeight(terrain, midx, midy, getNewHeight4(hTopLeft, hTopRight, hBottomLeft, hBottomRight));

  hmeSetHeight(terrain, xtop, midy, getNewHeight2(hTopLeft, hBottomLeft));
  hmeSetHeight(terrain, xbottom, midy, getNewHeight2(hTopRight, hBottomRight));
  hmeSetHeight(terrain, midx, ytop, getNewHeight2(hTopLeft, hTopRight));
  hmeSetHeight(terrain, midx, ybottom, getNewHeight2(hBottomLeft, hBottomRight));

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

  Uint32 width = terrain->width - 1;
  Uint32 height = terrain->height - 1;

  setRandomHeight(terrain, 0u, 0u);
  setRandomHeight(terrain, 0u, height);
  setRandomHeight(terrain, width, 0);
  setRandomHeight(terrain, width, height);

  return 0;
}

void generateRandomTerrain(Terrain *terrain) {
  int seedG = hmeDrawSeed(terrain);

  if(seedG == 0) {
    hmeDrawMap(terrain, 0, 0, terrain->width - 1, terrain->height - 1);
  }

  printf("setted the height %d times\n", countPoints);
}

void printLine(int width) {
  int i;

  for(i = 0; i < width; i++) printf("+-----");
  printf("+\n");
}

void showTerrainCmd(Terrain *terrain) {
  int i, j;
  int columns = terrain->width;
  int rows = terrain->height;
  int value;

  for(i = 0; i < rows; i++) {
    printLine(columns);
    for(j = 0; j < columns; j++) {
      printf("| ");
      value = valueCell(terrain, j, i);
      if(value < 100) printf(" ");
      if(value < 10) printf(" ");
      printf("%d ", value);
    }
    printf("|\n");
  }
  printLine(columns);

  Point *point;
  int pointsNo = terrain->pointsNo;

  for(i = 0; i < pointsNo; i++) {
    point = terrain->points + i;
    //printf("points(%u) = (%d, %d, %d)\n", i, point->x, point->y, point->z);
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
