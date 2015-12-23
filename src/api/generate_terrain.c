#include "generate_terrain.h"
#include "api.h"
#include "hme_lowlevel.h"

void setRandomHeight(Terrain *terrain, int x, int y) {
    int randomValue = rand() % 255;
    api_setHeight(terrain, x, y, randomValue);
}

int getRandomHeightOffset(int diffHeight) {
  if(diffHeight < 2) return 0;
  return rand() % (diffHeight / 2);
}

int getNewHeight2(int height1, int height2) {
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

int getNewHeight4(int height1, int height2, int height3, int height4) {
  int diffHeight = heightDifference(height1, height2, height3, height4);
  int randomDelta = getRandomHeightOffset(diffHeight);
  int calculation = (height1 + height2 + height3 + height4) / 4 + randomDelta;

  return calculation;
}

void drawMap(Terrain *terrain, int xtop, int ytop, int xbottom, int ybottom) {
  int midx = (xtop + xbottom) / 2;
  int midy = (ytop + ybottom) / 2;
  int difx = xbottom - xtop;
  int dify = ybottom - ytop;

  if (difx == 1 || dify == 1) return;

  int hTopLeft = getHeight(terrain, xtop, ytop);
  int hTopRight = getHeight(terrain, xbottom, ytop);
  int hBottomLeft = getHeight(terrain, xtop, ybottom);
  int hBottomRight = getHeight(terrain, xbottom, ybottom);

  api_setHeight(terrain, midx, midy, getNewHeight4(hTopLeft, hTopRight, hBottomLeft, hBottomRight));

  api_setHeight(terrain, xtop, midy, getNewHeight2(hTopLeft, hBottomLeft));
  api_setHeight(terrain, xbottom, midy, getNewHeight2(hTopRight, hBottomRight));
  api_setHeight(terrain, midx, ytop, getNewHeight2(hTopLeft, hTopRight));
  api_setHeight(terrain, midx, ybottom, getNewHeight2(hBottomLeft, hBottomRight));

  drawMap(terrain, xtop, ytop, midx, midy);
  drawMap(terrain, midx, ytop, xbottom, midy);
  drawMap(terrain, midx, midy, xbottom, ybottom);
  drawMap(terrain, xtop, midy, midx, ybottom);
}

int drawSeed(Terrain *terrain) {
  if(terrain->height < 2 || terrain->width < 2) {
      printf("[ERROR] The dimensions of the terrain are too small (%u x %u)\n", terrain->width, terrain->height);
      return 1;
  }

  int width = terrain->width - 1;
  int height = terrain->height - 1;

  setRandomHeight(terrain, 0, 0);
  setRandomHeight(terrain, 0, height);
  setRandomHeight(terrain, width, 0);
  setRandomHeight(terrain, width, height);

  return 0;
}

Terrain *api_generateRandomTerrain(int width, int height) {
    Terrain *terrain = api_generateTerrain(width, height);
    srand(terrain->seedRandom);

    int i, j;

    for(i =0; i < 9; i++) {
        for(j = 0; j < 9; j++) {
            setRandomHeight(terrain, i, j);
        }
    }
    /*int seedG = drawSeed(terrain);

    if(seedG == 0) {
        drawMap(terrain, 0, 0, terrain->width - 1, terrain->height - 1);
    }*/

    return terrain;
}
