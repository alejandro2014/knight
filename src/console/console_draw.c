#include "console_draw.h"

void drawConsole(SDL_Renderer *renderer, Console *console) {
    ConsoleVisualParams *params = console->visual;
    alloc(line, char, params->widthChars + 1);
    int currentLine = 0; //TODO

    clearConsoleScreen(renderer, params);
    showWindow(renderer, console, currentLine, console->visual->widthChars);
    drawBorder(renderer, params->coords, &(params->font->fgColor));
}

void showWindow(SDL_Renderer *renderer, Console *console, int lineStart, int numLines) {
    int width = console->visual->widthChars;
    ConsoleLine *line = NULL;
    int i;
    int currentY;

    for(i = lineStart; i < lineStart + numLines; i++) {
        line = getLineNumber(console, i);

        if(line != NULL) {
            currentY = i * console->visual->interLineSpace;
            printString(console->visual->font, renderer, line->content, console->visual->coords->x, currentY);
        }
    }
}

void drawCursor(Console *console, SDL_Renderer *renderer) {
    ConsoleVisualParams *consoleParams = console->visual;
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

void addLineToConsole(Console *console) {
    int lengthLine = console->visual->widthChars;
    alloc(newConsoleLine, ConsoleLine, 1);
    allocExist(newConsoleLine->content, char, lengthLine);

    if(console->visual->lastLine != NULL) {
        console->visual->lastLine->next = newConsoleLine;
        newConsoleLine->previous = console->visual->lastLine;
    } else {
        console->visual->lines = newConsoleLine;
    }

    console->visual->lastLine = newConsoleLine;
    console->visual->lineOffset = 0;
}

ConsoleLine *getLineNumber(Console *console, int lineNumber) {
    ConsoleLine *line = console->visual->lines;
    int currentLine = 0;

    while(currentLine < lineNumber && line != NULL) {
        line = line->next;
        currentLine++;
    }

    return (currentLine == lineNumber) ? line : NULL;
}
