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
        case 90: newTerrain = rotate90(oldTerrain); break;
        case 180: newTerrain = rotate180(oldTerrain); break;
        case 270: newTerrain = rotate270(oldTerrain); break;
    }

    return newTerrain;
}

//--------------------------------------------------------
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
    int terrainWidth;// = terrain->height;
    int terrainHeight;// = terrain->width;
    int height = 0;

    switch(operation) {
        case ROTATE_90:
            terrainWidth = terrain->height;
            terrainHeight = terrain->width;
            height = getHeight(terrain, y, terrainWidth - x - 1);
            break;
        case ROTATE_180:
            terrainWidth = terrain->width;
            terrainHeight = terrain->height;
            height = getHeight(terrain, terrainWidth - x - 1, terrainHeight - y - 1);
            break;
        case ROTATE_270:
            terrainWidth = terrain->height;
            terrainHeight = terrain->width;
            height = getHeight(terrain, terrainHeight - y - 1, x);
            break;
    }

    return height;
}
