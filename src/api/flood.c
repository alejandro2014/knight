#include "flood.h"
#include "api.h"
#include "hme_lowlevel.h"

/*
5 5 5 5 5    5 5 5 5 5    5 5 5 5 5
5 3 3 3 5    5 3 3 3 5    5 4 4 4 5
5 3 1 3 5 -> 5 3 4 3 5 -> 5 4 4 4 5
5 3 3 3 5    5 3 3 3 5    5 4 4 4 5
5 5 5 5 5    5 5 5 5 5    5 5 5 5 5
*/

/**
Floods an area of terrain. It fills with a flat surface the area to be flood, simulating the
effect of the water. It parts from a single point. From there it will flood the horizontal
lines at its left and right. For each point of these lines it will calculate the flood of
the vertical lines. The flood will stop when it finds a higher point. So basically, the way
to create a lake is to excavate the terrain first, and then to set the height of the water
*/
void api_floodArea(Terrain *terrain, int currentX, int currentY) {
    int x, y;
    bool pendingFound = true;
    int height = getHeight(terrain, currentX, currentY);

    setFillStatusTerrain(terrain, NOT_FILLED);
    flood_line(terrain, currentX, currentY, height);

    /*while(1) {
        pendingFound = true;

        for(x = 0; x < terrain->width; x++) {
            for(y = 0; y < terrain->height; y++) {
                if(!isFilled(terrain, x, y)) {
                    pendingFound = false;
                    flood_line(terrain, x, y, height);
                }
            }
        }

        if(pendingFound) break;
    }*/

    setFillStatusTerrain(terrain, NOT_FILLED);
}

//Scans left an right
void flood_line(Terrain *terrain, int x, int y, int height) {
    floodLineHor(terrain, x, y, height, LEFT);
    floodLineHor(terrain, x, terrain->width, y, height);
}

void floodLineHor(Terrain *terrain, int x, int y, int height, Direction direction) {
    int delta = (direction == LEFT) ? STEP_LEFT: STEP_RIGHT;
    x += delta;

    while(getHeight(terrain, x, y) <= height) {
        api_setHeight(terrain, x, y, height);
        setFillStatus(terrain, x, y, FILLED);

		//now, scan for the up and down neighbours
		/*if(y > 0 && getHeight(terrain, x - terrain->width, y) < height)
            flood_ver_line(terrain, x, y-1, height);

		if(y < terrain->height - 1 && getHeight(terrain, x + terrain->width, y) != height)
            flood_ver_line(terrain, x, y+1, height);*/
        x += delta;
	}
}

//Fills upwards and downwards
void flood_ver_line(Terrain *terrain, int x, int y, int height) {
    floodLineVer(terrain, x, 0, y, height);
    floodLineVer(terrain, x, y + 1, terrain->height - 1, height);
}

void floodLineVer(Terrain *terrain, int x, int yIni, int yFin, int height) {
    int y;

    for (y = yIni; y <= yFin; y++) {
		if(getHeight(terrain, x, y) != height) {
			api_setHeight(terrain, x, y, height);
            setFillStatus(terrain, x, y, FILLED);

            //now, scan for the up and down neighbours
			if(x > 0 && getHeight(terrain, x-1, y) < height)
                setFillStatus(terrain, x-1, y, NOT_FILLED);

			if(x < terrain->width - 1 && getHeight(terrain, x+1, y) < height)
                setFillStatus(terrain, x+1, y, NOT_FILLED);
		}
		else break;
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
