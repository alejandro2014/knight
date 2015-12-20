#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"

#define LINE_LENGTH 100
#define NUM_COMMANDS 6
#define MAX_PARAMS 10

typedef struct {
    char *key;
    char *value;
} Param;

typedef struct {
    char *name;
    Param *params;
    int numParams;
    char *target;
} Command;

typedef struct {
    int offset;
    int cursorPosition;
    int size;
    char *text;
    char *currentLine;
    size_t sizeLine;
    int numCommands;
    Command *commands;
    Command *currentCommand;
} Console;

Console *createConsole(int sizeKb);
void freeConsole(Console *console);

Command *loadCommands(Console *console);
void addCommand(char *commandName, Console *console);
void addParam(char *paramName, char *commandName, Console *console);

void printPrompt();
void printCommands(Console *console);
void printCommand(Command *command);

void readShellLine(Console *console);
Command *parseCommand(char *strCommand, Console *console);
bool getCommandParams(Command *command);
void parseParam(char *paramString, char **key, char **value);

Command *lookupCommand(char *commandName, Console *console);
Param *lookupParam(char *paramName, Command *command);

void executeCommand(Command *command);
int getParamValueInt(char *paramName, Command *command, bool *error);
void deleteParamsValue(Command *command);

#endif
