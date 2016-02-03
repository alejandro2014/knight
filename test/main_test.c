#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/console/write_console.h"

void consoleAddsCharProperly();

int main(int argn, char *argv[]) {
    consoleAddsCharProperly();
    return 0;
}

void consoleAddsCharProperly() {
    printf("* Console adds char properly...");
    Console *console = (Console *) malloc(sizeof(Console));
    memset(console, 0, sizeof(Console));

    console->buffer = (char *) malloc(100 * sizeof(char));
    memset(console->buffer, 0, 100 * sizeof(char));

    consoleAddChar(console, 'a');

    assert(*(console->buffer + 0) == 'a');
    assert(console->offset == 1);

    free(console->buffer);
    free(console);
    printf(" [OK]\n");
}
