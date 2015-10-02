#include "actions_core.h"

typedef struct {
  float x;
  float y;
  float z;
} Point;

typedef struct {
  int width;
  int height;
  Point **points;
} Terrain;

int hme_generate_terrain(int width, int height) {
  int map_size = width * height;

  return 0;
}
