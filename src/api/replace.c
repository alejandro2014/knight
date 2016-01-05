#include "replace.h"
#include "api.h"
#include "hme_lowlevel.h"

//the fill tool
void api_replace(Terrain *terrain, int currentX, int currentY, int mode) {
    int x,y;
    char *temp_buffer, *some_temp_buffer;
    bool no_pending_found=0;
    int height = getHeight(terrain, currentX, currentY); //TODO What for?
    int pending_fill = 0; //TODO Fake variable

    some_temp_buffer = temp_buffer;
    //TODO api_setHeightTerrain(some_temp_buffer, not_filled); //clear the temp buffer

    replace_line(terrain, currentX, currentY, height, mode);
	while(1) {
		no_pending_found=0;
		some_temp_buffer=temp_buffer;

        for(x = 0; x < terrain->width; x++) {
            for(y = 0; y < terrain->height; y++) {
                if(*(some_temp_buffer++) == pending_fill) {
    				no_pending_found=1;
    				replace_line(terrain, x, y, height, mode); //TODO height is possibly wrong
    			}
            }
        }

		if(!no_pending_found) break;
	}

	some_temp_buffer = temp_buffer;
    //TODO api_setHeightTerrain(some_temp_buffer, not_filled); //clear the temp buffer
}

//Scans left and right
void replace_line(Terrain *terrain, int x, int y, int height, int mode) {
    replaceLineHor(terrain, 0, x, y, height, mode);
    replaceLineHor(terrain, x+1, terrain->width - 1, y, height, mode);
}

void replaceLineHor(Terrain *terrain, int xIni, int xFin, int y, int height, int mode) {
    int currentHeight;
    int x;

    for(x = xIni; x < xFin; x++) {
        currentHeight = getHeight(terrain, x, y);

        if(!isHeightInsideLimits(mode, currentHeight, height) || !isFilled(terrain, x, y)) break;

        replacePoint(terrain, x, y, height, mode);
        setFilled(terrain, x, y);

        //now, scan for the up and down neighbours
        if(y>0) replaceVerticalLineIfNeeded(terrain, x - terrain->width, y, mode, height);
        if(y < terrain->height - 1) replaceVerticalLineIfNeeded(terrain, x + terrain->width, y, mode, height);
    }
}

void replaceVerticalLineIfNeeded(Terrain *terrain, int x, int y, int mode, int height) {
    int currentHeight = getHeight(terrain, x - terrain->width, y);

    if(isHeightInsideLimits(mode, currentHeight, height) && !isFilled(terrain, x - terrain->width, y)) {
        replace_ver_line(terrain, x, y, mode, height);
    }
}

//Replaces two lines, upwards and downwards
void replace_ver_line(Terrain *terrain, int x, int y, int mode, int height) {
    replaceLineVer(terrain, x, 0, y, mode, height);
    replaceLineVer(terrain, x, y + 1, terrain->height - 1, mode, height);
}

void replaceLineVer(Terrain *terrain, int x, int yIni, int yFin, int mode, int height) {
    int currentHeight;
    int y;

    for(y = yIni; y <= yFin; y++) {
		currentHeight = getHeight(terrain, x, y);

		if(!isHeightInsideLimits(mode, currentHeight, height) || isFilled(terrain, x, y)) break;

        replacePoint(terrain, x, y, height, mode);
        setFilled(terrain, x, y);

		//now, scan for the up and down neighbours
		if(x > 0) setPendingFillIfNeeded(terrain, x-1, y, mode, height);
        if(x < terrain->width - 1) setPendingFillIfNeeded(terrain, x+1, y, mode, height);
	}
}

void setPendingFillIfNeeded(Terrain *terrain, int x, int y, int tolerance, int deltaMax) {
    int currentHeight = getHeight(terrain, x, y);

    if(isHeightInsideLimits(tolerance, currentHeight, deltaMax) && !isFilled(terrain, x, y)) {
        setPendingFill(terrain, x, y);
    }
}

bool isHeightInsideLimits(int mode, int height, int deltaMax) {
    int maximum = height;
    int minimum = height;

    switch(mode) {
        case GREATER_OR_LEASER:
            maximum += deltaMax;
            minimum -= deltaMax;
            break;
        case GREATER: maximum += deltaMax; break;
        case LEASER: minimum -= deltaMax; break;
    }

    return (height >= minimum && height <= maximum) ? true : false;
}
