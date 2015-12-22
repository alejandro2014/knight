#ifndef GENERATE_TERRAIN_H
#define GENERATE_TERRAIN_H

#include "../global.h"
#include "api.h"

Terrain *api_generateRandomTerrain(int width, int height);
int drawSeed(Terrain *terrain);

void setRandomHeight(Terrain *terrain, int x, int y);
int getRandomHeightOffset(int diffHeight);
int getNewHeight2(int height1, int height2);
int getNewHeight4(int height1, int height2, int height3, int height4);
int heightDifference(int h1, int h2, int h3, int h4);
void drawMap(Terrain *terrain, int xtop, int ytop, int xbottom, int ybottom);

#endif
