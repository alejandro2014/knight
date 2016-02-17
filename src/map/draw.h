#ifndef DRAW_H
#define DRAW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../global.h"

#include "../api/api.h"

#include "../console/console_lang.h"
#include "../console/console_print.h"
#include "../console/console_draw.h"

#include "font.h"
#include "global_map.h"
#include "draw_terrain.h"

#include "../widgets/menu_bar.h"

void drawScreen(Screen *screen, Console *console, TerrainVisualParams *terrainParams, Widget_MenuBar *menuBar);
void drawBorder(SDL_Renderer *renderer, SDL_Rect *r, SDL_Color *color);
void clearSubScreen(SDL_Renderer *renderer, SDL_Rect *coords, SDL_Color *color);
/*void draw_frame (SDL_Surface * this_screen, int xmenu, int ymenu, int xlen, int ylen);
void draw_down_button (SDL_Surface * this_screen, int xmenu, int ymenu, int xlen, int ylen);
void draw_up_button (SDL_Surface * this_screen, int xmenu, int ymenu, int xlen, int ylen);
void draw_empty_menu (SDL_Surface * this_screen, char color, int xmenu, int ymenu, int xlen, int ylen);

void draw_status_bar ();

void draw_tool_tip();*/

#endif
