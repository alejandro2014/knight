#include "map_draw.h"

void drawBarcodeLine(SDL_Renderer *renderer, int x, int height) {
    SDL_RenderDrawLine(renderer, x, 100, x, 100 + height);
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

void drawBarcodeDigit(SDL_Renderer *renderer, char digit, int offset, int widthFactor, int height) {
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
                drawBarcodeLine(renderer, i * widthFactor + j + offset, height);
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

char getBarcodeDigitLeftSide(char number, int isOdd) {
    char odd[] = { 0x0d, 0x19, 0x13, 0x3d, 0x23, 0x31, 0x2f, 0x3b, 0x37, 0x0b };
    char even[] = { 0x27, 0x33, 0x1b, 0x21, 0x1d, 0x39, 0x05, 0x11, 0x09, 0x17 };
    int digit = number - 0x30;

    return (isOdd ? odd[digit] : even[digit]);
}

char getBarcodeDigitRigthSide(char number) {
    char digitsArray[] = { 0x72, 0x66, 0x6c, 0x42, 0x5c, 0x4e, 0x50, 0x44, 0x48, 0x74 };
    int digit = number - 0x30;

    return digitsArray[digit];
}

void drawTerrain(Screen *screen, Terrain *terrain, TerrainVisualParams *params) {
    SDL_Renderer *renderer = screen->renderer;
    char digit;
    int parity;
    char *leftDigits = "501031";
    char *rightDigits = "311309";

    int i;
    int widthFactor = 7;
    int offset = 50;

    clearSubScreen(renderer, &(screen->terrainCoords), &(screen->bgColorTerrain));

    drawBarcodeDigit(renderer, 0x05, -7 * widthFactor + offset, widthFactor, 120);

    for(i = 0; i < 6; i++) {
        parity = getParity('7', i);
        digit = getBarcodeDigitLeftSide(*(leftDigits + i), parity);
        drawBarcodeDigit(renderer, digit, 7 * widthFactor * i + offset, widthFactor, 100);
    }

    drawBarcodeDigit(renderer, 0x05, 39 * widthFactor + offset, widthFactor, 120);

    for(i = 0; i < 6; i++) {
        digit = getBarcodeDigitRigthSide(*(rightDigits + i));
        drawBarcodeDigit(renderer, digit, (7 * i + 47) * widthFactor + offset, widthFactor, 100);
    }

    drawBarcodeDigit(renderer, 0x05, 85 * widthFactor + offset, widthFactor, 120);
}

void calculateOffset(Terrain *terrain, int *xOffset, int *yOffset, TerrainVisualParams *terrainWindow) {
    *xOffset = ((terrainWindow->width - terrain->width) / 2) + terrainWindow->x;
    *yOffset = ((terrainWindow->height - terrain->height) / 2) + terrainWindow->y;
}
