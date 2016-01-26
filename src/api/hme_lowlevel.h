#ifndef HME_LOWLEVEL_H
#define HME_LOWLEVEL_H

#include <stdlib.h>
#include "api.h"

char *api_setHeight(Terrain **terrain, int x, int y, int height);
void incHeight(Terrain *terrain, int x, int y, int delta);
void decHeight(Terrain *terrain, int x, int y, int delta);
int getHeight(Terrain *terrain, int x, int y);

bool isFilled(Terrain *terrain, int x, int y);
void setFilled(Terrain *terrain, int x, int y);
void setPendingFill(Terrain *terrain, int x, int y);
void setFillStatus(Terrain *terrain, int x, int y, int fillStatus);

Point *getPoint(Terrain *terrain, int x, int y);

#endif
