#include "print.h"
#include "../api/api.h"
#include "../api/hme_lowlevel.h"

void printConsolePrompt(Console *console) {
    consoleAddString(console, "> ");
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

void printConsoleBanner(Console *console) {
    alloc(banner, char, 100);

    sprintf(banner, "Welcome to KNIGHT, the height terrain editor! - version %s", VERSION_NUMBER);
    consoleAddStringLine(console, banner);
    consoleAddStringLine(console, "Alejandro Ruperez 2015. Enter 'help' to see available commands");
    printConsolePrompt(console);
}
