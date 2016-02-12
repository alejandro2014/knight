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
    bool isCursorAfterPrompt = (*(line->content + visual->lineOffset - 2) == '>' && *(line->content + visual->lineOffset - 1) == ' ');

    if(isCursorAfterPrompt) return;

    if(visual->lineOffset > 0) {
        visual->lineOffset--;
        *(visual->lastLine->content + visual->lineOffset) = '\0';

        console->currentLineOffset--;
        *(console->currentLine + console->currentLineOffset) = '\0';
    } else if(!visual->lastLine->newLine) {
        visual->lastLine = visual->lastLine->previous;
        visual->currentLineNumber--;

        visual->lineOffset = visual->widthChars - 1;
        *(visual->lastLine->content + visual->lineOffset) = '\0';

        console->currentLineOffset--;
        *(console->currentLine + console->currentLineOffset) = '\0';
    }
}

void consoleNewLine(Console *console) {
    int lengthCurrentLine = 100; //TODO Hardcoded
    addLineToConsole(console);
    console->visual->lastLine->newLine = true;
    printConsolePrompt(console);

    printf("Exec -> [%s]\n", console->currentLine);

    memset(console->currentLine, 0, lengthCurrentLine);
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
