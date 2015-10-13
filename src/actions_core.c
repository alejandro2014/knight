#include "actions_core.h"

Terrain *terrain;

Terrain *generateTerrain(int width, int height) {
  Terrain *terrain = (Terrain *) malloc(sizeof(Terrain));
  int map_size = width * height;

  terrain->width = width;
  terrain->height = height;
  terrain->pointsNo = map_size;
  terrain->points = (Point *) malloc(map_size * sizeof(Point));

  return terrain;
}

void freeTerrain(Terrain *terrain) {
  if(terrain == NULL) return;

  free(terrain->points);
  free(terrain);
}

int getHeight(Point *point) {
    return point->z;
}

void setHeight(Point *point, int height) {
  point->z = height;
}
