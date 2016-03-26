#ifndef FONT_H
#define FONT_H

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../global.h"

#define FONT_PATH_MAC "/Library/Fonts/Courier New.ttf"
#define FONT_PATH_LINUX "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf"

typedef struct {
    TTF_Font *type;
    SDL_Color fgColor;
    SDL_Color bgColor;
} Font;

Font *loadFont(char *path, int size, SDL_Color *fg, SDL_Color *bg);
void freeFont(Font *font);

SDL_Texture *printString(Font *font, SDL_Renderer *renderer, char *string, int x, int y);
SDL_Texture *getStringTexture(TTF_Font *font, SDL_Renderer *renderer, char *string, SDL_Color fgColor, SDL_Color bgColor);

void trimLine(char *line);

#endif
