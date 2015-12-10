#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>

#include "menus.h"
#include "terrain.h"

typedef struct {
    Dialog **dialogs;
    Terrain *terrain;
} HeightMapEditor;

void programLoop();
int loadResources(HeightMapEditor *heightMapEditor);
void freeResources(HeightMapEditor *heightMapEditor);

#endif
