#ifndef GLOBAL_MAP_H
#define GLOBAL_MAP_H

#include <SDL2/SDL.h>

#include "../global.h"

void setRect(SDL_Rect *rect, int x, int y, int w, int h);
void drawBorder(SDL_Renderer *renderer, SDL_Rect *r, SDL_Color *color);

#endif
