#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/console/write_console.h"

int main(int argn, char *argv[]) {
    Console *console = (Console *) malloc(sizeof(Console));
    memset(console, 0, sizeof(Console));

    char *buffer = (char *) malloc(100 * sizeof(char));
    memset(buffer, 0, 100 * sizeof(char));

    console->buffer = buffer;

    consoleAddChar(console, 'a');

    assert(*(console->buffer + 0) == 'b');
    assert(console->offset == 1);

    free(buffer);
    free(console);
    return 0;
}
