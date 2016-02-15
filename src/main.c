#include "main.h"

#define NORTHWEST 0,menuHeight
#define NORTH width/2,menuHeight
#define NORTHEAST width-1,menuHeight

#define WEST 0,(height-menuHeight)/2+menuHeight
#define CENTER width/2,(height-menuHeight)/2+menuHeight
#define EAST width-1,(height-menuHeight)/2+menuHeight

#define SOUTHWEST 0,height-1
#define SOUTH width/2,height-1
#define SOUTHEAST width-1,height-1

extern Events *events;

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
    bool printBanner = false;
    allocExist(events, Events, 1);

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

        drawScreen(renderer, hme->console, hme->terrainParams);
        SDL_Delay(100);
    }
}

HeightMapEditor *loadHeightMapEditor(int windowWidth, int windowHeight) {
    alloc(hme, HeightMapEditor, 1);

    hme->console = createConsole(1);

    hmeSetLayout(hme, windowWidth, windowHeight, LAYOUT_HOR_TERRAIN_CONSOLE);

    /*heightMapEditor->dialogs = loadDialogs();
    printDialogs(heightMapEditor->dialogs);*/

    window = createWindow("Knight", hme->width, hme->height);
    renderer = createRenderer(window);

    return hme;
}

void hmeSetLayout(HeightMapEditor *hme, int width, int height, Layout layout) {
    int charWidth = 10; //TODO Hardcoded

    hme->width = width;
    hme->height = height;

    SDL_Rect menuCoords;
    SDL_Rect consoleCoords;
    SDL_Rect terrainRect;

    setWindowsLayout(layout, &menuCoords, &consoleCoords, &terrainRect, hme);

    consoleSetCoords(hme->console, &consoleCoords);
    hme->console->visual->widthChars = hme->console->visual->coords->w / charWidth;
    hme->console->visual->heightChars = hme->console->visual->coords->h / hme->console->visual->interLineSpace - 1;
    addLineToConsole(hme->console);

    hme->terrainParams = loadTerrainParams(&terrainRect);
}

void setWindowsLayout(Layout layout, SDL_Rect *menuRect, SDL_Rect *consoleRect, SDL_Rect *terrainRect, HeightMapEditor *hme) {
    int menuHeight = 20; //TODO
    int width = hme->width;
    int height = hme->height;

    setRect(menuRect, 0, 0, width, menuHeight);

    switch(layout) {
        case LAYOUT_ONLY_CONSOLE:
            break;

        case LAYOUT_ONLY_TERRAIN:
            break;

        case LAYOUT_VER_CONSOLE_TERRAIN:
            setRect(consoleRect, NORTHWEST, SOUTH);
            setRect(terrainRect, NORTH, SOUTHEAST);
            break;

        case LAYOUT_VER_TERRAIN_CONSOLE:
            setRect(terrainRect, NORTHWEST, SOUTH);
            setRect(consoleRect, NORTH, SOUTHEAST);
            break;

        case LAYOUT_HOR_CONSOLE_TERRAIN:
            setRect(consoleRect, NORTHWEST, EAST);
            setRect(terrainRect, WEST, SOUTHEAST);
            break;

        case LAYOUT_HOR_TERRAIN_CONSOLE:
            setRect(terrainRect, NORTHWEST, EAST);
            setRect(consoleRect, WEST, SOUTHEAST);
            break;
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
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    api_freeTerrain(hme->terrain);
    //freeDialogs(heightMapEditor->dialogs);
}

TerrainVisualParams *loadTerrainParams(SDL_Rect *paramsRect) {
    alloc(terrainParams, TerrainVisualParams, 1);

    terrainParams->width = paramsRect->w;
    terrainParams->height = paramsRect->h;
    terrainParams->x = paramsRect->x;
    terrainParams->y = paramsRect->y;

    return terrainParams;
}
