#ifndef __DISPLAY_TERRAIN_H__
#define __DISPLAY_TERRAIN_H__

#include "global.h"
#include "font.h"

void terrain_on_screen (SDL_Surface * this_screen);
//void cls(SDL_Surface * this_screen);
void cls();

void draw_grid(SDL_Surface * this_screen);
void draw_selection(SDL_Surface * this_screen);
void drawScreen();

void debug_info ();
#endif
