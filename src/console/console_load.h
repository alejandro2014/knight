#ifndef CONSOLE_LOAD_H
#define CONSOLE_LOAD_H

#include "console_types.h"
#include "console_lang.h"
#include "console_print.h"

Console *loadConsole();
Command *loadConsoleCommands();
ConsoleVisualParams *loadConsoleVisual();

void freeConsole(Console *console);
void freeConsoleCommands(Command *commands);
void freeConsoleVisual(ConsoleVisualParams *visual);
void freeConsoleLines(ConsoleVisualParams *visual);

void consoleSetCoords(Console *console, SDL_Rect *paramsRect);

void initConsole(Console *console);

#endif
