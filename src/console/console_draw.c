#include "console_draw.h"

void drawConsole(SDL_Renderer *renderer, Console *console) {
    ConsoleVisualParams *params = console->visual;
    alloc(line, char, params->widthChars + 1);
    int currentLine = 0; //TODO

    clearConsoleScreen(renderer, params);
    showWindow(renderer, console, currentLine, params->heightChars);
    drawBorder(renderer, params->coords, &(params->font->fgColor));
}

void showWindow(SDL_Renderer *renderer, Console *console, int lineStart, int numLines) {
    ConsoleVisualParams *visual = console->visual;
    int width = console->visual->widthChars;
    ConsoleLine *line = NULL;
    int i;
    int currentY;

    for(i = lineStart; i < lineStart + numLines; i++) {
        line = getLineNumber(console, i);

        if(line != NULL) {
            currentY = (i - lineStart) * visual->interLineSpace + visual->coords->y;
            printString(visual->font, renderer, line->content, visual->coords->x, currentY);
        }
    }
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
    SDL_SetRenderDrawColor(renderer, bgColor->r, bgColor->g, bgColor->b, 255);
    SDL_RenderFillRect(renderer, params->coords);
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
}

// l1->l2->l3->NULL
// console->lines: l1
// line: l1
// currentLine: 0
// lineNumber: 1
ConsoleLine *getLineNumber(Console *console, int lineNumber) {
    ConsoleLine *line = console->visual->lines;
    int currentLine = 0;

    while(currentLine < lineNumber && line != NULL) {
        line = line->next;
        currentLine++;
    }

    return (currentLine == lineNumber) ? line : NULL;
}
