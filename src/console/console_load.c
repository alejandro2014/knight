#include "console_load.h"

Console *createConsole(int sizeKb) {
    int lengthLine = 80; //TODO Hardcoded
    int i;

    alloc(console, Console, 1);
    allocExist(console->buffer, char, sizeKb * 1024);
    allocExist(console->currentLine, char, lengthLine);
    allocExist(console->commands, Command, NUM_COMMANDS);

    allocExist(console->visual, ConsoleVisualParams, 1);
    addLineToConsole(console);

    for(i = 0; i < NUM_COMMANDS; i++) {
        allocExist((console->commands + i)->params, Param, MAX_PARAMS);
    }

    loadCommands(console);

    return console;
}

//TODO It doesn't free all the memory
void freeConsole(Console *console) {
    free(console->visual);
    free(console->buffer);
    free(console);
}

Command *loadCommands(Console *console) {
    Command *command = NULL;

    addCommand("flipx", console);
    addCommand("flipy", console);
    addCommandIntParams("flood", (char *[]){"x", "y", "height"}, 3, console);
    addCommandIntParams("gterr", (char *[]){"width", "height"}, 2, console);
    addCommand("help", console);
    addCommand("invheight", console);
    addCommandStrParams("loadscr", (char *[]){"path"}, 1, console);
    addCommandIntParams("merge", (char *[]){"x", "y", "op"}, 3, console);
    addCommandIntParams("randgterr", (char *[]){"width", "height"}, 2, console);
    addCommandIntParams("replace", (char *[]){"mode", "x", "y", "delta"}, 4, console);
    addCommandIntParams("risesel", (char *[]){"x1", "y1", "x2", "y2", "delta"}, 5, console);
    addCommandIntParams("riseterr", (char *[]){"delta"}, 1, console);
    addCommand("rotate90", console);
    addCommand("rotate180", console);
    addCommand("rotate270", console);
    addCommandIntParams("sethp", (char *[]){"x", "y", "height"}, 3, console);
    addCommandIntParams("sethsel", (char *[]){"x1", "y1", "x2", "y2", "height"}, 5, console);
    addCommandIntParams("sethterr", (char *[]){"height"}, 1, console);
    addCommandIntParams("sinksel", (char *[]){"x1", "y1", "x2", "y2", "delta"}, 5, console);
    addCommandIntParams("sinkterr", (char *[]){"delta"}, 1, console);
    addCommandIntParams("smoothsel", (char *[]){"x1", "x2", "y1", "y2"}, 4, console);
    addCommand("smoothterr", console);

    return console->commands;
}

void addCommandIntParams(char *commandName, char *params[], int numParams, Console *console) {
    addCommand(commandName, console);

    int i;
    for(i = 0; i < numParams; i++) {
        addParam(params[i], commandName, INT, console);
    }
}

void addCommandStrParams(char *commandName, char *params[], int numParams, Console *console) {
    addCommand(commandName, console);

    int i;
    for(i = 0; i < numParams; i++) {
        addParam(params[i], commandName, STRING, console);
    }
}

void addCommand(char *commandName, Console *console) {
    int positionCommand = console->numCommands;
    Command *command = console->commands + positionCommand;
    command->name = commandName;
    console->numCommands++;
}

void addParam(char *paramName, char *commandName, ParamType type, Console *console) {
    Command *command = lookupCommand(commandName, console);
    int positionParam = command->numParams;
    Param *param = command->params + positionParam;
    param->key = paramName;
    param->type = type;
    command->numParams++;
}
