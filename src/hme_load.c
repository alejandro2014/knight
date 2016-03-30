#include "hme_load.h"

extern Events *events;

HeightMapEditor *loadHeightMapEditor() {
    alloc(hme, HeightMapEditor, 1);
    allocExist(hme->screen, Screen, 1);

    hme->screen->bgColorTerrain = (SDL_Color) {80, 40, 40};
    hme->screen->bgColorMenuBar = (SDL_Color) {40, 80, 40};

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

    hme->fontConsole = loadFont(FONT_PATH_MAC, 16, (SDL_Color) {180, 180, 180}, (SDL_Color) {50, 50, 50});
    hme->fontDialogsTitle = loadFont(FONT_PATH_MAC, 16, (SDL_Color) {200, 200, 200}, (SDL_Color) {0, 0, 100});
    hme->fontMenusNormal = loadFont(FONT_PATH_MAC, 16, (SDL_Color) {180, 180, 70}, hme->screen->bgColorMenuBar);
    hme->fontMenusSelected = loadFont(FONT_PATH_MAC, 16, hme->screen->bgColorMenuBar, (SDL_Color) {180, 180, 70});
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
