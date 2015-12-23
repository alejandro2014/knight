#include "global.h"
#include "main.h"
#include "helper.h"
#include "api/api.h"
#include "api/hme_lowlevel.h"
#include "console/console.h"
#include "console/print.h"

HeightMapEditor heightMapEditor;

int main(int argc, char* argv[]) {
    bool finish = false;
    Console *console = createConsole(1);
    heightMapEditor.console = console;
    Command *listCommands = loadCommands(console);

    printConsoleBanner(console);

    processCommand("randgterr width:9 height:9", console);
    processCommand("prterr", console);

    while(!finish) {
        printPrompt();
        readShellLine(console, stdin);
        finish = processCommand(console->currentLine, console);
    }

    freeConsole(console);

    return 0;
}
