#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"
#include "api/api.h"
#include "api/hme_lowlevel.h"
#include "console/console.h"
#include "console/print.h"

#include "2d/window.h"

typedef struct {
    Console *console;
    Terrain *terrain;
    int horSize;
    int verSize;
} HeightMapEditor;

HeightMapEditor *loadHeightMapEditor();

#endif
