#include "draw.h"

void setRect(SDL_Rect *rect, int x1, int y1, int x2, int y2) {
    rect->x = x1;
    rect->y = y1;
    rect->w = x2 - x1 + 1;
    rect->h = y2 - y1 + 1;
}

void drawBorder(SDL_Renderer *renderer, SDL_Rect *r, SDL_Color *color) {
    int x = r->x, y = r->y;
    int w = r->w-1, h = r->h-1;

    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);

    SDL_RenderDrawLine(renderer, x, y, x+w, y); //Top
    SDL_RenderDrawLine(renderer, x, y, x, y+h); //Left
    SDL_RenderDrawLine(renderer, x+w, y, x+w, y+h); //Right
    SDL_RenderDrawLine(renderer, x, y+h, x+w, y+h); //Bottom
}

void clearSubScreen(SDL_Renderer *renderer, SDL_Rect *coords, SDL_Color *color) {
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);
    SDL_RenderFillRect(renderer, coords);
}
