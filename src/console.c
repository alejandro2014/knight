#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "console.h"

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

    if(getIndexCommand(str, listCommands) != -1) {
        while(str) {
            str = strtok(NULL, " ");
        }
    } else {
        printf("Unknown command: '%s'\n", str);
    }

    return NULL;
}

Command *loadCommands() {
    Command *commands = (Command *) malloc(NUM_COMMANDS * sizeof(Command));
    memset(commands, 0, NUM_COMMANDS * sizeof(Command));

    Command *command = NULL;

    Param *params = (Param *) malloc(sizeof(Param) * 2);
    (params + 0)->key = "width";
    (params + 1)->key = "height";

    setCommand(commands, GENERATE_TERRAIN, "gterr", params);
    setCommand(commands, ROTATE90, "rotate90", NULL);
    setCommand(commands, ROTATE180, "rotate180", NULL);
    setCommand(commands, ROTATE270, "rotate270", NULL);

    printf("List of commands\n");
    printf("----------------\n");
    printf("%s (%s, %s)\n", (commands + 0)->string, ((commands + 0)->params + 0)->key, ((commands + 0)->params + 1)->key);
    printf("%s ()\n", (commands + 1)->string);
    printf("%s ()\n", (commands + 2)->string);
    printf("%s ()\n", (commands + 3)->string);

    return commands;
}

void setCommand(Command *commands, int numCommand, char *name, Param *params) {
    Command *command = (commands + numCommand);
    command->string = name;
    command->params = params;
}

int getIndexCommand(char *command, Command *listCommands) {
    Command *currentCommand = NULL;
    int i;

    for(i = 0; i < NUM_COMMANDS; i++) {
        currentCommand = listCommands + i;
        if(!strcmp(currentCommand->string, command)) {
            return i;
        }
    }

    return -1;
}

int getIndexParam(char *param, Command *command) {
    return 0;
}
