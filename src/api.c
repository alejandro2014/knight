#include "api.h"
#include "terrain.h"
#include "hme_lowlevel.h"
#include "global.h"

Terrain *api_flip(Terrain *terrain, Axis axis) {
    switch(axis) {
        case XAXIS: terrain = api_flipX(terrain); break;
        case YAXIS: terrain = api_flipY(terrain); break;
    }

    return terrain;
}

Terrain *api_flipX(Terrain *oldTerrain) {
    int x, y;
    int width = oldTerrain->width;
    int height = oldTerrain->height;
    int newHeight;

    Terrain *newTerrain = generateTerrain(width, height);

    for(x = 0; x < width; x++) {
        for(y = 0; y < height; y++) {
            newHeight = getHeight(oldTerrain, x, height - y - 1);
            setHeight(newTerrain, x, y, newHeight);
        }
    }

    freeTerrain(oldTerrain);
    oldTerrain = NULL;

    return newTerrain;
}

Terrain *api_flipY(Terrain *oldTerrain) {
    int x, y;
    int width = oldTerrain->width;
    int height = oldTerrain->height;
    int newHeight;

    Terrain *newTerrain = generateTerrain(width, height);

    for(x = 0; x < width; x++) {
        for(y = 0; y < height; y++) {
            newHeight = getHeight(oldTerrain, width - x - 1, y);
            setHeight(newTerrain, x, y, newHeight);
        }
    }

    freeTerrain(oldTerrain);
    oldTerrain = NULL;

    return newTerrain;
}

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

Terrain *api_rotate(Terrain *oldTerrain, int angle) {
    Terrain *newTerrain = NULL;

    switch(angle) {
        case 90: newTerrain = rotatex(ROTATE_90, oldTerrain); break;
        case 180: newTerrain = rotatex(ROTATE_180, oldTerrain); break;
        case 270: newTerrain = rotatex(ROTATE_270, oldTerrain); break;
    }

    return newTerrain;
}

//--------------------------------------------------------
Terrain *rotatex(Operation operation, Terrain *oldTerrain) {
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

Terrain *rotate90(Terrain *oldTerrain) {
    int x, y;
    int width = oldTerrain->height;
    int height = oldTerrain->width;
    int newHeight;

    Terrain *newTerrain = generateTerrain(width, height);

    for(x = 0; x < width; x++) {
        for(y = 0; y < height; y++) {
            newHeight = getHeightForOperation(ROTATE_90, oldTerrain, x, y);
            setHeight(newTerrain, x, y, newHeight);
        }
    }

    freeTerrain(oldTerrain);
    oldTerrain = NULL;

    return newTerrain;
}

Terrain *rotate180(Terrain *oldTerrain) {
    int x, y;
    int width = oldTerrain->width;
    int height = oldTerrain->height;
    int newHeight;

    Terrain *newTerrain = generateTerrain(width, height);

    for(x = 0; x < width; x++) {
        for(y = 0; y < height; y++) {
            newHeight = getHeightForOperation(ROTATE_180, oldTerrain, x, y);
            setHeight(newTerrain, x, y, newHeight);
        }
    }

    freeTerrain(oldTerrain);
    oldTerrain = NULL;

    return newTerrain;
}

Terrain *rotate270(Terrain *oldTerrain) {
    int x, y;
    int width = oldTerrain->height;
    int height = oldTerrain->width;
    int newHeight;

    Terrain *newTerrain = generateTerrain(width, height);

    for(x = 0; x < width; x++) {
        for(y = 0; y < height; y++) {
            newHeight = getHeightForOperation(ROTATE_270, oldTerrain, x, y);
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
    }

    return returned;
}

void setDimensionsForOperation(Operation operation, Terrain *terrain, int *width, int *height) {
    switch(operation) {
        case ROTATE_90:  *width = terrain->height; *height = terrain->width;  break;
        case ROTATE_180: *width = terrain->width;  *height = terrain->height; break;
        case ROTATE_270: *width = terrain->height; *height = terrain->width;  break;
    }
}
