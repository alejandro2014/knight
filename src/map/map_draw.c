#include "map_draw.h"

void drawBarcodeLine(SDL_Renderer *renderer, int x) {
    SDL_RenderDrawLine(renderer, x, 100, x, 200);
}

void drawRuler(SDL_Renderer *renderer, int widthFactor, int offset) {
    int i, x;

    SDL_SetRenderDrawColor(renderer, 180, 180, 0, 255);
    SDL_RenderDrawLine(renderer, widthFactor + offset, 97, 8 * widthFactor + offset, 97);

    for(i = 1; i < 9; i++) {
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

    for(i = 1; i < 8; i++) {
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

int getParity(char ctrlDigit, int position) {
    int parities[10][6] = {
        { 1, 1, 1, 1, 1, 1 }, { 1, 1, 0, 1, 0, 0 }, { 1, 1, 0, 0, 1, 0 }, /* 012 */
        { 1, 1, 0, 0, 0, 1 }, { 1, 0, 1, 1, 0, 0 }, { 1, 0, 0, 1, 1, 0 }, /* 345 */
        { 1, 0, 0, 0, 1, 1 }, { 1, 0, 1, 0, 1, 0 }, { 1, 0, 1, 0, 0, 1 }, /* 678 */
        { 1, 0, 0, 1, 0, 1 } /* 9 */
    };

    int controlDigit = ctrlDigit - 0x30;

    return parities[controlDigit][position];
}

char getBarcodeDigit(char number, int isOdd) {
    char odd[] = { 0x0d, 0x19, 0x13, 0x3d, 0x23, 0x31, 0x2f, 0x3b, 0x37, 0x0b };
    char even[] = { 0x27, 0x33, 0x1b, 0x21, 0x1d, 0x39, 0x05, 0x11, 0x09, 0x17 };
    int digit = number - 0x30;

    return (isOdd ? odd[digit] : even[digit]);
}

void drawTerrain(Screen *screen, Terrain *terrain, TerrainVisualParams *params) {
    SDL_Renderer *renderer = screen->renderer;
    int x, y;
    int color;
    char digit;
    int parity;

    clearSubScreen(renderer, &(screen->terrainCoords), &(screen->bgColorTerrain));

    parity = getParity('7', 0);
    digit = getBarcodeDigit('5', parity);
    drawBarcodeDigit(renderer, digit, 10);

    parity = getParity('7', 1);
    digit = getBarcodeDigit('0', parity);
    drawBarcodeDigit(renderer, digit, 110);

    parity = getParity('7', 2);
    digit = getBarcodeDigit('1', parity);
    drawBarcodeDigit(renderer, digit, 210);

    parity = getParity('7', 3);
    digit = getBarcodeDigit('0', parity);
    drawBarcodeDigit(renderer, digit, 310);

    parity = getParity('7', 4);
    digit = getBarcodeDigit('3', parity);
    drawBarcodeDigit(renderer, digit, 410);

    parity = getParity('7', 5);
    digit = getBarcodeDigit('1', parity);
    drawBarcodeDigit(renderer, digit, 510);

    //drawBarcodeDigit(renderer, '3', 220);

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
