//#include "console.h"
#include "print.h"
#include "../api/api.h"
#include "../api/hme_lowlevel.h"

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

void printConsoleBanner(Console *console) {
    printf("Welcome to KNIGHT, the height terrain editor! - version %s\n", VERSION_NUMBER);
    printf("Alejandro Ruperez 2015. Enter 'help' to see available commands\n");
}

void printTerrain(Terrain *terrain) {
    int i, j;
    int columns = terrain->width;
    int rows = terrain->height;
    int value;

    for(i = 0; i < rows; i++) {
        printLine(columns);
        for(j = 0; j < columns; j++) {
            printf("| ");
            value = getHeight(terrain, j, i);
            if(value < 100) printf(" ");
            if(value < 10) printf(" ");
            printf("%d ", value);
        }
        printf("|\n");
    }
    printLine(columns);
}

void printLine(int width) {
    int i;
    for(i = 0; i < width; i++) {
        printf("+-----");
    }

    printf("+\n");
}
