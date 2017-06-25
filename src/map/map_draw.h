#ifndef MAP_DRAW_H
#define MAP_DRAW_H

#include <SDL2/SDL.h>

#include "../draw.h"

#include "../api/api.h"
#include "../api/hme_lowlevel.h"

#include "global_map.h"

void drawTerrain(Screen *screen, Terrain *terrain, TerrainVisualParams *params);
void calculateOffset(Terrain *terrain, int *xOffset, int *yOffset, TerrainVisualParams *terrainParams);

void drawRuler(SDL_Renderer *renderer, int widthFactor, int offset);
void drawBarcodeLine(SDL_Renderer *renderer, int x);
void drawBarcodeDigit(SDL_Renderer *renderer, char digit, int offset, int widthFactor);

void drawGuard(SDL_Renderer *renderer, int offset, int widthFactor, int numberOfBars);

char getBarcodeDigitLeftSide(char number, int isOdd);
char getBarcodeDigitRightSide(char number);
int getParity(char ctrlDigit, int position);

#endif
