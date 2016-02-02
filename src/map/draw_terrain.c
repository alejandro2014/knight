#include "draw_terrain.h"

void drawTerrain(SDL_Renderer *renderer, Terrain *terrain, TerrainVisualParams *terrainParams) {
    int x, y;
    int color;
    int xOffset, yOffset;

    calculateOffset(terrain, &xOffset, &yOffset, terrainParams);

    for(y = 0; y < terrain->height; y++) {
        for(x = 0; x < terrain->width; x++) {
            color = getHeight(terrain, x, y);
            SDL_SetRenderDrawColor(renderer, color, color, color, 255);
            SDL_RenderDrawPoint(renderer, x + xOffset, y + yOffset);
        }
    }
}

void calculateOffset(Terrain *terrain, int *xOffset, int *yOffset, TerrainVisualParams *terrainWindow) {
    *xOffset = ((terrainWindow->width - terrain->width) / 2) + terrainWindow->x;
    *yOffset = ((terrainWindow->height - terrain->height) / 2) + terrainWindow->y;
}
