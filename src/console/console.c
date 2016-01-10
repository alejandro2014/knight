#include "console.h"
#include "print.h"

#include "../api/api.h"
#include "../api/hme_lowlevel.h"
#include "../api/generate_terrain.h"
#include "../api/flood.h"
#include "../api/replace.h"

#include "../global.h"

Console *createConsole(int sizeKb) {
    int i;

    alloc(console, Console, 1);
    allocExist(console->text, char, sizeKb * 1024);
    allocExist(console->currentLine, char, LINE_LENGTH);
    allocExist(console->commands, Command, NUM_COMMANDS);
    console->sizeLine = LINE_LENGTH;

    for(i = 0; i < NUM_COMMANDS; i++) {
        allocExist((console->commands + i)->params, Param, MAX_PARAMS);
    }

    return console;
}

void freeConsole(Console *console) {
    free(console->text);
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
    addCommand("prterr", console);
    addCommandIntParams("randgterr", (char *[]){"width", "height"}, 2, console);
    addCommandIntParams("replace", (char *[]){"mode", "x", "y", "delta"}, 4, console);
    addCommandIntParams("risesel", (char *[]){"x1", "x2", "y1", "y2", "delta"}, 5, console);
    addCommandIntParams("riseterr", (char *[]){"delta"}, 1, console);
    addCommand("rotate90", console);
    addCommand("rotate180", console);
    addCommand("rotate270", console);
    addCommandIntParams("sethp", (char *[]){"x", "y", "height"}, 3, console);
    addCommandIntParams("sethsel", (char *[]){"x1", "x2", "y1", "y2", "delta"}, 5, console);
    addCommandIntParams("sethterr", (char *[]){"height"}, 1, console);
    addCommandIntParams("sinksel", (char *[]){"x1", "x2", "y1", "y2", "delta"}, 5, console);
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

void readShellLine(Console *console, FILE *inputStream) {
    size_t sizeLineRead = getline(&console->currentLine, &console->sizeLine, inputStream);
    *(console->currentLine + sizeLineRead - 1) = '\0';
}

bool processCommand(char *textCommand, Console *console) {
    Command *command = NULL;
    bool finish = false;

    if(strcmp(textCommand, "exit")) {
        command = parseCommand(textCommand, console);

        if(command) {
            console->currentCommand = command;
            executeCommand(console);
        }
    } else {
        finish = true;
        printf("Bye\n");
    }

    return finish;
}

Command *parseCommand(char *strCommand, Console *console) {
    char stringCommand[100];
    int length = strlen(strCommand);

    if(length == 0) return NULL;

    memcpy(stringCommand, strCommand, length);
    stringCommand[length] = '\0';

    char *commandName = strtok(stringCommand, " ");
    Command *command = lookupCommand(commandName, console);

    if(!command) {
        printf("Unknown command: '%s'\n", commandName);
        return NULL;
    }

    if(getCommandParams(command)) {
        return command;
    }

    return NULL;
}

bool getCommandParams(Command *command) {
    char *key = NULL;
    char *value = NULL;
    Param *param = NULL;
    char *typedParam = strtok(NULL, " ");
    bool execute = true;

    while(typedParam) {
        parseParam(typedParam, &key, &value);
        param = lookupParam(key, command);

        if(param) {
            param->value = value;
        } else {
            printf("Param not found [%s]\n", typedParam);
            execute = false;
            break;
        }

        typedParam = strtok(NULL, " ");
    }

    return execute;
}

void parseParam(char *paramString, char **key, char **value) {
    int length = strlen(paramString);
    int i;
    int colonPos = -1;

    for(i = 0; i < length; i++) {
        if(*(paramString + i) == ':') {
            colonPos = i;
            break;
        }
    }

    if(colonPos > 0) {
        allocExist(*key, char, colonPos + 1);
        memcpy(*key, paramString, colonPos);

        allocExist(*value, char, length - colonPos + 1);
        memcpy(*value, paramString + i + 1, length - colonPos + 1);
    }
}

Command *lookupCommand(char *commandName, Console *console) {
    Command *currentCommand = NULL;
    int i;

    for(i = 0; i < console->numCommands; i++) {
        currentCommand = console->commands + i;

        if(!strcmp(currentCommand->name, commandName)) {
            return currentCommand;
        }
    }

    return NULL;
}

Param *lookupParam(char *paramName, Command *command) {
    Param *currentParam = NULL;
    int i;

    for(i = 0; i < command->numParams; i++) {
        currentParam = command->params + i;

        if(!strcmp(paramName, currentParam->key)) {
            return currentParam;
        }
    }

    return NULL;
}

/**
This method uses the macros P0, P1, P... to access the parameters array (params)
*/
void executeCommand(Console *console) {
    int numStrings = 5;
    alloc(intParams, int, 5);
    alloc(strParams, char *, numStrings);

    int i;
    for(i = 0; i < numStrings; i++) {
        allocExist(strParams[i], char, 100);
    }

    Terrain *terrain = console->terrain;
    Command *command = console->currentCommand;

    if(!areParamsValid(command, intParams, strParams)) return;

    if(!strcmp("flipx", command->name))           console->terrain = api_rotate(FLIP_XAXIS, terrain);
    else if(!strcmp("flipy", command->name))      console->terrain = api_rotate(FLIP_YAXIS, terrain);
    else if(!strcmp("flood", command->name))      api_floodArea(terrain, P0, P1, P2);
    else if(!strcmp("gterr", command->name))      console->terrain = api_generateTerrain(P0, P1);
    else if(!strcmp("help", command->name))       printCommands(console);
    else if(!strcmp("invheight", command->name))  api_invertHeight(terrain);
    else if(!strcmp("loadscr", command->name))    loadScript(console, *(strParams + 0));
    else if(!strcmp("merge", command->name))      api_MergeTerrains(NULL, NULL, P0, P1, P2);
    else if(!strcmp("prterr", command->name))     printTerrain(terrain);
    else if(!strcmp("randgterr", command->name))  console->terrain = api_generateRandomTerrain(P0, P1);
    else if(!strcmp("replace", command->name))    api_replace(terrain, P0, P1, P2, P3);
    else if(!strcmp("risesel", command->name))    api_riseSelection(terrain, P0, P1, P2, P3, P4);
    else if(!strcmp("riseterr", command->name))   api_riseTerrain(terrain, P0);
    else if(!strcmp("rotate90", command->name))   console->terrain = api_rotate(ROTATE_90, terrain);
    else if(!strcmp("rotate180", command->name))  console->terrain = api_rotate(ROTATE_180, terrain);
    else if(!strcmp("rotate270", command->name))  console->terrain = api_rotate(ROTATE_270, terrain);
    else if(!strcmp("sethp", command->name))      api_setHeight(terrain, P0, P1, P2);
    else if(!strcmp("sethsel", command->name))    api_setHeightSelection(terrain, P0, P1, P2, P3, P4);
    else if(!strcmp("sethterr", command->name))   api_setHeightTerrain(terrain, P0);
    else if(!strcmp("sinksel", command->name))    api_sinkSelection(terrain, P0, P1, P2, P3, P4);
    else if(!strcmp("sinkterr", command->name))   api_sinkTerrain(terrain, P0);
    else if(!strcmp("smoothsel", command->name))  api_smoothSelection(terrain, P0, P1, P2, P3);
    else if(!strcmp("smoothterr", command->name)) api_smoothTerrain(terrain);

    deleteParamsValue(command);
}

bool areParamsValid(Command *command, int *intParams, char **strParams) {
    if(command->numParams == 0) return true;

    int currentIntParam = 0;
    int currentStrParam = 0;
    bool validParams = false;
    Param *currentParam = NULL;

    int i;
    for(i = 0; i < command->numParams; i++) {
        currentParam = command->params + i;

        switch(currentParam->type) {
            case INT:
                *(intParams + currentIntParam) = getParamValueInt(currentParam->key, command, &validParams);
                currentIntParam++;
                break;
            case STRING:
                *(strParams + currentStrParam) = getParamValueStr(currentParam->key, command, &validParams);
                currentStrParam++;
                break;
        }


        if(!validParams) break;
    }

    return validParams;
}

int getParamValueInt(char *paramName, Command *command, bool *validParam) {
    Param *param = lookupParam(paramName, command);

    if(!param->value) {
        printf("[ERROR] The '%s' parameter is not present\n", paramName);
        *validParam = false;
        return -1;
    }

    *validParam = true;
    return atoi(param->value);
}

char *getParamValueStr(char *paramName, Command *command, bool *validParam) {
    Param *param = lookupParam(paramName, command);

    if(!param->value) {
        printf("[ERROR] The '%s' parameter is not present\n", paramName);
        *validParam = false;
        return NULL;
    }

    *validParam = true;
    return param->value;
}

void deleteParamsValue(Command *command) {
    int i;

    for(i = 0; i < MAX_PARAMS; i++) {
        (command->params + i)->value = NULL;
    }
}

void loadScript(Console *console, char *path) {
    FILE *script = fopen(path, "r");

    if(script == NULL) {
        printf("The script with path %s couldn't be loaded: file doesn't exist\n", path);
        return;
    }

    while(!feof(script)) {
        readShellLine(console, script);
        if(*(console->currentLine + 0) != '#' && strlen(console->currentLine) > 0) {
            printf("%s\n", console->currentLine);
            processCommand(console->currentLine, console);
        }
    }

    fclose(script);
}
