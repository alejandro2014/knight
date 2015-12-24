#include "hme_lowlevel.h"
#include "api.h"
#include "../global.h"

void api_setHeight(Terrain *terrain, int x, int y, int height) {
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
    api_setHeight(terrain, x, y, (newHeight < MAX_HEIGHT ? newHeight : MAX_HEIGHT));
}

void decHeight(Terrain *terrain, int x, int y, int delta) {
    int newHeight = getHeight(terrain, x, y) - delta;
    api_setHeight(terrain, x, y, (newHeight > MIN_HEIGHT ? newHeight : MIN_HEIGHT));
}

bool isFilled(Terrain *terrain, int x, int y) {
    Point *point = getPoint(terrain, x, y);
    return point->fillStatus == FILLED ? true : false;
}

void setFillStatus(Terrain *terrain, int x, int y, FillStatus fillStatus) {
    Point *point = getPoint(terrain, x, y);
    point->fillStatus = fillStatus;
}

Point *getPoint(Terrain *terrain, int x, int y) {
    return terrain->points + (y * terrain->width + x);
}

//TODO Graphic functions. Don't belong to here
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
