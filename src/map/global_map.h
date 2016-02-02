#ifndef GLOBAL_MAP_H
#define GLOBAL_MAP_H

#include "../global.h"

typedef struct {
    bool consoleNewLine;
    bool updateScreen;
    bool updateMap;
    bool updateConsole;
    bool finish;
    bool printPrompt;
} Events;

void setRect(SDL_Rect *rect, int x, int y, int w, int h);

#endif
