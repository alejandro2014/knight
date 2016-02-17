#ifndef DRAW_H
#define DRAW_H

#include <SDL2/SDL.h>

void setRect(SDL_Rect *rect, int x1, int y1, int x2, int y2);
void drawBorder(SDL_Renderer *renderer, SDL_Rect *r, SDL_Color *color);
void clearSubScreen(SDL_Renderer *renderer, SDL_Rect *coords, SDL_Color *color);

#endif
