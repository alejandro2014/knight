#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../global.h"
#include "../api/api.h"

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

typedef int ParamType;
#define STRING 0
#define INT 1

typedef struct {
    char *key;
    char *value;
    ParamType type;
} Param;

typedef struct {
    char *name;
    Param *params;
    int numParams;
    char *target;
} Command;

typedef struct {
    int cursorPosition;
    size_t interLineSpace;
    int numCommands;
    Command *commands;
    Command *currentCommand;
    Terrain *terrain;

    int size;
    char *buffer;
    int offset;

    int width;
    int height;
    char *window;
    char *currentLine;
    int cursorRow;
    int cursorCol;
} Console;

Console *createConsole(int sizeKb, int width, int height);
void freeConsole(Console *console);

Command *loadCommands(Console *console);
void addCommand(char *commandName, Console *console);
void addCommandIntParams(char *commandName, char *params[], int numParams, Console *console);
void addCommandStrParams(char *commandName, char *params[], int numParams, Console *console);
void addParam(char *paramName, char *commandName, ParamType type, Console *console);

void readShellLine(Console *console, FILE *inputStream);
bool processCommand(char *textCommand, Console *console);
Command *parseCommand(char *strCommand, Console *console);
bool getCommandParams(Command *command);
void parseParam(char *paramString, char **key, char **value);

Command *lookupCommand(char *commandName, Console *console);
Param *lookupParam(char *paramName, Command *command);

bool areParamsValid(Command *command, int *params, char **strParams);
void executeCommand(Console *console);
int getParamValueInt(char *paramName, Command *command, bool *error);
char *getParamValueStr(char *paramName, Command *command, bool *validParam);
void deleteParamsValue(Command *command);

void loadScript(Console *console, char *pathScript);

void consoleAddChar(Console *console, char currentChar);
void consoleDeleteChar(Console *console);
void consoleNewLine(Console *console);
void consoleAddString(Console *console, char *string);
void consoleResize(Console *console, int newRowsNum, int newColsNum);

#endif
