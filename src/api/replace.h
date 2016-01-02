#ifndef REPLACE_H
#define REPLACE_H

#include "replace.h"
#include "api.h"

#define GREATER_OR_LEASER 0
#define GREATER 1
#define LEASER 2

void pre_change_area();

void setPendingFillIfNeeded(Terrain *terrain, int x, int y, int tolerance, int deltaMax);
void replaceLineVer(Terrain *terrain, int x, int yIni, int yFin, int toleranceMode, int height);
void replaceVerticalLineIfNeeded(Terrain *terrain, int x, int y, int mode, int height);
void replaceLineHor(Terrain *terrain, int xIni, int xFin, int y, int height, int mode);

void replace_ver_line(Terrain *terrain, int x, int y, int toleranceMode, int height);
void replace_line(Terrain *terrain, int x, int y, int height, int mode);
bool isHeightInsideLimits(int mode, int height, int deltaMax);

#endif
