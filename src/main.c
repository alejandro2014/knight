#include "main.h"

HeightMapEditor *hme;
SDL_Window *window;
SDL_Renderer *renderer;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    hme = loadHeightMapEditor(800, 600);
    programLoop(renderer);
    freeResources(hme);

    SDL_Quit();

    return 0;
}

void programLoop(SDL_Renderer *renderer) {
    alloc(events, Events, 1);

    processCommand("gterr width=200 height=100", hme->console);
    //processCommand("sethterr height=200", hme->console);
    //processCommand("sethsel x1=10 y1=9 x2=80 y2=79 height=200", hme->console);
    //processCommand("risesel x1=10 y1=9 x2=80 y2=79 delta=200", hme->console);
    //processCommand("sinksel x1=10 y1=9 x2=80 y2=79 delta=200", hme->console);

    while(!events->finish) {
        readEvents(hme->console, events);

        if(events->consoleNewLine) {
            readShellLine(hme->console, NULL);
            events->finish = processCommand(hme->console->currentLine + 2, hme->console);
            memset(hme->console->currentLine, 0, 80);
            events->consoleNewLine = false;
        }

        if(events->printPrompt) {
            hme->consoleParams->printPrompt = true;
            events->printPrompt = false;
        }

        drawScreen(renderer, hme->console, hme->consoleParams, hme->terrainParams);
        SDL_Delay(100);
    }
}

HeightMapEditor *loadHeightMapEditor(int windowWidth, int windowHeight) {
    alloc(hme, HeightMapEditor, 1);

    hme->console = createConsole(1);

    hmeSetLayout(hme, windowWidth, windowHeight);

    /*heightMapEditor->dialogs = loadDialogs();
    printDialogs(heightMapEditor->dialogs);*/

    window = createWindow("Knight", hme->width, hme->height);
    renderer = createRenderer(window);

    return hme;
}

void hmeSetLayout(HeightMapEditor *hme, int width, int height) {
    hme->width = width;
    hme->height = height;

    SDL_Rect consoleParams;
    consoleParams.w = width;
    consoleParams.h = height / 2;
    consoleParams.x = 0;
    consoleParams.y = height / 2;

    hme->consoleParams = loadConsoleParams(&consoleParams);

    SDL_Rect terrainParams;
    terrainParams.w = width;
    terrainParams.h = height / 2;
    terrainParams.x = 0;
    terrainParams.y = 0;

    hme->terrainParams = loadTerrainParams(&terrainParams);
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
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_CloseFont(hme->consoleParams->font->type);
    api_freeTerrain(hme->terrain);
    //freeDialogs(heightMapEditor->dialogs);
}

ConsoleVisualParams *loadConsoleParams(SDL_Rect *paramsRect) {
    //TODO Hardcoded values
    char *FONT_PATH_MAC = "/Library/Fonts/Courier New.ttf";
    char *FONT_PATH_LINUX = "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf";
    int charWidth = 10;

    alloc(params, ConsoleVisualParams, 1);
    params->x = paramsRect->x;
    params->y = paramsRect->y;
    params->interLineSpace = 20;

    params->widthPixels = paramsRect->w;
    params->heightPixels = paramsRect->h;
    params->widthChars = paramsRect->w / charWidth;
    params->heightChars = paramsRect->h / params->interLineSpace;

    params->padding = 4;
    params->pixelsFill = 5;

    params->widthCursor = 10;
    params->heightCursor = 15;
    params->showCursor = true;

    params->font = initFont(FONT_PATH_MAC);

    return params;
}

TerrainVisualParams *loadTerrainParams(SDL_Rect *paramsRect) {
    alloc(terrainParams, TerrainVisualParams, 1);
    
    terrainParams->width = paramsRect->w;
    terrainParams->height = paramsRect->h;
    terrainParams->x = paramsRect->x;
    terrainParams->y = paramsRect->y;

    return terrainParams;
}
