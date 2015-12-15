#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>

#include "menus.h"
#include "api.h"

typedef struct {
    Dialog **dialogs;
    Terrain *terrain;
    int horSize;
    int verSize;
} HeightMapEditor;

void programLoop();
int loadResources(HeightMapEditor *heightMapEditor);
void freeResources(HeightMapEditor *heightMapEditor);

#endif
