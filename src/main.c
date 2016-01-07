#include "main.h"

HeightMapEditor *hme;

int main(int argc, char* argv[]) {
    HeightMapEditor *hme = loadHeightMapEditor();
    //testVideo();

    bool finish = false;
    Console *console = hme->console;
    Command *listCommands = loadCommands(console);

    printConsoleBanner(console);

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

    while(!finish) {
        printPrompt();
        readShellLine(console, stdin);
        finish = processCommand(console->currentLine, console);
    }

    freeConsole(console);

    return 0;
}

HeightMapEditor *loadHeightMapEditor() {
    alloc(hme, HeightMapEditor, 1);

    hme->console = createConsole(1);
    return hme;
    /*int width = 100;
    int height = 100;

    heightMapEditor->dialogs = loadDialogs();
    //printDialogs(heightMapEditor->dialogs);

    heightMapEditor->terrain = api_generateTerrain(heightMapEditor->horSize, heightMapEditor->verSize);

    *window = SDL_CreateWindow("HME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);

    if (*window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return -1;
    }

    *renderer = SDL_CreateRenderer(*window, -1, 0);

    if(*renderer == NULL) {
        printf("Could not create renderer: %s\n", SDL_GetError());
        return -1;
    }

    TTF_Init();
    *font = TTF_OpenFont(FONT_PATH_LINUX, 12);

    if(*font == NULL) {
        printf("Could not load the font\n");
        return -1;
    }*/

    return 0;
}

void freeResources(HeightMapEditor *hme) {
    freeConsole(hme->console);
    /*SDL_DestroyRenderer(heightMapEditor->renderer);
    SDL_DestroyWindow(heightMapEditor->window);
    TTF_CloseFont(heightMapEditor->font);
    freeDialogs(heightMapEditor->dialogs);
    api_freeTerrain(heightMapEditor->terrain);*/

}
