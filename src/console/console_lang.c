#include "console_lang.h"

void readShellLine(Console *console, FILE *inputStream) {
    int endOffset = console->offset;
    int beginOffset = console->visual->lineOffset;
    int length = endOffset - beginOffset;

    memcpy(console->currentLine, console->buffer + console->visual->lineOffset, length - 1);
    *(console->currentLine + length) = '\0';
    console->visual->lineOffset = console->offset;
}

// Returns whether we need to finish
bool processCommand(char *textCommand, Console *console) {
    if(!strcmp(textCommand, "exit")) return true;

    Command *command = parseCommand(textCommand, console);

    if(command) {
        console->currentCommand = command;
        executeCommand(console);
    }

    return false;
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
        consoleAddStringLine(console, errorMessage, true);
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

    Terrain *terrain = console->terrain;
    Command *command = console->currentCommand;

    if(!areParamsValid(command, intParams, strParams, infoMessage)) {
        printInfoMessage(infoMessage, console);
        return;
    }

    if(!strcmp("flipx", command->name))           terrain = api_rotate(terrain, FLIP_XAXIS, infoMessage);
    else if(!strcmp("flipy", command->name))      terrain = api_rotate(terrain, FLIP_YAXIS, infoMessage);
    else if(!strcmp("gterr", command->name))      terrain = api_generateTerrain(P0, P1, infoMessage);
    else if(!strcmp("invheight", command->name))  api_invertHeight(terrain);
    else if(!strcmp("randgterr", command->name))  terrain = api_generateRandomTerrain(P0, P1, infoMessage);
    else if(!strcmp("risesel", command->name))    api_riseSelection(terrain, P0, P1, P2, P3, P4);
    else if(!strcmp("riseterr", command->name))   api_riseTerrain(terrain, P0);
    else if(!strcmp("rotate90", command->name))   terrain = api_rotate(terrain, ROTATE_90, infoMessage);
    else if(!strcmp("rotate180", command->name))  terrain = api_rotate(terrain, ROTATE_180, infoMessage);
    else if(!strcmp("rotate270", command->name))  terrain = api_rotate(terrain, ROTATE_270, infoMessage);
    else if(!strcmp("sethp", command->name))      api_setHeight(terrain, P0, P1, P2);
    else if(!strcmp("sethsel", command->name))    api_setHeightSelection(terrain, P0, P1, P2, P3, P4);
    else if(!strcmp("sethterr", command->name))   api_setHeightTerrain(terrain, P0);
    else if(!strcmp("sinksel", command->name))    api_sinkSelection(terrain, P0, P1, P2, P3, P4);
    else if(!strcmp("sinkterr", command->name))   api_sinkTerrain(terrain, P0);

    /*else if(!strcmp("flood", command->name))      infoMessage = api_floodArea(terrain, P0, P1, P2);
    else if(!strcmp("help", command->name))       printCommands(console);
    else if(!strcmp("loadscr", command->name))    loadScript(console, *(strParams + 0));
    else if(!strcmp("merge", command->name))      api_MergeTerrains(NULL, NULL, P0, P1, P2);
    else if(!strcmp("replace", command->name))    infoMessage = api_replace(terrain, P0, P1, P2, P3);
    else if(!strcmp("smoothsel", command->name))  infoMessage = api_smoothSelection(terrain, P0, P1, P2, P3);
    else if(!strcmp("smoothterr", command->name)) infoMessage = api_smoothTerrain(terrain);*/

    console->terrain = terrain;
    deleteParamsValue(command);
    printInfoMessage(infoMessage, console);
}

void printInfoMessage(char *infoMessage, Console *console) {
    if(infoMessage == NULL) return;

    consoleAddStringLine(console, infoMessage, false);
    free(infoMessage);
}

bool areParamsValid(Command *command, int *intParams, char **strParams, char *infoMessage) {
    if(command->numParams == 0) return true;

    int currentIntParam = 0;
    int currentStrParam = 0;
    bool validParams = false;
    Param *currentParam = NULL;

    int i;
    for(i = 0; i < command->numParams; i++) {
        currentParam = command->params + i;

        switch(currentParam->type) {
            case INT: *(intParams + (currentIntParam++)) = getParamValueInt(currentParam->key, command, &validParams, infoMessage); break;
            case STRING: *(strParams + (currentStrParam++)) = getParamValueStr(currentParam->key, command, &validParams, infoMessage); break;
        }

        if(!validParams) break;
    }

    return validParams;
}

int getParamValueInt(char *paramName, Command *command, bool *validParam, char *infoMessage) {
    Param *param = lookupParam(paramName, command);

    if(!param->value) {
        sprintf(infoMessage, "[ERROR] The '%s' parameter is not present\n", paramName);
        *validParam = false;
        return -1;
    }

    *validParam = true;
    return atoi(param->value);
}

char *getParamValueStr(char *paramName, Command *command, bool *validParam, char *infoMessage) {
    Param *param = lookupParam(paramName, command);

    if(!param->value) {
        sprintf(infoMessage, "[ERROR] The '%s' parameter is not present\n", paramName);
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

void consoleResize(Console *console, int newRowsNum, int newColsNum) {

}
