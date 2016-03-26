#include "console_load.h"

Console *loadConsole() {
    alloc(console, Console, 1);

    console->visual = loadConsoleVisual();
    console->commands = loadConsoleCommands();

    console->maxLineLength = MAX_LINE_LENGTH;
    allocExist(console->currentLine, char, console->maxLineLength);

    return console;
}

ConsoleVisualParams *loadConsoleVisual() {
    alloc(params, ConsoleVisualParams, 1);

    params->interLineSpace = 20;
    params->padding = 4;
    params->pixelsFill = 5;

    params->widthCursor = 10;
    params->heightCursor = 15;
    params->showCursor = true;

    SDL_Color fgColor = {180, 180, 180};
    SDL_Color bgColor = {50, 50, 50};
    params->font = loadFont(FONT_PATH_MAC, 16, &fgColor, &bgColor);

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
    freeConsoleCommands(console->commands);
    freeConsoleVisual(console->visual);

    free(console->currentLine);
    free(console);
}

void freeConsoleVisual(ConsoleVisualParams *visual) {
    freeFont(visual->font);
    free(visual);
}

void freeConsoleCommands(Command *commands) {
    int i;

    for(i = 0; i < NUM_COMMANDS; i++) {
        free((commands + i)->params);
    }

    free(commands);
}

void consoleSetCoords(Console *console, SDL_Rect *paramsRect) {
    ConsoleVisualParams *params = console->visual;
    allocExist(params->coords, SDL_Rect, 1);
    memcpy(params->coords, paramsRect, sizeof(SDL_Rect));
}
