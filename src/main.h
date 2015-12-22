#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menus.h"
#include "api/api.h"
#include "console/console.h"

typedef struct {
    Console *console;
    Dialog **dialogs;
    Terrain *terrain;
    int horSize;
    int verSize;
} HeightMapEditor;

#endif
