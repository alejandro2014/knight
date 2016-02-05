#ifndef DRAW_CONSOLE_H
#define DRAW_CONSOLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../global.h"

#include "../console/console.h"
#include "../console/console_print.h"

#include "../map/font.h"
#include "../map/global_map.h"

typedef struct {
    SDL_Rect *coords;
    int widthChars, heightChars;
    int interLineSpace;
    int padding;
    int pixelsFill;
    int widthCursor;
    int heightCursor;
    Font *font;
    bool showCursor;
    int cursorTimeOld;
    bool printPrompt;
} ConsoleVisualParams;

void drawCursor(Console *console, SDL_Renderer *renderer, ConsoleVisualParams *consoleParams);
void drawConsole(SDL_Renderer *renderer, Console *console, ConsoleVisualParams *consoleParams);
void printConsoleLine(char *line, SDL_Renderer *renderer, ConsoleVisualParams *params, int *currentLine);

void clearConsoleScreen(SDL_Renderer *renderer, ConsoleVisualParams *params);

int calculateCursorPosition(Console *console);

#endif
