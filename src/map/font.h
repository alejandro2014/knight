#ifndef __FONT_H__
#define __FONT_H__

#include "global.h"
#include <SDL2/SDL.h>
#include <SDL_ttf.h>

typedef struct {
    SDL_Color fgColor;
    SDL_Color bgColor;
    TTF_Font *font;
} Font;

extern TTF_Font *font;

void load_font ();
void draw_char (SDL_Surface * this_screen, Uint8 my_char, char font_color, char background_color, int char_xscreen, int char_yscreen);
void print_string(char *str, char char_color, char background_color, int char_xscreen, int char_yscreen);
SDL_Texture *printString(char *string, Uint32 x, Uint32 y);
SDL_Texture *getStringTexture(TTF_Font *font, char *string, SDL_Color fgColor, SDL_Color bgColor);

#endif
