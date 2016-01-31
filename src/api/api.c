#include <string.h>
#include <time.h>

#include "api.h"
#include "hme_lowlevel.h"
#include "../global.h"

Terrain *api_generateTerrain(int width, int height, char *infoMessage) {
    alloc(terrain, Terrain, 1);
    int map_size = width * height;

    terrain->width = width;
    terrain->height = height;
    terrain->pointsNo = map_size;
    terrain->seedRandom = time(NULL);

    allocExist(terrain->points, Point, map_size);

    sprintf(infoMessage, "[INFO] Created terrain (%d x %d) = %d", terrain->width, terrain->height, terrain->pointsNo);

    return terrain;
}

void api_freeTerrain(Terrain *terrain) {
  if(terrain == NULL) return;

  free(terrain->points);
  free(terrain);
}

char *api_invertHeight(Terrain **terrain) {
    /*int x, y;
    int newHeight;

    for(x = 0; x < (*terrain)->width; x++) {
        for(y = 0; y < (*terrain)->height; y++) {
            newHeight = MAX_HEIGHT - getHeight((*terrain), x, y);
            api_setHeight(terrain, x, y, newHeight);
        }
    }*/

    return NULL;
}

void api_riseTerrain(Terrain *terrain, int delta) {
    return api_riseSelection(terrain, 0, 0, terrain->width - 1, terrain->height - 1, delta);
}

void api_sinkTerrain(Terrain *terrain, int delta) {
    return api_sinkSelection(terrain, 0, 0, terrain->width - 1, terrain->height - 1, delta);
}

void api_setHeightTerrain(Terrain *terrain, int height) {
    return api_setHeightSelection(terrain, 0, 0, terrain->width - 1, terrain->height - 1, height);
}

//TODO Not tested
char *api_smoothTerrain(Terrain **terrain) {
    return api_smoothSelection(terrain, 0, 0, (*terrain)->width - 1, (*terrain)->height - 1);
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

void api_setHeightSelection(Terrain *terrain, int x1, int y1, int x2, int y2, int height) {
    int x, y;

    printf("sethsel (x1:%d y1:%d x2:%d y2:%d height:%d)\n", x1, y1, x2, y2, height);
    for (y = y1; y <= y2; y++) {
        for (x = x1; x <= x2; x++) {
            api_setHeight(terrain, x, y, height);
        }
    }
}

//TODO Not tested
char *api_smoothSelection(Terrain **terrain, int startX, int startY, int endX, int endY) {
    /*int x, y;
    int sum;

    for (y = startY; y <= endY; y++) {
        for (x = startX; x <= endX; x++) {
            sum += getHeight(*terrain, x-1, y-1) + getHeight(*terrain, x, y-1) + getHeight(*terrain, x+1, y-1);
            sum += getHeight(*terrain, x-1,   y) + getHeight(*terrain, x,   y) + getHeight(*terrain, x+1,   y);
            sum += getHeight(*terrain, x-1, y+1) + getHeight(*terrain, x, y+1) + getHeight(*terrain, x+1, y+1);
            sum = (sum / 9) + (sum % 9 > 4 ? 1 : 0);

            api_setHeight(terrain, x, y, sum);
        }
    }*/

    return NULL;
}

Terrain *api_rotate(Terrain *oldTerrain, Operation operation, char *infoMessage) {
    Terrain *newTerrain = NULL;
    int x, y;
    int width, height;
    int newHeight;

    setDimensionsForOperation(operation, oldTerrain, &width, &height);
    newTerrain = api_generateTerrain(width, height, infoMessage);

    for(x = 0; x < width; x++) {
        for(y = 0; y < height; y++) {
            newHeight = getHeightForOperation(operation, oldTerrain, x, y);
            api_setHeight(newTerrain, x, y, newHeight);
        }
    }

    api_freeTerrain(oldTerrain);

    switch(operation) {
        case ROTATE_90: sprintf(infoMessage, "[INFO] Rotated 90 degrees (new width = %d, new height: %d)", width, height); break;
        case ROTATE_180: sprintf(infoMessage, "[INFO] Rotated 180 degrees"); break;
        case ROTATE_270: sprintf(infoMessage, "[INFO] Rotated 270 degrees (new width = %d, new height: %d)", width, height); break;
        case FLIP_XAXIS: sprintf(infoMessage, "[INFO] Flip x axis"); break;
        case FLIP_YAXIS: sprintf(infoMessage, "[INFO] Flip y axis"); break;
    }

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

void replacePoint(Terrain *terrain, int x, int y, int delta, int mode) {
    switch(mode) {
        case REPLACE_HEIGHT: api_setHeight(terrain, x, y, delta); break;
        case ADD_HEIGHT:  incHeight(terrain, x, y, delta); break;
        case SUBS_HEIGHT: decHeight(terrain, x, y, delta); break;
    }
}
