#ifndef REPLACE_H
#define REPLACE_H

#include "replace.h"
#include "api.h"

#define GREATER_OR_LEASER 0
#define GREATER 1
#define LEASER 2

#define EQUAL 0
#define PLUS 1
#define MINUS 2
#define PATTERN 3

char *api_replace(Terrain **terrain, int mode, int currentX, int currentY, int delta);

void setPendingFillIfNeeded(Terrain *terrain, int x, int y, int tolerance, int deltaMax);
void replaceLineVer(Terrain *terrain, int x, int yIni, int yFin, int toleranceMode, int height);
void replaceVerticalLineIfNeeded(Terrain *terrain, int x, int y, int mode, int height);
void replaceLineHor(Terrain *terrain, int xIni, int xFin, int y, int height, int mode);

void replace_ver_line(Terrain *terrain, int x, int y, int toleranceMode, int height);
void replace_line(Terrain *terrain, int x, int y, int height, int mode);
bool isHeightInsideLimits(int mode, int height, int deltaMax);

void put_pattern(Terrain * terrain, Terrain *pattern, int x, int y, int mode);
void modifyHeight(Terrain *terrain, int x, int y, int delta, int mode);

#endif
