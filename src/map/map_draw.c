#include "map_draw.h"

void drawBarcodeLine(SDL_Renderer *renderer, int x) {
    SDL_RenderDrawLine(renderer, x, 100, x, 200);
}

void drawRuler(SDL_Renderer *renderer, int widthFactor, int offset) {
    int i, x;

    SDL_SetRenderDrawColor(renderer, 180, 180, 0, 255);
    SDL_RenderDrawLine(renderer, offset, 97, 8 * widthFactor + offset, 97);

    for(i = 0; i < 9; i++) {
        x = i * widthFactor + offset;

        if(i == 4) {
            SDL_RenderDrawLine(renderer, x, 93, x, 101);
        } else {
            SDL_RenderDrawLine(renderer, x, 95, x, 99);
        }
    }
}

void drawBarcodeDigit(SDL_Renderer *renderer, char digit, int offset) {
    int widthFactor = 10;
    int i, j;
    char temp = 0x00;

    drawRuler(renderer, widthFactor, offset);
    SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);

    for(i = 0; i < 8; i++) {
        temp = digit;
        temp >>= (7 - i);
        temp &= 0x01;

        if (temp == 0x01) {
            for(j = 0; j < widthFactor; j++) {
                drawBarcodeLine(renderer, i * widthFactor + j + offset);
            }
        }
    }
}

void drawTerrain(Screen *screen, Terrain *terrain, TerrainVisualParams *params) {
    SDL_Renderer *renderer = screen->renderer;
    int x, y;
    int color;

    clearSubScreen(renderer, &(screen->terrainCoords), &(screen->bgColorTerrain));

    drawBarcodeDigit(renderer, '1', 10);

    drawBarcodeDigit(renderer, '2', 120);

    drawBarcodeDigit(renderer, '3', 220);
    /*int xOffset = 10;
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
    SDL_RenderDrawLine(renderer, xOffset, 150 + yOffset, xOffset + width, 150 + yOffset);*/
}

void calculateOffset(Terrain *terrain, int *xOffset, int *yOffset, TerrainVisualParams *terrainWindow) {
    *xOffset = ((terrainWindow->width - terrain->width) / 2) + terrainWindow->x;
    *yOffset = ((terrainWindow->height - terrain->height) / 2) + terrainWindow->y;
}
