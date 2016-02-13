#include "console_draw.h"
#include "console_write.h"

void consoleAddChar(Console *console, char currentChar, bool addToCommand) {
    ConsoleVisualParams *visual = console->visual;
    ConsoleLine *line = visual->lastLine;
    int width = visual->widthChars;

    if(addToCommand) {
        *(console->currentLine + console->currentLineOffset++) = currentChar;
    }

    *(line->content + visual->lineOffset++) = currentChar;

    if(visual->lineOffset == width) {
        addLineToConsole(console);
    }
}

void consoleDeleteChar(Console *console) {
    ConsoleVisualParams *visual = console->visual;
    ConsoleLine *line = visual->lastLine;

    if(isCursorAfterPrompt(visual)) return;

    if(visual->lineOffset > 0) {
        visual->lineOffset--;
        *(line->content + visual->lineOffset) = '\0';

        console->currentLineOffset--;
        *(console->currentLine + console->currentLineOffset) = '\0';
        return;
    }

    //Go back to the previous line
    if(!line->newLine) {
        visual->lastLine = line->previous;
        visual->currentLineNumber--;

        visual->lineOffset = visual->widthChars - 1;
        *(line->content + visual->lineOffset) = '\0';

        console->currentLineOffset--;
        *(console->currentLine + console->currentLineOffset) = '\0';
    }
}

void consoleNewLine(Console *console) {
    addLineToConsole(console);
    console->visual->lastLine->newLine = true;
    printConsolePrompt(console);

    processCommand(console);

    memset(console->currentLine, 0, console->maxLineLength);
    console->currentLineOffset = 0;
}

void consoleAddString(Console *console, char *string, bool addToCommand) {
    int length = strlen(string);
    int i;

    for(i = 0; i < length; i++) {
        consoleAddChar(console, *(string + i), addToCommand);
    }
}

void consoleAddStringLine(Console *console, char *string, bool addToCommand) {
    consoleAddString(console, string, addToCommand);
    consoleNewLine(console);
}

bool isCursorAfterPrompt(ConsoleVisualParams *visual) {
    ConsoleLine *line = visual->lastLine;

    return (*(line->content + visual->lineOffset - 2) == '>' &&
            *(line->content + visual->lineOffset - 1) == ' ') ? true : false;
}
