#include "console_load.h"

Console *loadConsole(Font *consoleFont) {
    alloc(console, Console, 1);

    console->visual = loadConsoleVisual(consoleFont);
    console->commands = loadConsoleCommands();

    console->maxLineLength = MAX_LINE_LENGTH;
    allocExist(console->currentLine, char, console->maxLineLength);

    return console;
}

ConsoleVisualParams *loadConsoleVisual(Font *consoleFont) {
    alloc(params, ConsoleVisualParams, 1);

    params->interLineSpace = 20;
    params->padding = 4;
    params->pixelsFill = 5;

    params->widthCursor = 10;
    params->heightCursor = 15;
    params->showCursor = true;

    params->font = consoleFont;

    params->currentLineNumber = -1;

    return params;
}

Command *loadConsoleCommands() {
    int i;

    alloc(commands, Command, NUM_COMMANDS);

    for(i = 0; i < NUM_COMMANDS; i++) {
        allocExist((commands + i)->params, Param, MAX_PARAMS);
    }

    return commands;
}

void freeConsole(Console *console) {
    if(!console) return;

    freeConsoleCommands(console->commands);
    freeConsoleVisual(console->visual);

    free(console->currentLine);
    free(console);
}

void freeConsoleVisual(ConsoleVisualParams *visual) {
    if(!visual) return;

    freeConsoleLines(visual);

    if(visual->coords) {
        free(visual->coords);
    }

    free(visual);
}

void freeConsoleLines(ConsoleVisualParams *visual) {
    if(!visual) return;

    ConsoleLine *line = visual->lines;
    ConsoleLine *nextLine = line->next;

    while(nextLine) {
        free(line->content);
        free(line);
        line = nextLine;
        nextLine = line->next;
    }

    free(line->content);
    free(line);
}

void freeConsoleCommands(Command *commands) {
    if(!commands) return;

    int i;

    for(i = 0; i < NUM_COMMANDS; i++) {
        free((commands + i)->params);
    }

    free(commands);
}

void consoleSetCoords(Console *console, SDL_Rect *paramsRect) {
    ConsoleVisualParams *visual = console->visual;
    allocExist(visual->coords, SDL_Rect, 1);
    memcpy(visual->coords, paramsRect, sizeof(SDL_Rect));
}

void initConsole(Console *console) {
    bool printBanner = false;

    if(printBanner) {
        printConsoleBanner(console);
    } else {
        printConsolePrompt(console);
    }
}
