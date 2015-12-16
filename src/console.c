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

Command *parseCommand(char *strCommand) {
    printf("Analyzing command [%s]\n", strCommand);
    char stringCommand[100];
    int length = strlen(strCommand);
    memcpy(stringCommand, strCommand, length);
    stringCommand[length] = 0x00;

    char *str = strtok(stringCommand, " ");

    while(str) {
        printf(">> Detected [%s]\n", str);
        str = strtok(NULL, " ");
    }

    return NULL;

    /*int numTokens = 0;
    int i;

    for(i = 0; i < numTokens; i++) {
        printf(">> %s\n", *(tokens + i));
    }

    return NULL;*/
}

Command *loadCommands() {
    /*int numCommands = 1;
    Command *commands = (Command *) malloc(numCommands * sizeof(Command));

    Param *params = (Param *) malloc(1, sizeof(Param));
    *(params + 0)->key = "-w";
    *(params + 1)->key = "-h";

    *(commands + 0)->string = "gterr";
    *(commands + 0)->params = params;

    return commands;*/
    return NULL;
}
