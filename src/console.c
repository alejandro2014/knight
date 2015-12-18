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

    printf("[INFO] Created console (%dkb)\n", sizeKb);

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

Command *parseCommand(char *strCommand, Command *listCommands) {
    char stringCommand[100];
    int length = strlen(strCommand);
    memcpy(stringCommand, strCommand, length);
    stringCommand[length] = 0x00;

    char *str = strtok(stringCommand, " ");
    Command *command = getCommand(str, listCommands);

    if(!command) {
        printf("Unknown command: '%s'\n", str);
        return NULL;
    }

    getCommandParams(command, str);
    return command;
}

Param *getCommandParams(Command *command, char *str) {
    Param *param = NULL;
    str = strtok(NULL, " ");

    while(str) {
        param = getParam(str, command);

        if(param) {
            printf("Detected param [%s]\n", str);
        } else {
            printf("Param not found [%s]\n", str);
        }

        str = strtok(NULL, " ");
    }

    return NULL;
}

//TODO Refactor
Param *parseParam(char *paramString) {
    Param *param = (Param *) malloc(sizeof(Param));
    char *key;
    char *value;
    int length = strlen(paramString);
    int i;

    for(i = 0; i < length; i++) {
        if(*(paramString + i) == ':') {
            key = (char *) malloc((i + 1) * sizeof(char));
            memcpy(key, paramString, i);
            *(key + i) = 0x00;

            value = (char *) malloc((length - i + 1) * sizeof(char));
            memcpy(value, paramString + i + 1, length - i + 1);
            *(value + length + 1) = 0x00;
            break;
        }
    }

    param->key = key;
    param->value = value;

    return param;
}

Param *createParam(char *key, char *value) {
    alloc(param, Param, 1);
    param->key = key;
    param->value = value;

    return param;
}

void executeCommand(Command *command) {
    if(!strcmp("gterr", command->name)) {
        api_generateTerrain(2, 3);
    }
}

Command *loadCommands() {
    int i;
    alloc(commands, Command, NUM_COMMANDS);

    for(i = 0; i < NUM_COMMANDS; i++) {
        allocExist((commands + i)->params, Param, MAX_PARAMS);

    }

    Command *command = NULL;

    setCommand(commands, ROTATE90, "rotate90");
    setCommand(commands, ROTATE180, "rotate180");
    setCommand(commands, ROTATE270, "rotate270");

    setCommand(commands, GENERATE_TERRAIN, "gterr");
    setParam(commands, GENERATE_TERRAIN, 0, "width");
    setParam(commands, GENERATE_TERRAIN, 1, "height");

    printf("List of commands\n");
    printf("----------------\n");
    printf("%s (%s, %s)\n", (commands + 0)->name, ((commands + 0)->params + 0)->key, ((commands + 0)->params + 1)->key);
    printf("%s ()\n", (commands + 1)->name);
    printf("%s ()\n", (commands + 2)->name);
    printf("%s ()\n", (commands + 3)->name);

    return commands;
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

    for(i = 0; i < command->numParams; i++) {
        currentParam = command->params + i;

        if(!strcmp(paramName, currentParam->key)) {
            return currentParam;
        }
    }

    return NULL;
}
