#include "map_draw.h"

void drawTerrain(Screen *screen, Terrain *terrain, TerrainVisualParams *params) {
    SDL_Renderer *renderer = screen->renderer;
    int x, y;
    int color;
    int xOffset, yOffset;

    clearSubScreen(renderer, &(screen->terrainCoords), &(screen->bgColorTerrain));

    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);

    int width = 600;
    int height = 300;

    SDL_RenderDrawLine(renderer, 10, 40, 10, height);
    SDL_RenderDrawLine(renderer, 20, 40, 20, height);
    SDL_RenderDrawLine(renderer, 30, 40, 30, height);
    SDL_RenderDrawLine(renderer, 40, 40, 40, height);

    SDL_RenderDrawLine(renderer, 10, 40, width, 40);
    SDL_RenderDrawLine(renderer, 10, 50, width, 50);
    SDL_RenderDrawLine(renderer, 10, 60, width, 60);
    SDL_RenderDrawLine(renderer, 10, 70, width, 70);
    /*if(!terrain) return;

    calculateOffset(terrain, &xOffset, &yOffset, params);

    for(y = 0; y < terrain->height; y++) {
        for(x = 0; x < terrain->width; x++) {
            color = getHeight(terrain, x, y);
            SDL_SetRenderDrawColor(renderer, color, color, color, 255);
            SDL_RenderDrawPoint(renderer, x + xOffset, y + yOffset);
        }
    }

    SDL_Color c = {160, 80, 80};
    drawBorder(renderer, &(screen->terrainCoords), &c);*/
}

void calculateOffset(Terrain *terrain, int *xOffset, int *yOffset, TerrainVisualParams *terrainWindow) {
    *xOffset = ((terrainWindow->width - terrain->width) / 2) + terrainWindow->x;
    *yOffset = ((terrainWindow->height - terrain->height) / 2) + terrainWindow->y;
}
