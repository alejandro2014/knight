#ifndef PRINT_H
#define PRINT_H

#include "console.h"
#include "../api/api.h"

void printPrompt();
void printCommands(Console *console);
void printCommand(Command *command);
void printConsoleBanner(Console *console);

void printTerrain(Terrain *terrain);
void printLine(int width);

#endif
