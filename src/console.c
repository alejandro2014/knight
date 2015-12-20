#include "console.h"
#include "api.h"
#include "hme_lowlevel.h"
#include "global.h"

#include "main.h" //TODO Isn't this an error?
#include "helper.h"

extern HeightMapEditor heightMapEditor;

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

    printf("[INFO] Created console. size: %dkb maxCommands: %d maxParams: %d\n", sizeKb, NUM_COMMANDS, MAX_PARAMS);

    return console;
}

void freeConsole(Console *console) {
    free(console->text);
    free(console);
}

Command *loadCommands(Console *console) {
    Command *command = NULL;

    /*addCommand("rotate90", console);
    addCommand("rotate180", console);
    addCommand("rotate270", console);*/

    addCommand("gterr", console);
    addParam("width", "gterr", console);
    addParam("height", "gterr", console);

    addCommand("setp", console);
    addParam("x", "setp", console);
    addParam("y", "setp", console);
    addParam("height", "setp", console);

    return console->commands;
}

void addCommand(char *commandName, Console *console) {
    int positionCommand = console->numCommands;
    Command *command = console->commands + positionCommand;
    command->name = commandName;
    console->numCommands++;
}

void addParam(char *paramName, char *commandName, Console *console) {
    Command *command = lookupCommand(commandName, console);
    int positionParam = command->numParams;
    Param *param = command->params + positionParam;
    param->key = paramName;
    command->numParams++;
}

void printPrompt() {
    printf("> ");
}

void printCommands(Console *console) {
    printf("List of commands\n");
    printf("----------------\n");

    int i;
    for(i = 0; i < console->numCommands; i++)
        printCommand(console->commands + i);
}

void printCommand(Command *command) {
    Param *params = command->params;
    Param *currentParam = NULL;
    int j;

    printf("%s( ", command->name);

    for(j = 0; j < command->numParams; j++) {
        currentParam = params + j;
        printf("%s ", currentParam->key);

        if(currentParam->value)
            printf("-> %s ", currentParam->value);
    }

    printf(")\n");
}

void readShellLine(Console *console) {
    size_t sizeLineRead = getline(&console->currentLine, &console->sizeLine, stdin);
    *(console->currentLine + sizeLineRead - 1) = '\0';
}

bool parseCommand(char *strCommand, Console *console) {
    char stringCommand[100];
    int length = strlen(strCommand);
    memcpy(stringCommand, strCommand, length);
    stringCommand[length] = '\0';

    char *commandName = strtok(stringCommand, " ");
    Command *command = lookupCommand(commandName, console);

    if(!command) {
        printf("Unknown command: '%s'\n", commandName);
        return false;
    }

    if(getCommandParams(command)) {
        console->currentCommand = command;
        return true;
    }

    return false;
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

void executeCommand(Command *command) {
    bool error = false;
    int p1, p2, p3;

    if(!strcmp("gterr", command->name)) {
        p1 = getParamValueInt("width", command, &error);
        p2 = getParamValueInt("height", command, &error);
        if(!error) {
            heightMapEditor.terrain = api_generateTerrain(p1, p2);
            showTerrainCmd(heightMapEditor.terrain);
        }
    } else if(!strcmp("setp", command->name)) {
        p1 = getParamValueInt("x", command, &error);
        p2 = getParamValueInt("y", command, &error);
        p3 = getParamValueInt("height", command, &error);
        if(!error) {
            api_setHeight(heightMapEditor.terrain, p1, p2, p3);
            showTerrainCmd(heightMapEditor.terrain);
        }
    }
    /*else if(!strcmp("rotate90", command->name)) {
        api_rotate(ROTATE_90, terrain);
    } else if(!strcmp("rotate180", command->name)) {
        api_rotate(ROTATE_90, terrain);
    } else if(!strcmp("rotate270", command->name)) {
        api_rotate(ROTATE_90, terrain);
    }*/

    deleteParamsValue(command);
}

int getParamValueInt(char *paramName, Command *command, bool *error) {
    Param *param = lookupParam(paramName, command);

    if(!param->value) {
        printf("[ERROR] The '%s' parameter is not present\n", paramName);
        *error = true;
        return -1;
    }

    return atoi(param->value);
}

void deleteParamsValue(Command *command) {
    int i;

    for(i = 0; i < MAX_PARAMS; i++) {
        (command->params + i)->value = NULL;
    }
}
