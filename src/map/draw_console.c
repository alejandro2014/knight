#include "draw_console.h"

void drawConsole(SDL_Renderer *renderer, Console *console, ConsoleVisualParams *consoleParams) {
    alloc(line, char, consoleParams->widthChars + 1);
    int numChars = strlen(console->buffer);
    int currentLine = 0;
    char currentChar;
    int i;
    int cursorPos = 0;
    bool finishedLine;
    int windowOffset = console->windowOffset;

    clearConsoleScreen(renderer, consoleParams);

    for(i = windowOffset; i < numChars; i++) {
        currentChar = *(console->buffer + i);
        *(line + cursorPos) = currentChar;
        finishedLine = (cursorPos == consoleParams->widthChars - 1 || currentChar == '\n') ? true : false;

        if(finishedLine) {
            printConsoleLine(line, renderer, consoleParams, &currentLine);
            cursorPos = 0;
        } else {
            cursorPos++;
        }
    }

    printConsoleLine(line, renderer, consoleParams, &currentLine);
    drawConsoleBorder(renderer, consoleParams);
}

/*void prototype() {
    int offsetIni;
    int linesWritten;

    if(linesWritten == 15) {
        moveOffsetIni();
    }
}*/

void printConsoleLine(char *line, SDL_Renderer *renderer, ConsoleVisualParams *params, int *currentLine) {
    int currentY = *currentLine * params->interLineSpace + params->y;
    printString(params->font, renderer, line, params->x, currentY);
    memset(line, 0, params->widthChars + 1);
    (*currentLine)++;
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
