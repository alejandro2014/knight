#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../global.h"

#include "../api/api.h"
#include "../api/hme_lowlevel.h"
#include "../api/generate_terrain.h"
#include "../api/flood.h"
#include "../api/replace.h"

#include "console_types.h"
#include "console_write.h"

#define LINE_LENGTH 50
#define NUM_COMMANDS 30
#define MAX_PARAMS 10

#define P0 *(intParams+0)
#define P1 *(intParams+1)
#define P2 *(intParams+2)
#define P3 *(intParams+3)
#define P4 *(intParams+4)
#define P5 *(intParams+5)
#define P6 *(intParams+6)
#define P7 *(intParams+7)

bool processCommand(Console *console);
Command *parseCommand(char *strCommand, Console *console);
bool getCommandParams(Command *command);
void parseParam(char *paramString, char **key, char **value);

Command *lookupCommand(char *commandName, Console *console);
Param *lookupParam(char *paramName, Command *command);

bool areParamsValid(Command *command, int *params, char **strParams, char *infoMessage);
void printInfoMessage(char *infoMessage, Console *console);

void executeCommand(Console *console);
int getParamValueInt(char *paramName, Command *command, bool *error, char *infoMessage);
char *getParamValueStr(char *paramName, Command *command, bool *validParam, char *infoMessage);
void deleteParamsValue(Command *command);

void loadScript(Console *console, char *pathScript);

void consoleResize(Console *console, int newRowsNum, int newColsNum);

#endif
