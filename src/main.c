#include "main.h"
#include "hme_load.h"

extern Dialog *registeredDialogs;
extern Terrain *currentTerrain;
extern Events *events;

int calculateCheckDigit(char *code) {
    int currentDigit, currentWeight;
    int subtotal, checkSum = 0;
    int i;

    for(i = 0; i < 12; i++) {
        currentDigit = *(code + i) - 0x30;
        currentWeight = (i % 2 == 0) ? 1 : 3;
        subtotal = currentDigit * currentWeight;
        checkSum += subtotal;
    }

    return 10 - (checkSum % 10);
}

int main(int argc, char* argv[]) {
    HeightMapEditor *hme = loadHeightMapEditor();
    programLoop(hme);
    freeHeightMapEditor(hme);
    /*char *code = "978841591557";
    int checkDigit = calculateCheckDigit(code);
    printf("%s-%d\n", code, checkDigit);

    code = "978848298586";
    checkDigit = calculateCheckDigit(code);
    printf("%s-%d\n", code, checkDigit);

    code = "978842840651";
    checkDigit = calculateCheckDigit(code);
    printf("%s-%d\n", code, checkDigit);

    code = "303005307475";
    checkDigit = calculateCheckDigit(code);
    printf("%s-%d\n", code, checkDigit);*/

    return 0;
}

void programLoop(HeightMapEditor *hme) {
    initConsole(hme->console);

    while(!events->finish) {
        readEvents(hme->console, events);

        if(events->consoleNewLine) {
            events->finish = processCommand(hme->console);
            memset(hme->console->currentLine, 0, hme->console->maxLineLength);
            hme->console->currentLineOffset = 0;
            events->consoleNewLine = false;
        }

        drawScreen(hme);
        SDL_Delay(100);
    }
}

void drawScreen(HeightMapEditor *hme) {
    SDL_Renderer *renderer = hme->screen->renderer;

    drawTerrain(hme->screen, currentTerrain, hme->terrainParams);
    drawConsole(renderer, hme->console);

    clearSubScreen(renderer, &(hme->screen->menuBarCoords), &(hme->screen->bgColorMenuBar));
    drawMenu(hme->menuBar, hme->screen);

    //drawDialogWindow(renderer, registeredDialogs);

    SDL_RenderPresent(renderer);
}

void hmeSetLayout(Screen *screen, Layout layout, Console *console) {
    int charWidth = 10; //TODO Hardcoded variables

    screen->width = 1024;
    screen->height = 768;
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
