#include "hme_load.h"

extern Events *events;

HeightMapEditor *loadHeightMapEditor() {
    SDL_Init(SDL_INIT_VIDEO);

    alloc(hme, HeightMapEditor, 1);
    allocExist(hme->screen, Screen, 1);
    allocExist(events, Events, 1);
    Screen *screen = hme->screen;

    loadFonts(hme);

    hme->console = loadConsole(hme->fontConsole);
    addCommands(hme->console);

    hmeSetLayout(screen, LAYOUT_HOR_TERRAIN_CONSOLE, hme->console);
    initScreen(screen);

    hme->terrainParams = loadTerrainParams(&(screen->terrainCoords));
    loadDialogs(hme->fontDialogsTitle);
    hme->menuBar = loadMenu(hme->fontMenusNormal, hme->fontMenusSelected);

    return hme;
}

void initScreen(Screen *screen) {
    screen->window = createWindow("Knight", screen->width, screen->height);
    screen->renderer = createRenderer(screen->window);
    screen->bgColorTerrain = (SDL_Color) {80, 40, 40};
    screen->bgColorMenuBar = (SDL_Color) {40, 80, 40};
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

void freeHeightMapEditor(HeightMapEditor *hme) {
    freeFonts(hme);

    freeConsole(hme->console);
    freeDialogs();

    SDL_DestroyRenderer(hme->screen->renderer);
    SDL_DestroyWindow(hme->screen->window);

    free(hme->terrainParams);
    //api_freeTerrain(hme->terrain);
    free(hme->screen);
    free(hme);
    free(events);

    SDL_Quit();
}

void loadFonts(HeightMapEditor *hme) {
    TTF_Init();

    hme->fontConsole = loadFont(FONT_PATH_MAC, 16, (SDL_Color) {180, 180, 180}, (SDL_Color) {50, 50, 50});
    hme->fontDialogsTitle = loadFont(FONT_PATH_MAC, 16, (SDL_Color) {200, 200, 200}, (SDL_Color) {0, 0, 100});
    hme->fontMenusNormal = loadFont(FONT_PATH_MAC, 16, (SDL_Color) {180, 180, 70}, (SDL_Color) {40, 80, 40});
    hme->fontMenusSelected = loadFont(FONT_PATH_MAC, 16, (SDL_Color) {40, 80, 40}, (SDL_Color) {180, 180, 70});
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
