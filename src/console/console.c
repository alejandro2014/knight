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
    allocExist(console->buffer, char, sizeKb * 1024);
    allocExist(console->currentLine, char, 80);
    allocExist(console->commands, Command, NUM_COMMANDS);

    for(i = 0; i < NUM_COMMANDS; i++) {
        allocExist((console->commands + i)->params, Param, MAX_PARAMS);
    }

    loadCommands(console);

    return console;
}

void freeConsole(Console *console) {
    free(console->buffer);
    free(console);
}

Command *loadCommands(Console *console) {
    Command *command = NULL;

    // Non tested
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
    addCommandIntParams("risesel", (char *[]){"x1", "x2", "y1", "y2", "delta"}, 5, console);
    addCommandIntParams("riseterr", (char *[]){"delta"}, 1, console);
    addCommand("rotate90", console);
    addCommand("rotate180", console);
    addCommand("rotate270", console);
    addCommandIntParams("sethp", (char *[]){"x", "y", "height"}, 3, console);
    addCommandIntParams("sethsel", (char *[]){"x1", "y1", "x2", "y2", "height"}, 5, console);
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
    int endOffset = console->offset;
    int beginOffset = console->lastLineOffset;
    int length = endOffset - beginOffset;

    memcpy(console->currentLine, console->buffer + console->lastLineOffset, length - 1);
    *(console->currentLine + length) = '\0';
    console->lastLineOffset = console->offset;
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
        alloc(errorMessage, char, 100);
        sprintf(errorMessage, "Unknown command: '%s'", commandName);
        consoleAddStringLine(console, errorMessage);
        free(errorMessage);
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
            printf("Param not found [%s]\n", typedParam); //TODO How to write this to the console?
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
        if(*(paramString + i) == '=') {
            colonPos = i;
            break;
        }
    }

    if(colonPos > 0) {
        allocExist(*key, char, colonPos + 1);
        memcpy(*key, paramString, colonPos);

        allocExist(*value, char, length - colonPos + 1);
        memcpy(*value, paramString + i + 1, length - colonPos + 1);

        printf("[DEBUG] Parsed param (%s, %s)\n", *key, *value);
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
    alloc(infoMessage, char, LENGTH_MESSAGE);

    int i;
    for(i = 0; i < numStrings; i++) {
        allocExist(strParams[i], char, 100);
    }

    Terrain **terrain = &(console->terrain);
    Terrain *terrain1 = console->terrain;
    Command *command = console->currentCommand;

    if(!areParamsValid(command, intParams, strParams)) return;

    if(!strcmp("flipx", command->name))           terrain1 = api_rotate(terrain1, FLIP_XAXIS, infoMessage);
    else if(!strcmp("flipy", command->name))      terrain1 = api_rotate(terrain1, FLIP_YAXIS, infoMessage);
    //else if(!strcmp("flood", command->name))      infoMessage = api_floodArea(terrain, P0, P1, P2);
    else if(!strcmp("gterr", command->name))      terrain1 = api_generateTerrain(P0, P1, infoMessage);
    /*else if(!strcmp("help", command->name))       printCommands(console);
    else if(!strcmp("invheight", command->name))  infoMessage = api_invertHeight(terrain);
    else if(!strcmp("loadscr", command->name))    loadScript(console, *(strParams + 0));
    else if(!strcmp("merge", command->name))      api_MergeTerrains(NULL, NULL, P0, P1, P2);
    else if(!strcmp("randgterr", command->name))  console->terrain = api_generateRandomTerrain(P0, P1);
    else if(!strcmp("replace", command->name))    infoMessage = api_replace(terrain, P0, P1, P2, P3);*/
    else if(!strcmp("risesel", command->name))    api_riseSelection(terrain1, P0, P1, P2, P3, P4);
    else if(!strcmp("riseterr", command->name))   api_riseTerrain(terrain1, P0);
    else if(!strcmp("rotate90", command->name))   terrain1 = api_rotate(terrain1, ROTATE_90, infoMessage);
    else if(!strcmp("rotate180", command->name))  terrain1 = api_rotate(terrain1, ROTATE_180, infoMessage);
    else if(!strcmp("rotate270", command->name))  terrain1 = api_rotate(terrain1, ROTATE_270, infoMessage);
    else if(!strcmp("sethp", command->name))      api_setHeight(terrain1, P0, P1, P2);
    else if(!strcmp("sethsel", command->name))    api_setHeightSelection(terrain1, P0, P1, P2, P3, P4);
    else if(!strcmp("sethterr", command->name))   api_setHeightTerrain(terrain1, P0);
    else if(!strcmp("sinksel", command->name))    api_sinkSelection(terrain1, P0, P1, P2, P3, P4);
    else if(!strcmp("sinkterr", command->name))   api_sinkTerrain(terrain1, P0);
    /*else if(!strcmp("smoothsel", command->name))  infoMessage = api_smoothSelection(terrain, P0, P1, P2, P3);
    else if(!strcmp("smoothterr", command->name)) infoMessage = api_smoothTerrain(terrain);*/

    console->terrain = terrain1;
    deleteParamsValue(command);

    if(infoMessage != NULL) {
        consoleAddStringLine(console, infoMessage);
        free(infoMessage);
    }
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
    printf("[DEBUG] Getting param value int (%s, %d)\n", param->key, atoi(param->value));
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
    printf("[DEBUG] Getting param value string (%s, %s)\n", param->key, param->value);
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

void consoleAddChar(Console *console, char currentChar) {
    char *buffer = console->buffer;

    *(buffer + console->offset) = currentChar;
    console->offset++;
}

void consoleDeleteChar(Console *console) {
    char *buffer = console->buffer;
    if(!(*(buffer + console->offset - 2) == '>' &&
        *(buffer + console->offset - 1) == ' ')) {
        console->offset--;
        *(buffer + console->offset) = '\0';
    }
}

void consoleNewLine(Console *console) {
    consoleAddChar(console, '\n');

    console->currentLineNumber++;

    if(console->currentLineNumber > 14) {
        calculateWindowOffset(console);
    }
}

void consoleAddString(Console *console, char *string) {
    char *buffer = console->buffer;
    int length = strlen(string);

    memcpy(buffer + console->offset, string, length);
    console->offset += length;
}

void consoleAddStringLine(Console *console, char *string) {
    consoleAddString(console, string);
    consoleNewLine(console);
    console->lastLineOffset = console->offset;
}

void consoleResize(Console *console, int newRowsNum, int newColsNum) {

}

//TODO This function placed here seems to be a design error
void calculateWindowOffset(Console *console) {
    int position = console->windowOffset;

    while(*(console->buffer + position) != '\n') {
        position++;
    }

    console->windowOffset = position + 1;
}
