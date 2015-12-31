#ifndef BMP_H
#define BMP_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../global.h"

typedef struct {
    uint16_t header;
    uint32_t fileSize;
    uint32_t unused;
    uint32_t dataOffset;
    uint32_t dibHeaderSize;
    uint32_t width;

    uint32_t height;
    uint16_t colorPlanes;
    uint16_t bitsPerPixel;
    uint32_t biRgb;
    uint32_t sizeBmpRawData;
    uint32_t printResHor;

    uint32_t printResVer;
    uint32_t paletteColorsNo;
    uint32_t importantColorsNo;
} BmpHeader;

void save_bmp(char * FileName, char * raw_mem, int x_size, int y_size);
bool load_bmp(char * FileName);

#endif
