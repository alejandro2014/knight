#include "hme_lowlevel.h"
#include "api.h"
#include "../global.h"

char *api_setHeight(Terrain **terrain, int x, int y, int height) {
    Point *point = getPoint(*terrain, x, y);
    //if(point->isHeightSetted) return;

    //countPoints++;
    point->z = height;
    //point->isHeightSetted = true;
    return NULL;
}

int getHeight(Terrain *terrain, int x, int y) {
    Point *point = getPoint(terrain, x, y);
    return point->z;
}

void incHeight(Terrain *terrain, int x, int y, int delta) {
    int newHeight = getHeight(terrain, x, y) + delta;
    api_setHeight(&terrain, x, y, (newHeight < MAX_HEIGHT ? newHeight : MAX_HEIGHT));
}

void decHeight(Terrain *terrain, int x, int y, int delta) {
    int newHeight = getHeight(terrain, x, y) - delta;
    api_setHeight(&terrain, x, y, (newHeight > MIN_HEIGHT ? newHeight : MIN_HEIGHT));
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
