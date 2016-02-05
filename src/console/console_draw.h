#ifndef DRAW_CONSOLE_H
#define DRAW_CONSOLE_H

#include <SDL2/SDL.h>

#include "console_types.h"

#include "../global.h"

#include "../console/console.h"
#include "../console/console_print.h"

#include "../map/global_map.h"

void drawCursor(Console *console, SDL_Renderer *renderer);
void drawConsole(SDL_Renderer *renderer, Console *console);
void printConsoleLine(char *line, SDL_Renderer *renderer, ConsoleVisualParams *params, int *currentLine);

void clearConsoleScreen(SDL_Renderer *renderer, ConsoleVisualParams *params);

int calculateCursorPosition(Console *console);

#endif
