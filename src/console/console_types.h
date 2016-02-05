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

typedef struct {
    SDL_Rect *coords;
    int widthChars, heightChars;
    int interLineSpace;
    int padding;
    int pixelsFill;
    int widthCursor;
    int heightCursor;
    Font *font;
    bool showCursor;
    int cursorTimeOld;
    bool printPrompt;
    int windowOffset;
    int currentLineNumber;
} ConsoleVisualParams;

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

    ConsoleVisualParams *visual;
} Console;

#endif
