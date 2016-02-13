#ifndef CONSOLE_TYPES_H
#define CONSOLE_TYPES_H

#include <SDL2/SDL.h>

#include "../global.h"

#include "../map/font.h"

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

typedef struct ConsoleLine {
    char *content;
    bool newLine;
    struct ConsoleLine *previous;
    struct ConsoleLine *next;
} ConsoleLine;

typedef struct {
    SDL_Rect *coords;
    Font *font;
    int widthChars;
    int heightChars;

    bool showCursor;
    int widthCursor;
    int heightCursor;
    int cursorTimeOld;

    bool printPrompt;
    int windowOffset;
    int currentLineNumber;
    int lineNumberAbsolute;

    ConsoleLine *lines;
    ConsoleLine *lastLine;
    int lineOffset;

    int interLineSpace;
    int padding;
    int pixelsFill;
} ConsoleVisualParams;

typedef struct {
    ConsoleVisualParams *visual;

    //TODO
    int numCommands;
    Command *commands;
    Command *currentCommand;

    char *currentLine;
    int currentLineOffset;
    int maxLineLength;
} Console;

#endif
