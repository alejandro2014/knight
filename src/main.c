#include <SDL.h>
#include "main.h"

HeightMapEditor *hme;
SDL_Window *window;
SDL_Renderer *renderer;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    hme = loadHeightMapEditor(640, 480);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_RenderClear(renderer);

    SDL_Rect r;
    r.x = 50;
    r.y = 50;
    r.w = 50;
    r.h = 50;

    SDL_RenderFillRect(renderer, &r);

    SDL_RenderPresent(renderer);
    /*bool finish = false;
    Console *console = hme->console;
    Command *listCommands = loadCommands(console);

    printConsoleBanner(console);

    while(!finish) {
        printPrompt();
        readShellLine(console, stdin);
        finish = processCommand(console->currentLine, console);
    }

    freeConsole(console);*/

    SDL_Delay(5000);

    freeResources(hme);

    SDL_Quit();
    return 0;
}

HeightMapEditor *loadHeightMapEditor(int windowWidth, int windowHeight) {
    alloc(hme, HeightMapEditor, 1);

    hme->console = createConsole(1);

    /*heightMapEditor->dialogs = loadDialogs();
    //printDialogs(heightMapEditor->dialogs);

    heightMapEditor->terrain = api_generateTerrain(heightMapEditor->horSize, heightMapEditor->verSize);*/

    window = createWindow("Knight", 640, 480);

    renderer = createRenderer(window);

    /*TTF_Init();
    *font = TTF_OpenFont(FONT_PATH_LINUX, 12);

    if(*font == NULL) {
        printf("Could not load the font\n");
        return -1;
    }*/

    return hme;
}

SDL_Window *createWindow(char *title, int width, int height) {
    SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE);

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

    /*TTF_CloseFont(heightMapEditor->font);
    freeDialogs(heightMapEditor->dialogs);
    api_freeTerrain(heightMapEditor->terrain);*/

}

/*processCommand("gterr width:5 height:5", console);

processCommand("sethterr height:5", console);
processCommand("sethp x:1 y:1 height:3", console);
processCommand("sethp x:2 y:1 height:3", console);
processCommand("sethp x:3 y:1 height:3", console);

processCommand("sethp x:1 y:2 height:3", console);
processCommand("sethp x:2 y:2 height:1", console);
//processCommand("sethp x:3 y:2 height:3", console);

processCommand("sethp x:1 y:3 height:3", console);
processCommand("sethp x:2 y:3 height:3", console);
processCommand("sethp x:3 y:3 height:3", console);
processCommand("prterr", console);

processCommand("sethp x:2 y:2 height:4", console);
processCommand("prterr", console);

processCommand("flood x:2 y:2", console);
processCommand("prterr", console);*/
