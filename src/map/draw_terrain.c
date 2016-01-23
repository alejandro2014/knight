#include "draw_terrain.h"

Uint32 *pixels;
bool update = true;
int pitch;

void drawTerrain(SDL_Renderer *renderer, Terrain *terrain) {
    int i, j;

    /*for(i = 0; i < 200; i++) {
        for(j = 0; j < 100; j++) {
            SDL_RenderDrawPoint(renderer, i, j);
        }
    }*/

    //SDL_RenderPresent(renderer);

    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 800, 300);

    //if(update) {
        allocExist(pixels, Uint32, 800 * 300);
        update = false;
    //} else {
        memset(pixels, 100, 800 * 300 * sizeof(Uint32));

        SDL_LockTexture(texture, NULL, (void *)&pixels, &pitch);

        for(i = 0; i < 10; i++) {
            setPixel(i, i, 255);
        }

        SDL_UnlockTexture(texture);
    //}

    SDL_UpdateTexture(texture, NULL, pixels, 800 * sizeof(Uint32));

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
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
