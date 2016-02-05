#ifndef LOAD_CONSOLE_H
#define LOAD_CONSOLE_H

#include "console.h"

Console *createConsole(int sizeKb);
void freeConsole(Console *console);

Command *loadCommands(Console *console);
void addCommand(char *commandName, Console *console);
void addCommandIntParams(char *commandName, char *params[], int numParams, Console *console);
void addCommandStrParams(char *commandName, char *params[], int numParams, Console *console);
void addParam(char *paramName, char *commandName, ParamType type, Console *console);

#endif
