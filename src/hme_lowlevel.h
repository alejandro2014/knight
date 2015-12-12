#ifndef HME_LOWLEVEL_H
#define HME_LOWLEVEL_H

#include "hme_lowlevel.h"
#include "terrain.h"

void setHeight(Terrain *terrain, int x, int y, int height);
void incHeight(int x, int y, int delta);
void decHeight(int x, int y, int delta);
int getHeight(Terrain *terrain, int x, int y);

int isFilled(int x, int y);
void setFilled(int x, int y);
void setPendingFill(int x, int y);
void setFillStatus(int x, int y, int fillStatus);

Point *getPoint(Terrain *terrain, int x, int y);

//TODO Visual functions (not belonging here)
int isPointInWindow(int x, int y);
void setPixel(int x, int y, int colour);
int getPixel(int x, int y);

#endif
