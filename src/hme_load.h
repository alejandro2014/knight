#ifndef HME_LOAD_H
#define HME_LOAD_H

#include "main.h"

HeightMapEditor *loadHeightMapEditor();
void loadFonts(HeightMapEditor *hme);

void initScreen(Screen *screen);
SDL_Window *createWindow(char *title, int width, int height);
SDL_Renderer *createRenderer(SDL_Window *window);

void freeHeightMapEditor(HeightMapEditor *hme);
void freeFonts(HeightMapEditor *hme);

TerrainVisualParams *loadTerrainParams(SDL_Rect *paramsRect);
void freeMenus(WMenu *menu);

#endif
