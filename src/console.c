#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "console.h"
#include "api.h"

Console *createConsole(int sizeKb) {
    Console *console = (Console *) malloc(sizeof(Console));
    memset(console, 0, sizeof(Console));

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

Param *parseParam(char *paramString) {
    char *key;
    char *value;
    int length = strlen(paramString);
    int i;

    for(i = 0; i < length; i++) {
        if(*(paramString + i) == ':') {
            key = (char *) malloc((i + 1) * sizeof(char));
            memcpy(key, paramString, i);
            *(key + i) = 0x00;
            printf("Detected param name [%s]\n", key);

            value = (char *) malloc((length - i + 1) * sizeof(char));
            memcpy(value, paramString + i + 1, length - i + 1);
            *(value + length + 1) = 0x00;
            printf("Detected param value [%s]\n", value);
            break;
        }
    }

    return NULL;
}

Param *createParam(char *key, char *value) {
    Param *param = (Param *) malloc(sizeof(Param));
    memset(param, 0, sizeof(Param));
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
    Command *commands = (Command *) malloc(NUM_COMMANDS * sizeof(Command));
    memset(commands, 0, NUM_COMMANDS * sizeof(Command));

    Command *command = NULL;

    Param *params = (Param *) malloc(sizeof(Param) * 2);
    (params + 0)->key = "width";
    (params + 1)->key = "height";

    setCommand(commands, GENERATE_TERRAIN, "gterr", params, 2);
    setCommand(commands, ROTATE90, "rotate90", NULL, 0);
    setCommand(commands, ROTATE180, "rotate180", NULL, 0);
    setCommand(commands, ROTATE270, "rotate270", NULL, 0);

    printf("List of commands\n");
    printf("----------------\n");
    printf("%s (%s, %s)\n", (commands + 0)->name, ((commands + 0)->params + 0)->key, ((commands + 0)->params + 1)->key);
    printf("%s ()\n", (commands + 1)->name);
    printf("%s ()\n", (commands + 2)->name);
    printf("%s ()\n", (commands + 3)->name);

    return commands;
}

void setCommand(Command *commands, int numCommand, char *name, Param *params, int numParams) {
    Command *command = (commands + numCommand);
    command->name = name;
    command->params = params;
    command->numParams = numParams;
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
