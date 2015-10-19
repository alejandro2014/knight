#ifndef __FONT_H__
#define __FONT_H__

#include "global.h"
#include <SDL_ttf.h>

extern TTF_Font *font;

void load_font ();
void draw_char (SDL_Surface * this_screen, Uint8 my_char, char font_color, char background_color, int char_xscreen, int char_yscreen);
void print_string (char *str, char char_color, char background_color, int char_xscreen, int char_yscreen);

#endif
