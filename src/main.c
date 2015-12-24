#include "global.h"
#include "main.h"
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

    processCommand("gterr width:5 height:5", console);

    processCommand("sethterr height:5", console);
    processCommand("sethp x:1 y:1 height:3", console);
    processCommand("sethp x:2 y:1 height:3", console);
    processCommand("sethp x:3 y:1 height:3", console);

    processCommand("sethp x:1 y:2 height:3", console);
    processCommand("sethp x:2 y:2 height:1", console);
    //processCommand("sethp x:3 y:2 height:3", console);

    processCommand("sethp x:1 y:3 height:3", console);
    processCommand("sethp x:2 y:3 height:3", console);
    processCommand("sethp x:3 y:3 height:3", console);
    processCommand("prterr", console);

    processCommand("sethp x:2 y:2 height:4", console);
    processCommand("prterr", console);

    processCommand("flood x:2 y:2", console);
    processCommand("prterr", console);

    while(!finish) {
        printPrompt();
        readShellLine(console, stdin);
        finish = processCommand(console->currentLine, console);
    }

    freeConsole(console);

    return 0;
}
