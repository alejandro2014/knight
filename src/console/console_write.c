#include "console_draw.h"
#include "console_write.h"

void consoleAddChar(Console *console, char currentChar) {
    ConsoleVisualParams *visual = console->visual;
    ConsoleLine *line = visual->lastLine;
    int width = visual->widthChars;

    *(line->content + visual->lineOffset) = currentChar;
    visual->lineOffset++;

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
    } else if(!visual->lastLine->newLine) {
        visual->lastLine = visual->lastLine->previous;
        visual->currentLineNumber--;

        visual->lineOffset = visual->widthChars - 1;
        *(visual->lastLine->content + visual->lineOffset) = '\0';
    }
}

void consoleNewLine(Console *console) {
    addLineToConsole(console);
    console->visual->lastLine->newLine = true;
    printConsolePrompt(console);
}

void consoleAddString(Console *console, char *string) {
    int length = strlen(string);
    int i;

    for(i = 0; i < length; i++) {
        consoleAddChar(console, *(string + i));
    }
}

void consoleAddStringLine(Console *console, char *string) {
    consoleAddString(console, string);
    consoleNewLine(console);
}

//TODO This function placed here seems to be a design error
void calculateWindowOffset(Console *console) {
    int position = console->visual->windowOffset;

    while(*(console->buffer + position) != '\n') {
        position++;
    }

    console->visual->windowOffset = position + 1;
}
