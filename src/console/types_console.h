#ifndef TYPES_H
#define TYPES_H

#include "../global.h"
#include "../api/types_api.h"

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
    int numCommands;
    Command *commands;
    Command *currentCommand;
    Terrain *terrain; //TODO Coupled with map

    int size;
    char *buffer;
    int offset;
    int lastLineOffset;

    char *currentLine;
    int cursorPos;

    int windowOffset; //TODO
    int currentLineNumber; //TODO
} Console;

#endif
