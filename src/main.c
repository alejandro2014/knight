#include "main.h"
#include "hme_load.h"

extern Terrain *currentTerrain;
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

        drawScreen(hme);

        SDL_Delay(100);
    }
}

void drawScreen(HeightMapEditor *hme) {
    SDL_Renderer *renderer = hme->screen->renderer;

    drawMenuBar(hme->menuBar, hme->screen);
    drawTerrain(hme->screen, currentTerrain, hme->terrainParams);
    drawConsole(renderer, hme->console);
    SDL_RenderPresent(renderer);
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
