#include "hme_load.h"

extern Events *events;

HeightMapEditor *loadHeightMapEditor() {
    TTF_Init();

    alloc(hme, HeightMapEditor, 1);

    hme->console = loadConsole();
    addCommands(hme->console);

    allocExist(hme->screen, Screen, 1);
    hmeSetLayout(hme->screen, LAYOUT_HOR_TERRAIN_CONSOLE, hme->console);

    hme->terrainParams = loadTerrainParams(&(hme->screen->terrainCoords));
    hme->dialogs = loadDialogs();

    hme->screen->window = createWindow("Knight", hme->screen->width, hme->screen->height);
    hme->screen->renderer = createRenderer(hme->screen->window);

    hme->screen->bgColorTerrain.r = 80;
    hme->screen->bgColorTerrain.g = 40;
    hme->screen->bgColorTerrain.b = 40;

    hme->screen->bgColorMenuBar.r = 40;
    hme->screen->bgColorMenuBar.g = 80;
    hme->screen->bgColorMenuBar.b = 40;

    hme->menuBar = loadMenu(&(hme->screen->bgColorMenuBar));
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
    freeConsole(hme->console);

    TTF_Quit();

    SDL_DestroyRenderer(hme->screen->renderer);
    SDL_DestroyWindow(hme->screen->window);

    free(hme->terrainParams);
    //api_freeTerrain(hme->terrain);
    //freeDialogs(hme->dialogs);
    free(hme->screen);
    free(hme);
    free(events);
}

TerrainVisualParams *loadTerrainParams(SDL_Rect *paramsRect) {
    alloc(terrainParams, TerrainVisualParams, 1);

    terrainParams->width = paramsRect->w;
    terrainParams->height = paramsRect->h;
    terrainParams->x = paramsRect->x;
    terrainParams->y = paramsRect->y;

    return terrainParams;
}
