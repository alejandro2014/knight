#ifndef HME_LOAD_H
#define HME_LOAD_H

#include "main.h"

HeightMapEditor *loadHeightMapEditor();
/*SDL_Window *createWindow(char *title, int width, int height);
SDL_Renderer *createRenderer(SDL_Window *window);*/
void freeResources(HeightMapEditor *hme);
//TerrainVisualParams *loadTerrainParams(SDL_Rect *paramsRect);

#endif
