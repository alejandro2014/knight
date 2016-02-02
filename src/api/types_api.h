#ifndef TYPES_API_H
#define TYPES_API_H

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

#endif
