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
    printf("sh(%u, %u).height = %u\n", x, y, height);
  hmeGetPoint(terrain, x, y)->z = height;
}

__inline unsigned int mrandom (unsigned int max) {
  //return (int) ((float) max * rand() / (RAND_MAX + 120.0));
  return (unsigned int) (rand() % max);
}

void setRandomHeight(Terrain *terrain, unsigned int x, unsigned y) {
  unsigned int terrainWidth = terrain->width;
  unsigned int maximum = 10;

  Point *point = terrain->points + (y * terrain->width + x);
  point->z = mrandom(maximum);

  printf("srh(%u, %u).height = %u\n", x, y, point->z);
}

unsigned int getNewHeight2(unsigned int height1, unsigned int height2, unsigned int diffHeight) {
  unsigned int MAX_HEIGHT = 512u;
  int randomDelta = mrandom(diffHeight) - diffHeight / 2u;
  unsigned int divisor = 2u;

  unsigned int thisHeight = (height1 + height2 + randomDelta);

  if(thisHeight < MAX_HEIGHT) divisor = 3u;

  thisHeight =  thisHeight / divisor;

  //printf("g2 - h1: %u h2: %u diff: %u rd: %u div: %u height: %u\n", height1, height2, diffHeight, randomDelta, divisor, thisHeight);

  return thisHeight;
}

unsigned int getNewHeight4(unsigned int height1, unsigned int height2, unsigned int height3, unsigned int height4, unsigned int diffHeight) {
  unsigned int MAX_HEIGHT = 1024u;
  int randomDelta = mrandom(diffHeight) - diffHeight / 2u;
  unsigned int divisor = 4u;

  unsigned int thisHeight = (height1 + height2 + height3 + height4 + randomDelta);
  if(thisHeight < MAX_HEIGHT) divisor = 5u;

  thisHeight =  thisHeight / divisor;

  //printf("g4 - h1: %d h2: %d h3: %d h4: %d diff: %d rd: %d div: %d height: %d\n", height1, height2, height3, height4, diffHeight, randomDelta, divisor, thisHeight);

  return thisHeight;
}

/*
  0   1   2   3   4
0 x--- --- --- ---x
  |   |   |   |   |
1  ---x--- --- ---
  |   |   |   |   |
2  --- ---x--- ---
  |   |   |   |   |
3  --- --- --- ---
  |   |   |   |   |
4 x--- --- --- ---x
*/
void hmeDrawMap(Terrain *terrain, unsigned int xtop, unsigned int ytop, unsigned int xbottom, unsigned int ybottom) {
  /*
  xtop    = 0  ytop    = 0
  xbottom = 1  ybottom = 1
  midx    = 0  midy    = 0
  difx    = 1  dify    = 1
  */
  unsigned int midx = (xtop + xbottom) / 2u;
  unsigned int midy = (ytop + ybottom) / 2u;
  unsigned int difx = xbottom - xtop;
  unsigned int dify = ybottom - ytop;

  if (difx == 1 || dify == 1) return;

  printf("[DEBUG] top = (%u, %u) bottom = (%u, %u) mid = (%u, %u) dif = (%u, %u)\n", xtop, ytop, xbottom, ybottom, midx, midy, difx, dify);

  unsigned int hTopLeft = hmeGetHeight(terrain, xtop, ytop);
  unsigned int hTopRight = hmeGetHeight(terrain, xbottom, ytop);
  unsigned int hBottomLeft = hmeGetHeight(terrain, xtop, ybottom);
  unsigned int hBottomRight = hmeGetHeight(terrain, xbottom, ybottom);

  unsigned int hMidTop = hmeGetHeight(terrain, midx, ytop);
  unsigned int hMidBottom = hmeGetHeight(terrain, midx, ybottom);
  unsigned int hMidLeft = hmeGetHeight(terrain, xtop, midy);
  unsigned int hMidRight = hmeGetHeight(terrain, xbottom, midy);

  hmeSetHeight(terrain, xtop, midy, getNewHeight2(hTopLeft, hBottomLeft, dify));
  hmeSetHeight(terrain, xbottom, midy, getNewHeight2(hTopRight, hBottomRight, dify));
  hmeSetHeight(terrain, midx, ytop, getNewHeight2(hTopLeft, hTopRight, difx));
  hmeSetHeight(terrain, midx, ybottom, getNewHeight2(hBottomLeft, hBottomRight, difx));

  hmeSetHeight(terrain, midx, midy, getNewHeight4(hMidLeft, hMidRight, hMidTop, hMidBottom, dify));

  //if (difx > 1 || dify > 1) {
    hmeDrawMap(terrain, xtop, ytop, midx, midy);
    hmeDrawMap(terrain, midx, ytop, xbottom, midy);
    hmeDrawMap(terrain, midx, midy, xbottom, ybottom);
    hmeDrawMap(terrain, xtop, midy, midx, ybottom);
  //}
}

int hmeDrawSeed(Terrain *terrain) {
  if(terrain->height < 2 || terrain->width < 2) {
      printf("[ERROR] The dimensions of the terrain are too small (%u x %u)\n", terrain->width, terrain->height);
      return 1;
  }

  int width = terrain->height - 1;
  int height = terrain->width - 1;

  setRandomHeight(terrain, 0u, 0u);
  setRandomHeight(terrain, 0u, height);
  setRandomHeight(terrain, width, 0u);
  setRandomHeight(terrain, width, height);

  return 0;
}

void printLine(int width) {
  int i;

  for(i = 0; i < width; i++) printf("+---");
  printf("+\n");
}

unsigned int valueCell(Terrain *terrain, int x, int y) {
  return hmeGetHeight(terrain, x, y);;
}

void showTerrainCmd(Terrain *terrain) {
  unsigned int i, j;
  unsigned int columns = terrain->width;
  unsigned int rows = terrain->height;

  for(i = 0; i < rows; i++) {
    printLine(columns);
    for(j = 0; j < columns; j++) {
      printf("| %u ", valueCell(terrain, j, i));
    }
    printf("|\n");
  }
  printLine(columns);

  Point *point;
  int pointsNo = terrain->pointsNo;

  for(i = 0; i < pointsNo; i++) {
    point = terrain->points + i;
    printf("points(%u) = (%u, %u, %u)\n", i, point->x, point->y, point->z);
  }
}

void generateRandomTerrain(Terrain *terrain) {
  int seedG = hmeDrawSeed(terrain);

  if(seedG == 0) {
  hmeDrawMap(terrain, 0, 0, terrain->width - 1, terrain->height - 1 );

  showTerrainCmd(terrain);
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
