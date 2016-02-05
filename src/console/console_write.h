#ifndef WRITE_CONSOLE_H
#define WRITE_CONSOLE_H

#include <string.h>
#include "types_console.h"

void consoleAddChar(Console *console, char currentChar);
void consoleDeleteChar(Console *console);
void consoleNewLine(Console *console);
void consoleAddString(Console *console, char *string);
void consoleAddStringLine(Console *console, char *string);

void calculateWindowOffset(Console *console);

#endif
