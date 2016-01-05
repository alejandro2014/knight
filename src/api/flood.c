#include "flood.h"
#include "api.h"
#include "hme_lowlevel.h"

//TODO This algorithm needs to be changed for another that is able to fill non-convexe areas
/**
Floods an area of terrain. It fills with a flat surface the area to be flood, simulating the
effect of the water. It parts from a single point. From there it will flood the horizontal
lines at its left and right. For each point of these lines it will calculate the flood of
the vertical lines. The flood will stop when it finds a higher point. So basically, the way
to create a lake is to excavate the terrain first, and then to set the height of the water
*/
void api_floodArea(Terrain *terrain, int currentX, int currentY, int height) {
    int x = currentX;
    int y = currentY;
    bool pendingFound = true;

    setFillStatusTerrain(terrain, NOT_FILLED);

    floodLineHor(terrain, x, y, height, LEFT);
    floodLineHor(terrain, x, y, height, RIGHT);

    setFillStatusTerrain(terrain, NOT_FILLED);
}

void floodLineHor(Terrain *terrain, int x, int y, int height, Direction direction) {
    int delta = (direction == LEFT) ? STEP_LEFT: STEP_RIGHT;

    floodLineVer(terrain, x, y, height, UP);
    floodLineVer(terrain, x, y, height, DOWN);
    x += delta;

    while(getHeight(terrain, x, y) <= height) {
        api_setHeight(terrain, x, y, height);
        setFillStatus(terrain, x, y, FILLED);
        floodLineVer(terrain, x, y, height, UP);
        floodLineVer(terrain, x, y, height, DOWN);
        x += delta;
	}
}

void floodLineVer(Terrain *terrain, int x, int y, int height, Direction direction) {
    int delta = (direction == UP) ? STEP_UP: STEP_DOWN;
    y += delta;

    while(getHeight(terrain, x, y) <= height) {
        api_setHeight(terrain, x, y, height);
        setFillStatus(terrain, x, y, FILLED);
        y += delta;
	}
}

void setFillStatusTerrain(Terrain *terrain, FillStatus fillStatus) {
    int x, y;

    for(x = 0; x < terrain->width; x++) {
        for(y = 0; y < terrain->height; y++) {
            setFillStatus(terrain, x, y, fillStatus);
        }
    }
}

/*
TODO To make this work we need:
- A way to create a terrain using a name, and address it later on
- A mixed parsing of parameters, string and integer
*/
void api_MergeTerrains(Terrain *srcTerrain, Terrain *destTerrain, int startX, int startY, Operation operation) {
    int xOffsetSrcTerrain = startX + srcTerrain->width;
    int yOffsetSrcTerrain = startY + srcTerrain->height;

    if(xOffsetSrcTerrain > srcTerrain->width || yOffsetSrcTerrain > srcTerrain->height) {
        printf("[ERROR] The source terrain doesn't fit the destination terrain\n");
        return;
    }

    int x, y;
    int height;

    for(x = startX; x < xOffsetSrcTerrain; x++) {
        for(y = startY; y < yOffsetSrcTerrain; y++) {
            height = getHeight(srcTerrain, x, y);
            replacePoint(destTerrain, x, y, height, operation);
        }
    }
}
