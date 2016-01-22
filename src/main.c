#include "main.h"

HeightMapEditor *hme;
SDL_Window *window;
SDL_Renderer *renderer;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    hme = loadHeightMapEditor(800, 600);

    //bool finish = false;
    Console *console = hme->console;
    Command *listCommands = loadCommands(console);

    printConsoleBanner(console);

    //while(!finish) {
        printPrompt(console);
        //readShellLine(console, stdin);
        //finish = processCommand(console->currentLine, console);
    //}

    programLoop(renderer);

    freeResources(hme);
    SDL_Quit();
    return 0;
}

void programLoop(SDL_Renderer *renderer) {
    bool finish = false;
    char *consoleBuffer = hme->console->buffer;

    while(!finish) {
        readEvents(hme->console, &finish);
        drawScreen(renderer, hme->terrain, hme->console, hme->consoleParams);
        SDL_Delay(500);
    }
}

HeightMapEditor *loadHeightMapEditor(int windowWidth, int windowHeight) {
    alloc(hme, HeightMapEditor, 1);

    hme->width = windowWidth;
    hme->height = windowHeight;
    hme->console = createConsole(1);
    hme->consoleParams = loadConsoleParams(hme->width, hme->height);

    /*heightMapEditor->dialogs = loadDialogs();
    //printDialogs(heightMapEditor->dialogs);*/

    hme->terrain = api_generateTerrain(300, 150);

    window = createWindow("Knight", hme->width, hme->height);
    renderer = createRenderer(window);

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
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_CloseFont(hme->consoleParams->font->type);
    api_freeTerrain(hme->terrain);
    //freeDialogs(heightMapEditor->dialogs);
}

ConsoleVisualParams *loadConsoleParams(int windowWidth, int windowHeight) {
    char *FONT_PATH_MAC = "/Library/Fonts/Courier New.ttf";
    char *FONT_PATH_LINUX = "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf";

    int consoleWidth = windowWidth;
    int yConsole = windowHeight / 2;
    int heightConsole = windowHeight / 2;
    int charWidth = 10;

    alloc(consoleParams, ConsoleVisualParams, 1);
    consoleParams->x = 0;
    consoleParams->y = yConsole;
    consoleParams->interLineSpace = 20;
    consoleParams->width = windowWidth / charWidth;
    consoleParams->height = heightConsole / consoleParams->interLineSpace;

    consoleParams->padding = 4;
    consoleParams->pixelsFill = 5;

    consoleParams->widthCursor = 10;
    consoleParams->heightCursor = 15;
    consoleParams->showCursor = true;

    consoleParams->font = initFont(FONT_PATH_MAC);

    return consoleParams;
}
