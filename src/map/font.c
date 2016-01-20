#include "font.h"

Font *initFont(char *path) {
    TTF_Init();

    alloc(font, Font, 1);

    font->type = TTF_OpenFont(path, 16);

    if(font->type == NULL) {
        printf("Could not load the font\n");
        return NULL;
    }

    SDL_Color fgColor = {180, 180, 180};
    SDL_Color bgColor = {50, 50, 50};

    font->fgColor = fgColor;
    font->bgColor = bgColor;

    return font;
}

SDL_Texture *printString(Font *font, SDL_Renderer *renderer, char *string, int x, int y) {
    //trimLine(string);

    SDL_Texture *texture = getStringTexture(font->type, renderer, string, font->fgColor, font->bgColor);

    SDL_Rect textLocation;
    textLocation.x = x;
    textLocation.y = y;

    SDL_QueryTexture(texture, NULL, NULL, &textLocation.w, &textLocation.h);
    SDL_RenderCopy(renderer, texture, NULL, &textLocation);

    return texture;
}

SDL_Texture *getStringTexture(TTF_Font *font, SDL_Renderer *renderer, char *string, SDL_Color fgColor, SDL_Color bgColor) {
    SDL_Surface *textSurface = TTF_RenderText_Shaded(font, string, fgColor, bgColor);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    return texture;
}

void trimLine(char *line) {
    int linePos = strlen(line) - 1;

    if(*(line + linePos) == '\n') {
        *(line + linePos) = '\0';
    }
}
