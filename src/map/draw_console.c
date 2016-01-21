#include "draw_console.h"

void drawConsole(SDL_Renderer *renderer, Font *font, Console *console, ConsoleVisualParams *consoleParams) {
    int numChars = strlen(console->buffer);
    int currentLine = 0;
    int linePos = 0;
    char currentChar;
    int i;
    int offsetLine = 0;

    int currentY;

    alloc(line, char, consoleParams->width + 1);

    for(i = 0; i < numChars; i++) {
        currentChar = *(console->buffer + i);
        *(line + offsetLine) = currentChar;

        if(offsetLine == consoleParams->width - 1 || currentChar == '\n') {
            currentY = (currentLine++) * consoleParams->interLineSpace + consoleParams->y;
            printString(font, renderer, line, consoleParams->x, currentY);
            memset(line, 0, consoleParams->width + 1);
            offsetLine = 0;
        } else {
            offsetLine++;
        }
    }

    currentY = (currentLine++) * consoleParams->interLineSpace + consoleParams->y;
    printString(font, renderer, line, consoleParams->x, currentY);

    SDL_SetRenderDrawColor(renderer, 150, 0, 0, 255);
    SDL_RenderDrawLine(renderer, consoleParams->x, consoleParams->y, consoleParams->x, 600);
    SDL_RenderDrawLine(renderer, consoleParams->x, consoleParams->y, 800, consoleParams->y);
}

void drawCursor(Console *console, SDL_Renderer *renderer, SDL_Color *color, ConsoleVisualParams *consoleParams) {
    int cursorPosition = calculateCursorPosition(console);
    int row = cursorPosition / consoleParams->width;
    int col = cursorPosition % consoleParams->width;

    SDL_Rect r;
    r.w = consoleParams->widthCursor;
    r.h = consoleParams->heightCursor;
    r.x = col * r.w + consoleParams->x;
    r.y = row * (r.h + consoleParams->pixelsFill) + consoleParams->y;

    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);
    SDL_RenderFillRect(renderer, &r);
}

int calculateCursorPosition(Console *console) {
    int offsetScreen = 0;
    int offsetLine = 0;
    int length = strlen(console->buffer);
    int i;
    char currentChar;

    for(i = 0; i < length; i++) {
        currentChar = *(console->buffer + i);

        if(offsetLine == 80) {
            offsetScreen++;
            offsetLine = 0;
        } else if(currentChar == '\n') {
            offsetScreen += 80 - offsetLine;
            offsetLine = 0;
        } else {
            offsetScreen++;
            offsetLine++;
        }
    }

    return offsetScreen;
}
