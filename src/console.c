#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "console.h"

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
