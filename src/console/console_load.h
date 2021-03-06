#ifndef CONSOLE_LOAD_H
#define CONSOLE_LOAD_H

#include "console_types.h"
#include "console_lang.h"
#include "console_print.h"

#include "../font.h"

Console *loadConsole(Font *consoleFont);
Command *loadConsoleCommands();
ConsoleVisualParams *loadConsoleVisual(Font *consoleFont);

void freeConsole(Console *console);
void freeConsoleCommands(Command *commands);
void freeConsoleVisual(ConsoleVisualParams *visual);
void freeConsoleLines(ConsoleVisualParams *visual);

void consoleSetCoords(Console *console, SDL_Rect *paramsRect);

void initConsole(Console *console);

#endif
