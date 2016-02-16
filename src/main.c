#include "main.h"

extern Events *events;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    HeightMapEditor *hme = loadHeightMapEditor();
    programLoop(hme);
    freeResources(hme);

    SDL_Quit();

    return 0;
}

void programLoop(HeightMapEditor *hme) {
    SDL_Renderer *renderer = hme->screen->renderer;
    allocExist(events, Events, 1);
    bool printBanner = false;

    if(printBanner) {
        printConsoleBanner(hme->console);
    } else {
        printConsolePrompt(hme->console);
    }

    while(!events->finish) {
        readEvents(hme->console, events);

        if(events->consoleNewLine) {
            events->finish = processCommand(hme->console);
            memset(hme->console->currentLine, 0, hme->console->maxLineLength);
            hme->console->currentLineOffset = 0;
            events->consoleNewLine = false;
        }

        drawScreen(hme->screen, hme->console, hme->terrainParams);
        SDL_Delay(100);
    }
}

HeightMapEditor *loadHeightMapEditor() {
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

    return hme;
}

void hmeSetLayout(Screen *screen, Layout layout, Console *console) {
    int charWidth = 10; //TODO Hardcoded variables

    screen->width = 800;
    screen->height = 600;
    screen->menuHeight = 20;

    setWindowsLayout(screen, layout);

    consoleSetCoords(console, &(screen->consoleCoords));
    console->visual->widthChars = console->visual->coords->w / charWidth;
    console->visual->heightChars = console->visual->coords->h / console->visual->interLineSpace - 1;
    addLineToConsole(console);
}

void setWindowsLayout(Screen *screen, Layout layout) {
    int menuHeight = screen->menuHeight;
    int width = screen->width;
    int height = screen->height;

    SDL_Rect *menu = &(screen->menuBarCoords);
    SDL_Rect *console = &(screen->consoleCoords);
    SDL_Rect *terrain = &(screen->terrainCoords);

    setRect(menu, 0, 0, width, menuHeight);

    switch(layout) {
        case LAYOUT_ONLY_CONSOLE: break;
        case LAYOUT_ONLY_TERRAIN: break;
        case LAYOUT_VER_CONSOLE_TERRAIN: setRect(console, NORTHWEST, SOUTH); setRect(terrain, NORTH, SOUTHEAST); break;
        case LAYOUT_VER_TERRAIN_CONSOLE: setRect(terrain, NORTHWEST, SOUTH); setRect(console, NORTH, SOUTHEAST); break;
        case LAYOUT_HOR_CONSOLE_TERRAIN: setRect(console, NORTHWEST, EAST);  setRect(terrain, WEST, SOUTHEAST); break;
        case LAYOUT_HOR_TERRAIN_CONSOLE: setRect(terrain, NORTHWEST, EAST);  setRect(console, WEST, SOUTHEAST); break;
    }
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
