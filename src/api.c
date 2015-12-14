#include "api.h"
#include "terrain.h"
#include "hme_lowlevel.h"

Terrain *api_rotate(Terrain *oldTerrain, int angle) {
    Terrain *newTerrain = NULL;

    switch(angle) {
        case 90: newTerrain = rotate_90(oldTerrain); break;
        case 180: newTerrain = rotate_180(oldTerrain); break;
        case 270: newTerrain = rotate_270(oldTerrain); break;
    }

    return newTerrain;
}

Terrain *rotate_90(Terrain *oldTerrain) {
    int x, y;
    int width = oldTerrain->height;
    int height = oldTerrain->width;
    int newHeight;

    Terrain *newTerrain = generateTerrain(width, height);

    for(x = 0; x < width; x++) {
        for(y = 0; y < height; y++) {
            newHeight = getHeight(oldTerrain, y, width - x - 1);
            setHeight(newTerrain, x, y, newHeight);
        }
    }

    freeTerrain(oldTerrain);
    oldTerrain = NULL;

    return newTerrain;
}

Terrain *rotate_180(Terrain *oldTerrain) {
    int x, y;
    int height = oldTerrain->height;
    int width = oldTerrain->width;
    int newHeight;

    Terrain *newTerrain = generateTerrain(width, height);

    for(x = 0; x < width; x++) {
        for(y = 0; y < height; y++) {
            newHeight = getHeight(oldTerrain, width - x - 1, height - y - 1);
            setHeight(newTerrain, x, y, newHeight);
        }
    }

    freeTerrain(oldTerrain);
    oldTerrain = NULL;

    return newTerrain;
}

Terrain *rotate_270(Terrain *oldTerrain) {
    int x, y;
    int width = oldTerrain->height;
    int height = oldTerrain->width;
    int newHeight;

    Terrain *newTerrain = generateTerrain(width, height);

    for(x = 0; x < width; x++) {
        for(y = 0; y < height; y++) {
            printf("b[%d, %d] = a [%d, %d]\n", x, y, y, x);
            newHeight = getHeight(oldTerrain, height - y - 1, x);
            setHeight(newTerrain, x, y, newHeight);
        }
    }

    freeTerrain(oldTerrain);
    oldTerrain = NULL;

    return newTerrain;
}
