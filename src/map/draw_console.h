#ifndef DRAW_CONSOLE_H
#define DRAW_CONSOLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../global.h"

#include "../console/console.h"
#include "../console/print.h"

#include "font.h"

/*
0 ----
1 ----
2 ----
3 ++++
4 ++++
5 ++++
6 ----
7 ----
*/
typedef struct {
    int x, y;
    int widthChars, heightChars;
    int widthPixels, heightPixels;
    int interLineSpace;
    int padding;
    int pixelsFill;
    int widthCursor;
    int heightCursor;
    Font *font;
    bool showCursor;
    int cursorTimeOld;
    bool printPrompt;

    int lineStart;
    int lineEnd;
    int currentLine;
} ConsoleVisualParams;

void drawCursor(Console *console, SDL_Renderer *renderer, ConsoleVisualParams *consoleParams);
void drawConsole(SDL_Renderer *renderer, Console *console, ConsoleVisualParams *consoleParams);
void drawConsoleBorder(SDL_Renderer *renderer, ConsoleVisualParams *consoleParams);

void clearConsoleScreen(SDL_Renderer *renderer, ConsoleVisualParams *consoleParams);

int calculateCursorPosition(Console *console);

#endif
