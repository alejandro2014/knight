#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "console.h"
#include "api.h"

Console *createConsole(int sizeKb) {
    alloc(console, Console, 1);
    console->sizeLine = LINE_LENGTH;

    int sizeBytes = sizeKb * 1024 * sizeof(char);
    console->text = (char *) malloc(sizeBytes);
    memset(console->text, 0, sizeBytes);

    console->currentLine = (char *) malloc(LINE_LENGTH * sizeof(char));
    memset(console->currentLine, 0, sizeof(LINE_LENGTH));

    allocExist(console->commands, Command, NUM_COMMANDS);

    int i;
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

void printPrompt() {
    printf("> ");
}

void readShellLine(Console *console) {
    size_t sizeLineRead = getline(&console->currentLine, &console->sizeLine, stdin);
    *(console->currentLine + sizeLineRead - 1) = 0x00;
}

Command *parseCommand(char *strCommand, Console *console) {
    char stringCommand[100];
    int length = strlen(strCommand);
    memcpy(stringCommand, strCommand, length);
    stringCommand[length] = 0x00;

    char *commandName = strtok(stringCommand, " ");
    Command *command = lookupCommand(commandName, console);

    if(!command) {
        printf("Unknown command: '%s'\n", commandName);
        return NULL;
    }

    printf("Executing command [%s]\n", commandName);
    //getCommandParams(command);
    return command;
}

Param *getCommandParams(Command *command) {
    char *key = NULL;
    char *value = NULL;
    Param *param = NULL;
    char *paramName = strtok(NULL, " ");

    while(paramName) {
        printf("Param name: [%s] -> ", paramName);
        //param = getParam(str, command);
        parseParam(paramName, &key, &value);
        printf(" %s, %s\n", key, value);

        if(getParam(key, command)) {
            printf("Detected param [%s]\n", paramName);
        } else {
            printf("Param not found [%s]\n", paramName);
        }

        paramName = strtok(NULL, " ");
    }

    return NULL;
}

//TODO Refactor
void parseParam(char *paramString, char **key, char **value) {
    Param *param = (Param *) malloc(sizeof(Param));
    int length = strlen(paramString);
    int i;

    for(i = 0; i < length; i++) {
        if(*(paramString + i) == ':') {
            *key = (char *) malloc((i + 1) * sizeof(char));
            memcpy(*key, paramString, i);
            *(*key + i) = 0x00;

            *value = (char *) malloc((length - i + 1) * sizeof(char));
            memcpy(*value, paramString + i + 1, length - i + 1);
            *(*value + length + 1) = 0x00;
            break;
        }
    }
}

Param *createParam(char *key, char *value) {
    alloc(param, Param, 1);
    param->key = key;
    param->value = value;

    return param;
}

void executeCommand(Command *command) {
    return;
    if(!strcmp("gterr", command->name)) {
        api_generateTerrain(2, 3);
    }
}

Command *loadCommands(Console *console) {
    Command *command = NULL;

    addCommand("rotate90", console);
    addCommand("rotate180", console);
    addCommand("rotate270", console);

    addCommand("gterr", console);
    addParam("width", "gterr", console);
    addParam("height", "gterr", console);

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

void printCommands(Console *console) {
    Command *command = NULL;
    Param *params = NULL;
    int i, j;

    printf("List of commands\n");
    printf("----------------\n");

    for(i = 0; i < console->numCommands; i++) {
        command = console->commands + i;
        printf("%s( ", command->name);

        params = command->params;
        for(j = 0; j < command->numParams; j++) {
            printf("%s ", (params + j)->key);
        }

        printf(")\n");
    }
}

void setCommand(Command *commands, int numCommand, char *name) {
    Command *command = (commands + numCommand);
    command->name = name;
}

void setParam(Command *commands, int numCommand, int positionParam, char *name) {
    Param *params = (commands + numCommand)->params;
    (params + positionParam)->key = name;
}

Command *getCommand(char *command, Command *listCommands) {
    printf("Looking for command [%s]\n", command);
    Command *currentCommand = NULL;
    int i;

    for(i = 0; i < NUM_COMMANDS; i++) {
        currentCommand = listCommands + i;
        if(!strcmp(currentCommand->name, command)) {
            return currentCommand;
        }
    }

    return NULL;
}

Param *getParam(char *paramName, Command *command) {
    Param *currentParam = NULL;
    int i;

    for(i = 0; i < MAX_PARAMS; i++) {
        currentParam = command->params + i;

        if(!strcmp(paramName, currentParam->key)) {
            return currentParam;
        }
    }

    return NULL;
}
