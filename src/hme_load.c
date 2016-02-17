#include "hme_load.h"

HeightMapEditor *loadHeightMapEditor() {
    TTF_Init();

    alloc(hme, HeightMapEditor, 1);

    hme->console = createConsole(1);

    allocExist(hme->screen, Screen, 1);
    hmeSetLayout(hme->screen, LAYOUT_HOR_TERRAIN_CONSOLE, hme->console);

    hme->terrainParams = loadTerrainParams(&(hme->screen->terrainCoords));
    /*heightMapEditor->dialogs = loadDialogs();
    printDialogs(heightMapEditor->dialogs);*/

    hme->screen->window = createWindow("Knight", hme->screen->width, hme->screen->height);
    hme->screen->renderer = createRenderer(hme->screen->window);

    hme->screen->bgColorTerrain.r = 80;
    hme->screen->bgColorTerrain.g = 40;
    hme->screen->bgColorTerrain.b = 40;

    hme->screen->bgColorMenuBar.r = 40;
    hme->screen->bgColorMenuBar.g = 80;
    hme->screen->bgColorMenuBar.b = 40;

    hme->menuBar = loadMenuBar(&(hme->screen->bgColorMenuBar));

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
    TTF_CloseFont(hme->console->visual->font->type);
    freeConsole(hme->console);

    SDL_DestroyRenderer(hme->screen->renderer);
    SDL_DestroyWindow(hme->screen->window);
    api_freeTerrain(hme->terrain);
    //freeDialogs(heightMapEditor->dialogs);
    free(hme);
}

TerrainVisualParams *loadTerrainParams(SDL_Rect *paramsRect) {
    alloc(terrainParams, TerrainVisualParams, 1);

    terrainParams->width = paramsRect->w;
    terrainParams->height = paramsRect->h;
    terrainParams->x = paramsRect->x;
    terrainParams->y = paramsRect->y;

    return terrainParams;
}
