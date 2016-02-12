#ifndef DRAW_CONSOLE_H
#define DRAW_CONSOLE_H

#include <SDL2/SDL.h>

#include "console_types.h"

#include "../global.h"

#include "../console/console_lang.h"
#include "../console/console_print.h"

#include "../map/global_map.h"

void drawCursor(Console *console, SDL_Renderer *renderer);
void drawConsole(SDL_Renderer *renderer, Console *console);

void clearConsoleScreen(SDL_Renderer *renderer, ConsoleVisualParams *params);

void showWindow(SDL_Renderer *renderer, Console *console);
void consolePrintLine(SDL_Renderer *renderer, Console *console, char *content, int lineNumber);
void addLineToConsole(Console *console);
ConsoleLine *consoleGetLineByNumber(Console *console, int lineNumber);

#endif
