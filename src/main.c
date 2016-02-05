#include "main.h"

HeightMapEditor *hme;
SDL_Window *window;
SDL_Renderer *renderer;

/*
1. Compose console line -
2. Add line to pointer list -
3. Lookup line (pointer)
4. Delete console pointers
5. Redo structure when console is resized
*/

typedef struct ConsoleLine {
    char *content;
    struct ConsoleLine *previous;
    struct ConsoleLine *next;
} ConsoleLine;

typedef struct {
    ConsoleLine *lines;
    ConsoleLine *lastLine;
} Console2;

int contador = 0;

void addLineToConsole(Console2 *console) {
    int lengthLine = 10; //TODO Hardcoded
    alloc(newConsoleLine, ConsoleLine, 1);
    allocExist(newConsoleLine->content, char, lengthLine);

    sprintf(newConsoleLine->content, "Line %d", contador++);

    if(console->lastLine != NULL) {
        console->lastLine->next = newConsoleLine;
        newConsoleLine->previous = console->lastLine;
    } else {
        console->lines = newConsoleLine;
    }

    console->lastLine = newConsoleLine;
}

Console2 *initConsole() {
    alloc(console, Console2, 1);
    addLineToConsole(console);
    return console;
}

void printLine(int width) {
    int i = 0;

    printf("+");
    for(i = 0; i < width; i++) printf("-");
    printf("+\n");
}

ConsoleLine *getLineNumber(Console2 *console, int lineNumber) {
    ConsoleLine *line = console->lines;
    int currentLine = 0;

    while(currentLine < lineNumber && line->next != NULL) {
        line = line->next;
        currentLine++;
    }

    return (currentLine == lineNumber) ? line : NULL;
}

void showWindow(Console2 *console, int lineStart, int numLines) {
    int width = 10; //TODO Hardcoded
    ConsoleLine *line = NULL;
    int i;

    printLine(width);

    for(i = lineStart; i < lineStart + numLines; i++) {
        line = getLineNumber(console, i);

        if(line != NULL) {
            printf("%s\n", line->content);
        } else {
            printf("\n");
        }
    }

    printLine(width);
}

int main(int argc, char* argv[]) {
    /*alloc(consoleWindow, char, 10 * 3);
    char *buffer = "line a\nline b\nline c a little bit longer\nline d\nline e";
    char *consoleLine = NULL;
    int remaining = 3;

    showWindow(buffer, 1, 3);
    showWindow(buffer, 2, 3);
    showWindow(buffer, 3, 3);*/
    Console2 *console = initConsole();
    addLineToConsole(console);
    addLineToConsole(console);

    showWindow(console, 0, 3);
    showWindow(console, 1, 3);
    showWindow(console, 2, 3);
    showWindow(console, 3, 3);

    return 0;

    SDL_Init(SDL_INIT_VIDEO);

    hme = loadHeightMapEditor(800, 600);
    programLoop(renderer);
    freeResources(hme);

    SDL_Quit();

    return 0;
}

/*int getLinePosition(char *buffer, int lineNumber) {
    int currentLine = 0;
    int length = strlen(buffer);
    int i;

    if(lineNumber == 0) return currentLine;

    for(i = 0; i < length; i++) {
        if(*(buffer + i) == '\n') currentLine++;
        if(currentLine == lineNumber) return i + 1;
    }

    return currentLine >= lineNumber ? currentLine : -1;
}

int getLengthLine(char *buffer, int bufferPos) {
    int i = 0;
    char currentChar = *(buffer + bufferPos);

    while(currentChar != '\n' && currentChar != '\0')
        currentChar = *(buffer + bufferPos + (i++));

    return i - 1;
}

char *getLineFromBuffer(int lineNumber, char *buffer) {
    int bufferPos = getLinePosition(buffer, lineNumber);
    int lengthLine = getLengthLine(buffer, bufferPos);

    alloc(bufferLine, char, lengthLine + 1);
    memcpy(bufferLine, buffer + bufferPos, lengthLine);

    return bufferLine;
}

void printConsoleLine2(char *consoleLine, int *remaining) {
    printf("|%s|\n", consoleLine);
    (*remaining)--;
}

void printConsoleLine3(char *consoleRow, char *stringOffset, int lengthRowConsole, int *remaining, bool trailingSpaces) {
    memcpy(consoleRow, stringOffset, lengthRowConsole);

    if(trailingSpaces) {
        memset(consoleRow + strlen(stringOffset), ' ', lengthRowConsole - strlen(stringOffset));
    }

    printConsoleLine2(consoleRow, remaining);
}

void printConsoleString(char *string, int lengthRowConsole, int *remaining) {
    alloc(consoleRow, char, lengthRowConsole + 1);
    int completeRows = strlen(string) / lengthRowConsole;
    int i;
    char *stringOffset = NULL;

    for(i = 0; i < completeRows && *remaining > 0; i++) {
        stringOffset = string + (i * lengthRowConsole);
        printConsoleLine3(consoleRow, stringOffset, lengthRowConsole, remaining, false);
    }

    if(*remaining > 0) {
        stringOffset = string + (i * lengthRowConsole);
        printConsoleLine3(consoleRow, stringOffset, lengthRowConsole, remaining, true);
    }
}*/

void programLoop(SDL_Renderer *renderer) {
    alloc(events, Events, 1);

    //processCommand("gterr width=200 height=100", hme->console);
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
    allocExist(params->coords, SDL_Rect, 1);
    memcpy(params->coords, paramsRect, sizeof(SDL_Rect));

    params->interLineSpace = 20;

    params->widthChars =params->coords->w / charWidth;
    params->heightChars = params->coords->h / params->interLineSpace - 1;

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
