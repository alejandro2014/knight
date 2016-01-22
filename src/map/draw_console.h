#ifndef DRAW_CONSOLE_H
#define DRAW_CONSOLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../global.h"

#include "../console/console.h"

#include "font.h"

typedef struct {
    int x, y;
    int width, height;
    int interLineSpace;
    int padding;
    int pixelsFill;
    int widthCursor;
    int heightCursor;
    Font *font;
    bool showCursor;
} ConsoleVisualParams;

void drawCursor(Console *console, SDL_Renderer *renderer, SDL_Color *color, ConsoleVisualParams *consoleParams);
void drawConsole(SDL_Renderer *renderer, Console *console, ConsoleVisualParams *consoleParams);

int calculateCursorPosition(Console *console);

#endif
