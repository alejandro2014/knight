#ifndef FONT_H
#define FONT_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../global.h"

typedef struct {
    SDL_Color fgColor;
    SDL_Color bgColor;
    TTF_Font *font;
} Font;

SDL_Texture *printString(TTF_Font *font, SDL_Renderer *renderer, char *string, int x, int y);
SDL_Texture *getStringTexture(TTF_Font *font, SDL_Renderer *renderer, char *string, SDL_Color fgColor, SDL_Color bgColor);

//void draw_char (SDL_Surface * this_screen, Uint8 my_char, char font_color, char background_color, int char_xscreen, int char_yscreen);
//void print_string(char *str, char char_color, char background_color, int char_xscreen, int char_yscreen);

#endif
