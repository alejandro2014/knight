#include "draw_terrain.h"

Uint32 *pixels;
bool update = true;
int pitch;

void drawTerrain(SDL_Renderer *renderer, Terrain *terrain) {
    int x, y;
    int color;

    for(y = 0; y < 150; y++) {
        for(x = 0; x < 300; x++) {
            color = getHeight(terrain, x, y);
            SDL_SetRenderDrawColor(renderer, color, color, color, 255);
            SDL_RenderDrawPoint(renderer, x + 10, y + 10);
        }
    }
}

void setPixel(int x, int y, int intensity) {
    int intens;
    int color = 0;

    intens = intensity;
    color += intens << 24;

    intens = intensity;
    color += intens << 16;

    intens = intensity;
    color += intens << 8;

    Uint8 *pixel = (Uint8*)pixels + (y * pitch) + (x * sizeof(Uint32));
    *((Uint32*)pixel) = color;
}

int getPixel(int x, int y) {
    return 0;
}
