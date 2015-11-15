#ifndef __DISPLAY_TERRAIN_H__
#define __DISPLAY_TERRAIN_H__

#include "global.h"
#include "font.h"
#include "actions_core.h"

void terrain_on_screen (SDL_Surface * this_screen);
void cls(SDL_Surface * this_screen);

void draw_grid(SDL_Surface * this_screen);
void draw_selection(SDL_Surface * this_screen);
Uint32 on_screen (Uint32 interval, void *params);

void debug_info ();
#endif
