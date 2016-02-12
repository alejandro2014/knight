#ifndef TYPES_H
#define TYPES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../global.h"
#include "../api/types_api.h"

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
    int widthChars, heightChars;
    int interLineSpace;
    int padding;
    int pixelsFill;
    int widthCursor, heightCursor;
    Font *font;
    bool showCursor;
    int cursorTimeOld;
    bool printPrompt;
    int windowOffset;
    int currentLineNumber;
    int lineNumberAbsolute;

    ConsoleLine *lines;
    ConsoleLine *lastLine;
    int lineOffset;
} ConsoleVisualParams;

typedef struct {
    int numCommands;
    Command *commands;
    Command *currentCommand;

    int size;
    char *buffer;
    int offset;

    char *currentLine;
    int currentLineOffset;
    int cursorPos;

    ConsoleVisualParams *visual;
} Console;

#endif
