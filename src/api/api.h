#ifndef API_H
#define API_H

#include <stdio.h>
#include <stdlib.h>

#include "../global.h"

typedef int Operation;
#define ROTATE_90 0
#define ROTATE_180 1
#define ROTATE_270 2
#define FLIP_XAXIS 3
#define FLIP_YAXIS 4
#define REPLACE_HEIGHT 5
#define ADD_HEIGHT 6
#define SUBS_HEIGHT 7

typedef int FillStatus;
#define NOT_FILLED 0
#define FILLED 1
#define PENDING_FILL 2

typedef struct {
  int x;
  int y;
  int z;
  bool isHeightSetted;
  FillStatus fillStatus;
} Point;

typedef struct {
  int width;
  int height;
  int pointsNo;
  Point *points;
  int seedRandom;
} Terrain;

Terrain *api_generateTerrain(int width, int height, char *infoMessage);
void api_freeTerrain(Terrain *terrain);

void api_riseTerrain(Terrain *terrain, int delta);
void api_sinkTerrain(Terrain *terrain, int delta);
void api_setHeightTerrain(Terrain *terrain, int height);
char *api_smoothTerrain(Terrain **terrain);

void api_riseSelection(Terrain *terrain, int startX, int startY, int endX, int endY, int delta);
void api_sinkSelection(Terrain *terrain, int startX, int startY, int endX, int endY, int delta);
void api_setHeightSelection(Terrain *terrain, int x1, int y1, int x2, int y2, int height);
char *api_smoothSelection(Terrain **terrain, int startX, int startY, int endX, int endY);

Terrain *api_rotate(Terrain *oldTerrain, Operation operation, char *infoMessage);
void api_invertHeight(Terrain *terrain);

int getHeightForOperation(Operation operation, Terrain *terrain, int x, int y);
void setDimensionsForOperation(Operation operation, Terrain *terrain, int *width, int *height);

void replacePoint(Terrain *terrain, int x, int y, int delta, int mode);

#endif
