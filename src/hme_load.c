#include "hme_load.h"

extern Events *events;

HeightMapEditor *loadHeightMapEditor() {
    alloc(hme, HeightMapEditor, 1);

    allocExist(hme->screen, Screen, 1);

    hme->screen->bgColorTerrain.r = 80;
    hme->screen->bgColorTerrain.g = 40;
    hme->screen->bgColorTerrain.b = 40;

    hme->screen->bgColorMenuBar.r = 40;
    hme->screen->bgColorMenuBar.g = 80;
    hme->screen->bgColorMenuBar.b = 40;

    loadFonts(hme);

    hme->console = loadConsole(hme->fontConsole);
    addCommands(hme->console);

    hmeSetLayout(hme->screen, LAYOUT_HOR_TERRAIN_CONSOLE, hme->console);

    hme->terrainParams = loadTerrainParams(&(hme->screen->terrainCoords));

    //hme->dialogs = loadDialogs(hme->dialogsFont);

    hme->screen->window = createWindow("Knight", hme->screen->width, hme->screen->height);
    hme->screen->renderer = createRenderer(hme->screen->window);

    hme->menuBar = loadMenu(hme->fontMenusNormal, hme->fontMenusSelected);
    allocExist(events, Events, 1);

    return hme;
}

SDL_Window *createWindow(char *title, int width, int height) {
    SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
                    SDL_WINDOW_RESIZABLE);

    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
    }

    return window;
}

SDL_Renderer *createRenderer(SDL_Window *window) {
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(renderer == NULL) {
        printf("Could not create renderer: %s\n", SDL_GetError());
    }

    return renderer;
}

void freeResources(HeightMapEditor *hme) {
    freeFonts(hme);
    freeConsole(hme->console);
    //freeDialogs(hme->dialogs);

    SDL_DestroyRenderer(hme->screen->renderer);
    SDL_DestroyWindow(hme->screen->window);

    free(hme->terrainParams);
    //api_freeTerrain(hme->terrain);
    free(hme->screen);
    free(hme);
    free(events);
}

void loadFonts(HeightMapEditor *hme) {
    TTF_Init();

    SDL_Color bgColor, fgColor;

    fgColor.r = 180;
    fgColor.g = 180;
    fgColor.b = 180;
    bgColor.r = 50;
    bgColor.g = 50;
    bgColor.b = 50;
    hme->fontConsole = loadFont(FONT_PATH_MAC, 16, &fgColor, &bgColor);

    fgColor.r = 200;
    fgColor.g = 200;
    fgColor.b = 200;
    bgColor.r = 0;
    bgColor.g = 0;
    bgColor.b = 100;
    hme->fontDialogsTitle = loadFont(FONT_PATH_MAC, 16, &fgColor, &bgColor);

    fgColor.r = 200;
    fgColor.g = 200;
    fgColor.b = 80;
    bgColor.r = hme->screen->bgColorMenuBar.r;
    bgColor.g = hme->screen->bgColorMenuBar.g;
    bgColor.b = hme->screen->bgColorMenuBar.b;
    hme->fontMenusNormal = loadFont(FONT_PATH_MAC, 16, &fgColor, &bgColor);

    fgColor.r = hme->screen->bgColorMenuBar.r;
    fgColor.g = hme->screen->bgColorMenuBar.g;
    fgColor.b = hme->screen->bgColorMenuBar.b;
    bgColor.r = 200;
    bgColor.g = 200;
    bgColor.b = 80;
    hme->fontMenusSelected = loadFont(FONT_PATH_MAC, 16, &fgColor, &bgColor);
}

void freeFonts(HeightMapEditor *hme) {
    freeFont(hme->fontConsole);
    freeFont(hme->fontDialogsTitle);
    freeFont(hme->fontMenusNormal);
    freeFont(hme->fontMenusSelected);
    TTF_Quit();
}

TerrainVisualParams *loadTerrainParams(SDL_Rect *paramsRect) {
    alloc(terrainParams, TerrainVisualParams, 1);

    terrainParams->width = paramsRect->w;
    terrainParams->height = paramsRect->h;
    terrainParams->x = paramsRect->x;
    terrainParams->y = paramsRect->y;

    return terrainParams;
}
