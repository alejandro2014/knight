#ifndef API_H
#define API_H

#include <stdio.h>
#include <stdlib.h>

#include "../global.h"

#define MAX_HEIGHT 255

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

char *api_generateTerrain(Terrain **terrain, int width, int height);
void api_freeTerrain(Terrain *terrain);

char *api_riseTerrain(Terrain **terrain, int delta);
char *api_sinkTerrain(Terrain **terrain, int delta);
char *api_setHeightTerrain(Terrain **terrain, int height);
char *api_smoothTerrain(Terrain **terrain);

char *api_riseSelection(Terrain **terrain, int startX, int startY, int endX, int endY, int delta);
char *api_sinkSelection(Terrain **terrain, int startX, int startY, int endX, int endY, int delta);
char *api_setHeightSelection(Terrain **terrain, int startX, int startY, int endX, int endY, int height);
char *api_smoothSelection(Terrain **terrain, int startX, int startY, int endX, int endY);

char *api_rotate(Terrain **terrain, Operation operation);
char *api_invertHeight(Terrain **terrain);

int getHeightForOperation(Operation operation, Terrain *terrain, int x, int y);
void setDimensionsForOperation(Operation operation, Terrain *terrain, int *width, int *height);

void replacePoint(Terrain *terrain, int x, int y, int delta, int mode);

#endif
