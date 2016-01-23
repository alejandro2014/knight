#include "draw_terrain.h"

bool update = true;

void drawTerrain(SDL_Renderer *renderer, Terrain *terrain) {
    int x, y;
    int color;
    int xOffset;
    int yOffset;

    calculateOffset(terrain, &xOffset, &yOffset);

    for(y = 0; y < terrain->height; y++) {
        for(x = 0; x < terrain->width; x++) {
            color = getHeight(terrain, x, y);
            SDL_SetRenderDrawColor(renderer, color, color, color, 255);
            SDL_RenderDrawPoint(renderer, x + xOffset, y + yOffset);
        }
    }
}

void calculateOffset(Terrain *terrain, int *xOffset, int *yOffset) {
    int widthScreen = 800;
    int heightScreen = 300;

    *xOffset = (widthScreen - terrain->width) / 2;
    *yOffset = (heightScreen - terrain->height) / 2;
}
