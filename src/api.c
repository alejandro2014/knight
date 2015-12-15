#include "api.h"
#include "terrain.h"
#include "hme_lowlevel.h"
#include "global.h"

void api_invertHeight(Terrain *terrain) {
    int x, y;
    int newHeight;

    for(x = 0; x < terrain->width; x++) {
        for(y = 0; y < terrain->height; y++) {
            newHeight = MAX_HEIGHT - getHeight(terrain, x, y);
            setHeight(terrain, x, y, newHeight);
        }
    }
}

void api_riseTerrain(Terrain *terrain, int delta) {
    api_riseSelection(terrain, 0, 0, terrain->width - 1, terrain->height - 1, delta);
}

void api_sinkTerrain(Terrain *terrain, int delta) {
    api_sinkSelection(terrain, 0, 0, terrain->width - 1, terrain->height - 1, delta);
}

void api_setHeightTerrain(Terrain *terrain, int height) {
    api_setHeightSelection(terrain, 0, 0, terrain->width - 1, terrain->height - 1, height);
}

//TODO Not tested
void api_smoothTerrain(Terrain *terrain) {
    api_smoothSelection(terrain, 0, 0, terrain->width - 1, terrain->height - 1);
}

void api_riseSelection(Terrain *terrain, int startX, int startY, int endX, int endY, int delta) {
    int x, y;

    for (y = startY; y <= endY; y++) {
        for (x = startX; x <= endX; x++) {
            incHeight(terrain, x, y, delta);
        }
    }
}

void api_sinkSelection(Terrain *terrain, int startX, int startY, int endX, int endY, int delta) {
    int x, y;

    for (y = startY; y <= endY; y++) {
        for (x = startX; x <= endX; x++) {
            decHeight(terrain, x, y, delta);
        }
    }
}

void api_setHeightSelection(Terrain *terrain, int startX, int startY, int endX, int endY, int height) {
    int x, y;

    for (y = startY; y <= endY; y++) {
        for (x = startX; x <= endX; x++) {
            setHeight(terrain, x, y, height);
        }
    }
}

//TODO Not tested
void api_smoothSelection(Terrain *terrain, int startX, int startY, int endX, int endY) {
    int x, y;
    int sum;

    for (y = startY; y <= endY; y++) {
        for (x = startX; x <= endX; x++) {
            sum += getHeight(terrain, x-1, y-1) + getHeight(terrain, x, y-1) + getHeight(terrain, x+1, y-1);
            sum += getHeight(terrain, x-1,   y) + getHeight(terrain, x,   y) + getHeight(terrain, x+1,   y);
            sum += getHeight(terrain, x-1, y+1) + getHeight(terrain, x, y+1) + getHeight(terrain, x+1, y+1);
            sum = (sum / 9) + (sum % 9 > 4 ? 1 : 0);

            setHeight(terrain, x, y, sum);
        }
    }
}

Terrain *api_rotate(Operation operation, Terrain *oldTerrain) {
    int x, y;
    int width, height;
    int newHeight;

    setDimensionsForOperation(operation, oldTerrain, &width, &height);
    Terrain *newTerrain = generateTerrain(width, height);

    for(x = 0; x < width; x++) {
        for(y = 0; y < height; y++) {
            newHeight = getHeightForOperation(operation, oldTerrain, x, y);
            setHeight(newTerrain, x, y, newHeight);
        }
    }

    freeTerrain(oldTerrain);
    oldTerrain = NULL;

    return newTerrain;
}

int getHeightForOperation(Operation operation, Terrain *terrain, int x, int y) {
    int width, height;
    int returned = 0;

    setDimensionsForOperation(operation, terrain, &width, &height);

    switch(operation) {
        case ROTATE_90: returned = getHeight(terrain, y, width - x - 1); break;
        case ROTATE_180: returned = getHeight(terrain, width - x - 1, height - y - 1); break;
        case ROTATE_270: returned = getHeight(terrain, height - y - 1, x); break;
        case FLIP_XAXIS: returned = getHeight(terrain, x, height - y - 1); break;
        case FLIP_YAXIS: returned = getHeight(terrain, width - x - 1, y); break;
    }

    return returned;
}

void setDimensionsForOperation(Operation operation, Terrain *terrain, int *width, int *height) {
    switch(operation) {
        case ROTATE_90:  *width = terrain->height; *height = terrain->width;  break;
        case ROTATE_180: *width = terrain->width;  *height = terrain->height; break;
        case ROTATE_270: *width = terrain->height; *height = terrain->width;  break;
        case FLIP_XAXIS: *width = terrain->width; *height = terrain->height; break;
        case FLIP_YAXIS: *width = terrain->width; *height = terrain->height; break;
    }
}
