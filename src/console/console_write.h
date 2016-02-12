#ifndef WRITE_CONSOLE_H
#define WRITE_CONSOLE_H

#include <string.h>
#include "console_types.h"

void consoleAddChar(Console *console, char currentChar, bool addToCommand);
void consoleDeleteChar(Console *console);
void consoleNewLine(Console *console);
void consoleAddString(Console *console, char *string, bool addToCommand);
void consoleAddStringLine(Console *console, char *string, bool addToCommand);

void calculateWindowOffset(Console *console);

#endif
