#include "api.h"
#include "terrain.h"
#include "hme_lowlevel.h"
#include "global.h"

Terrain *api_flipZ(Terrain *oldTerrain) {
    /*int i;
    int map_size=WIDTH*HEIGHT;

    for(x = 0; x < WIDTH; x++) {
        for(y = 0; y < HEIGHT; y++) {
            currentHeight = getHeight(x, y);
            setHeight(x, y, -currentHeight);
        }
    }*/
    return NULL;
}

//--------------------------------------------------------
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
