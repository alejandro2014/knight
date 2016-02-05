#ifndef PRINT_H
#define PRINT_H

#include "../api/api.h"

#include "console.h"

void printConsolePrompt(Console *console);
void printCommands(Console *console);
void printCommand(Command *command);
void printConsoleBanner(Console *console);

#endif
