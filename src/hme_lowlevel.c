#include "hme_lowlevel.h"
#include "terrain.h"
#include "global.h"

#include <stdlib.h>

Terrain *currentTerrain = NULL;

void setHeight(Terrain *terrain, int x, int y, int height) {
    Point *point = getPoint(terrain, x, y);
    //if(point->isHeightSetted) return;

    //countPoints++;
    point->z = height;
    //point->isHeightSetted = true;
}

int getHeight(Terrain *terrain, int x, int y) {
    Point *point = getPoint(terrain, x, y);
    return point->z;
}

void incHeight(Terrain *terrain, int x, int y, int delta) {
    int newHeight = getHeight(terrain, x, y) + delta;
    setHeight(terrain, x, y, (newHeight < MAX_HEIGHT ? newHeight : MAX_HEIGHT));
}

void decHeight(Terrain *terrain, int x, int y, int delta) {
    int newHeight = getHeight(terrain, x, y) - delta;
    setHeight(terrain, x, y, (newHeight > MIN_HEIGHT ? newHeight : MIN_HEIGHT));
}

int isFilled(int x, int y) {
    /*Terrain *terrain = currentTerrain;
    Point *point = getPoint(terrain, x, y);
    return point->fillStatus == already_filled ? 1 : 0;*/
    return 1;
}

void setFilled(int x, int y) {
    //setFillStatus(x, y, already_filled);
}

void setPendingFill(int x, int y) {
    //setFillStatus(x, y, pending_filled);
}

void setFillStatus(int x, int y, int fillStatus) {
    /*Terrain *terrain = currentTerrain;
    Point *point = getPoint(terrain, x, y);
    point->fillStatus = fillStatus;*/
}

Point *getPoint(Terrain *terrain, int x, int y) {
    return terrain->points + (y * terrain->width + x);
}

//====================
int isPointInWindow(int x, int y) {
  //return (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT) ? 1 : 0;
  return 0;
}

void setPixel(int x, int y, int colour) {
    /*currentScreen = NULL;
    *((Uint32 *)currentScreen->pixels + y * currentScreen->w + x) = colour;*/
}

int getPixel(int x, int y) {
    return 0;
}

/*
void setHeight(Point *point, int height) {
  point->z = height;
}*/
