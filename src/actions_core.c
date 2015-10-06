#include "actions_core.h"

Terrain *hme_generate_terrain(int width, int height) {
  Terrain *terrain = (Terrain *) malloc(sizeof(Terrain));
  terrain->width = width;
  terrain->height = height;
  terrain->pointsNo = width * height;
  terrain->points = hmeAllocatePoints(width, height);

  return terrain;
}

Point **hmeAllocatePoints(int width, int height) {
  int map_size = width * height;
  Point **points = (Point **) calloc(map_size, sizeof(Point *));
  Point *currentPoint = NULL;
  int i;

  if(points == NULL) {
    sprintf(error_msg_1,"Not enough memory for the height map!");
    sprintf(error_msg_2,"Please use a smaller map size!");
    return NULL;
  }

  for(i = 0; i < map_size; i++) {
    currentPoint = (Point *) calloc(1, sizeof(Point));
    *(points + i) = currentPoint;
  }

  return points;
}

int hmeAllocateMem(Uint8 **buffer, int size) {
  *buffer = calloc ( size, sizeof(Uint8));

  if(*buffer) {
    memset(*buffer, 0, size);
    return 0;
  }

  return -1;
}

void hmeFreeTerrain(Terrain *terrain) {
  int i;

  for(i = 0; i < terrain->pointsNo; i++) {
    free(terrain->points[i]);
  }

  free(terrain->points);

  free(terrain);
}
