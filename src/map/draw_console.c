#include "draw_console.h"

void drawConsole(SDL_Renderer *renderer, Console *console, ConsoleVisualParams *params) {
    //console->buffer = "first line\nsecond line\n0123456789012345678901234567890123456789";
    alloc(line, char, params->widthChars + 1);
    int numChars = strlen(console->buffer);
    int currentLine = 0;
    char currentChar;
    int i;
    int cursorPos = 0;
    bool finishedLine;
    int windowOffset = console->windowOffset;

    clearConsoleScreen(renderer, params);

    for(i = windowOffset; i < numChars; i++) {
        currentChar = *(console->buffer + i);
        *(line + cursorPos) = currentChar;
        finishedLine = (cursorPos == params->widthChars - 1 || currentChar == '\n') ? true : false;

        if(finishedLine) {
            printConsoleLine(line, renderer, params, &currentLine);
            cursorPos = 0;
        } else {
            cursorPos++;
        }
    }

    printConsoleLine(line, renderer, params, &currentLine);
    drawBorder(renderer, params->coords, &(params->font->fgColor));
}

void printConsoleLine(char *line, SDL_Renderer *renderer, ConsoleVisualParams *params, int *currentLine) {
    int currentY = *currentLine * params->interLineSpace + params->coords->y;
    printString(params->font, renderer, line, params->coords->x, currentY);
    memset(line, 0, params->widthChars + 1);
    (*currentLine)++;
}

void drawCursor(Console *console, SDL_Renderer *renderer, ConsoleVisualParams *consoleParams) {
    SDL_Color *color = &(consoleParams->font->fgColor);
    int cursorPosition = calculateCursorPosition(console);
    int row = cursorPosition / consoleParams->widthChars;
    int col = cursorPosition % consoleParams->widthChars;
    int maxRows = consoleParams->heightChars;

    if(row > maxRows) row = maxRows;

    SDL_Rect r;
    r.w = consoleParams->widthCursor;
    r.h = consoleParams->heightCursor;
    r.x = col * r.w + consoleParams->coords->x;
    r.y = row * (r.h + consoleParams->pixelsFill) + consoleParams->coords->y;

    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);
    SDL_RenderFillRect(renderer, &r);
}

void clearConsoleScreen(SDL_Renderer *renderer, ConsoleVisualParams *params) {
    SDL_Color *bgColor = &(params->font->bgColor);
    SDL_SetRenderDrawColor(renderer, bgColor->r, bgColor->g, bgColor->b, 255);
    SDL_RenderFillRect(renderer, params->coords);
}

int calculateCursorPosition(Console *console) {
    int lineLength = 80; //TODO Hardcoded variable
    int offsetScreen = 0;
    int offsetLine = 0;
    int length = strlen(console->buffer);
    int i;
    char currentChar;

    for(i = 0; i < length; i++) {
        currentChar = *(console->buffer + i);

        if(offsetLine == lineLength) {
            offsetScreen++;
            offsetLine = 0;
        } else if(currentChar == '\n') {
            offsetScreen += lineLength - offsetLine;
            offsetLine = 0;
        } else {
            offsetScreen++;
            offsetLine++;
        }
    }

    return offsetScreen;
}
