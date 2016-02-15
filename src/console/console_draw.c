#include "console_draw.h"

void drawConsole(SDL_Renderer *renderer, Console *console) {
    ConsoleVisualParams *params = console->visual;

    clearConsoleScreen(renderer, params);
    showWindow(renderer, console);
    drawBorder(renderer, params->coords, &(params->font->fgColor));
}

void showWindow(SDL_Renderer *renderer, Console *console) {
    ConsoleVisualParams *visual = console->visual;
    ConsoleLine *line = NULL;
    int lineStartAbs, lineEndAbs;
    int lineWindow;
    int i;

    consoleCalculateOffsetWindow(visual, &lineStartAbs, &lineEndAbs);

    for(i = lineStartAbs; i < lineEndAbs; i++) {
        line = consoleGetLineByNumber(console, i);

        if(line != NULL) {
            lineWindow = i - lineStartAbs;
            consolePrintLine(renderer, console, line->content, lineWindow);
        }
    }
}

void consoleCalculateOffsetWindow(ConsoleVisualParams *visual, int *lineStartAbs, int *lineEndAbs) {
    *lineStartAbs = visual->lineNumberAbsolute;

    if(visual->currentLineNumber >= visual->heightChars) {
        *lineStartAbs = visual->currentLineNumber - visual->heightChars;
    }

    *lineEndAbs = *lineStartAbs + visual->heightChars;
}

void consolePrintLine(SDL_Renderer *renderer, Console *console, char *content, int lineNumber) {
    ConsoleVisualParams *visual = console->visual;
    SDL_Rect *coords = visual->coords;
    printString(visual->font, renderer, content, coords->x, lineNumber * visual->interLineSpace + coords->y);
}

void drawCursor(Console *console, SDL_Renderer *renderer) {
    ConsoleVisualParams *visual = console->visual;
    SDL_Color *color = &(visual->font->fgColor);
    int row = visual->currentLineNumber;
    int col = visual->lineOffset;
    int maxRows = visual->heightChars;

    if(row > maxRows) row = maxRows;

    SDL_Rect r;
    r.w = visual->widthCursor;
    r.h = visual->heightCursor;
    r.x = col * r.w + visual->coords->x;
    r.y = row * (r.h + visual->pixelsFill) + visual->coords->y;

    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);
    SDL_RenderFillRect(renderer, &r);
}

void clearConsoleScreen(SDL_Renderer *renderer, ConsoleVisualParams *params) {
    SDL_Color *bgColor = &(params->font->bgColor);
    clearSubScreen(renderer, params->coords, bgColor);
}

void addLineToConsole(Console *console) {
    ConsoleVisualParams *visual = console->visual;
    ConsoleLine *lastLine = visual->lastLine;
    ConsoleLine *newLine = NULL;
    int lengthLine = visual->widthChars;

    if(lastLine == NULL) {
        allocExist(newLine, ConsoleLine, 1);
        allocExist(newLine->content, char, lengthLine + 1);
        visual->lines = newLine;
        visual->lastLine = newLine;
    } else if(lastLine->next == NULL) {
        allocExist(newLine, ConsoleLine, 1);
        allocExist(newLine->content, char, lengthLine + 1);
        lastLine->next = newLine;
        newLine->previous = lastLine;
        visual->lastLine = newLine;
    } else {
        visual->lastLine = visual->lastLine->next;
    }

    visual->lineOffset = 0;
    visual->currentLineNumber++;
    //visual->lineNumberAbsolute++;
}

ConsoleLine *consoleGetLineByNumber(Console *console, int lineNumber) {
    ConsoleLine *line = console->visual->lines;
    int currentLine = 0;

    while(currentLine < lineNumber && line != NULL) {
        line = line->next;
        currentLine++;
    }

    return (currentLine == lineNumber) ? line : NULL;
}
