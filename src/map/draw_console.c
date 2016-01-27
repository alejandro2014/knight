#include "draw_console.h"

void drawConsole(SDL_Renderer *renderer, Console *console, ConsoleVisualParams *consoleParams) {
    Font *font = consoleParams->font;
    int numChars = strlen(console->buffer);
    int currentLine = 0;
    int linePos = 0;
    char currentChar;
    int i;
    int offsetLine = 0;
    int currentY;

    clearConsoleScreen(renderer, consoleParams);

    alloc(line, char, consoleParams->widthChars + 1);

    for(i = 0; i < numChars; i++) {
        currentChar = *(console->buffer + i);
        *(line + offsetLine) = currentChar;

        if(offsetLine == consoleParams->widthChars - 1 || currentChar == '\n') {
            currentY = (currentLine++) * consoleParams->interLineSpace + consoleParams->y;
            printString(font, renderer, line, consoleParams->x, currentY);
            memset(line, 0, consoleParams->widthChars + 1);
            offsetLine = 0;
        } else {
            offsetLine++;
        }
    }

    currentY = (currentLine++) * consoleParams->interLineSpace + consoleParams->y;
    printString(font, renderer, line, consoleParams->x, currentY);

    drawConsoleBorder(renderer, consoleParams);
}

void drawCursor(Console *console, SDL_Renderer *renderer, ConsoleVisualParams *consoleParams) {
    SDL_Color *color = &(consoleParams->font->fgColor);
    int cursorPosition = calculateCursorPosition(console);
    int row = cursorPosition / consoleParams->widthChars;
    int col = cursorPosition % consoleParams->widthChars;

    SDL_Rect r;
    r.w = consoleParams->widthCursor;
    r.h = consoleParams->heightCursor;
    r.x = col * r.w + consoleParams->x;
    r.y = row * (r.h + consoleParams->pixelsFill) + consoleParams->y;

    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);
    SDL_RenderFillRect(renderer, &r);
}

void clearConsoleScreen(SDL_Renderer *renderer, ConsoleVisualParams *consoleParams) {
    SDL_Color *bgColor = &(consoleParams->font->bgColor);
    SDL_SetRenderDrawColor(renderer, bgColor->r, bgColor->g, bgColor->b, 255);

    SDL_Rect r;
    r.w = consoleParams->widthPixels;
    r.h = consoleParams->heightPixels;
    r.x = consoleParams->x;
    r.y = consoleParams->y;
    SDL_RenderFillRect(renderer, &r);
}

void drawConsoleBorder(SDL_Renderer *renderer, ConsoleVisualParams *consoleParams) {
    SDL_Color *color = &(consoleParams->font->fgColor);

    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);
    SDL_RenderDrawLine(renderer, consoleParams->x, consoleParams->y, 800, consoleParams->y);
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
