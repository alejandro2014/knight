#ifndef API_H
#define API_H

#include "terrain.h"

Terrain *api_rotate(Terrain *oldTerrain, int angle);
Terrain *rotate_90(Terrain *oldTerrain);
Terrain *rotate_180(Terrain *oldTerrain);
Terrain *rotate_270(Terrain *oldTerrain);

#endif
