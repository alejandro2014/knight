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

    hmeSetLayout(hme, windowWidth, windowHeight, LAYOUT_VER_TERRAIN_CONSOLE);

    /*heightMapEditor->dialogs = loadDialogs();
    printDialogs(heightMapEditor->dialogs);*/

    window = createWindow("Knight", hme->width, hme->height);
    renderer = createRenderer(window);

    return hme;
}

void hmeSetLayout(HeightMapEditor *hme, int width, int height, Layout layout) {
    hme->width = width;
    hme->height = height;

    SDL_Rect consoleRect;
    SDL_Rect terrainRect;

    setWindowsLayout(layout, &consoleRect, &terrainRect, hme);

    hme->consoleParams = loadConsoleParams(&consoleRect);
    hme->terrainParams = loadTerrainParams(&terrainRect);
}

void setWindowsLayout(Layout layout, SDL_Rect *consoleRect, SDL_Rect *terrainRect, HeightMapEditor *hme) {
    int width = hme->width;
    int height = hme->height;

    switch(layout) {
        case LAYOUT_ONLY_CONSOLE:
            break;

        case LAYOUT_ONLY_TERRAIN:
            break;

        case LAYOUT_VER_CONSOLE_TERRAIN:
            setRect(consoleRect, 0, 0, (width/2), height);
            setRect(terrainRect, (width/2) + 1, 0, (width/2) - 1, height - 1);
            break;

        case LAYOUT_VER_TERRAIN_CONSOLE:
            setRect(terrainRect, 0, 0, (width/2), height);
            setRect(consoleRect, (width/2), 0, (width/2), height);
            break;

        case LAYOUT_HOR_CONSOLE_TERRAIN:
            setRect(consoleRect, 0, 0, width, (height/2));
            setRect(terrainRect, 0, (height/2), width, height);
            break;

        case LAYOUT_HOR_TERRAIN_CONSOLE:
            setRect(terrainRect, 0, 0, width, (height/2));
            setRect(consoleRect, 0, (height/2), width, height);
            break;
    }
}

void setRect(SDL_Rect *rect, int x, int y, int w, int h) {
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
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

    params->widthChars =params->widthPixels / charWidth;
    params->heightChars = params->heightPixels / params->interLineSpace - 1;

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
