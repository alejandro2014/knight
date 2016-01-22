#include "draw_terrain.h"

Uint32 *pixels;
bool update = true;

void drawTerrain(SDL_Renderer *renderer, Terrain *terrain) {
    /*int i, j;

    for(i = 0; i < 200; i++) {
        for(j = 0; j < 100; j++) {
            SDL_RenderDrawPoint(renderer, i, j);
        }
    }*/

    //SDL_RenderPresent(renderer);

    /*if(update) {
        allocExist(pixels, Uint32, 800 * 300);
        update = false;
    }*/

    //SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 800, 300);

    //SDL_UpdateTexture(texture, NULL, pixels, 800 * sizeof(Uint32));

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect r;
    r.w = 800;
    r.h = 300;
    r.x = 0;
    r.y = 0;

    SDL_RenderFillRect(renderer, &r);

    //SDL_RenderCopy(renderer, texture, NULL, NULL);
    //SDL_RenderPresent(renderer);
}
