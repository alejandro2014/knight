#include "map_draw.h"

void drawTerrain(Screen *screen, Terrain *terrain, TerrainVisualParams *params) {
    SDL_Renderer *renderer = screen->renderer;
    int x, y;
    int color;

    clearSubScreen(renderer, &(screen->terrainCoords), &(screen->bgColorTerrain));

    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);

    int xOffset = 10;
    int yOffset = 40;
    int width = 600;
    int height = 300;

    int currentX = 0;
    int currentY = 0;

    int i, j;
    int squareSize = 10; //TODO works only with multipler of width and height

    for (i = 0; currentX < width; i++) {
        currentX = i * squareSize;
        SDL_RenderDrawLine(renderer, xOffset + currentX, yOffset, xOffset + currentX, yOffset + height);
    }

    for (j = 0; currentY < height; j++) {
        currentY = j * squareSize;
        SDL_RenderDrawLine(renderer, xOffset, yOffset + currentY, xOffset + width, yOffset + currentY);
    }

    SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);

    SDL_RenderDrawLine(renderer, 300 + xOffset, yOffset, 300 + xOffset, yOffset + height);
    SDL_RenderDrawLine(renderer, xOffset, 150 + yOffset, xOffset + width, 150 + yOffset);
}

void calculateOffset(Terrain *terrain, int *xOffset, int *yOffset, TerrainVisualParams *terrainWindow) {
    *xOffset = ((terrainWindow->width - terrain->width) / 2) + terrainWindow->x;
    *yOffset = ((terrainWindow->height - terrain->height) / 2) + terrainWindow->y;
}
