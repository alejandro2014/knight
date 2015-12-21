#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menus.h"
#include "api.h"
#include "console.h"

typedef struct {
    Console *console;
    Dialog **dialogs;
    Terrain *terrain;
    int horSize;
    int verSize;
} HeightMapEditor;

void programLoop();
int loadResources(HeightMapEditor *heightMapEditor);
void freeResources(HeightMapEditor *heightMapEditor);

#endif
