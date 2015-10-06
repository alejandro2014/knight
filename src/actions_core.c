#include "actions_core.h"

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
  free(terrain->points);
  free(terrain);
}
