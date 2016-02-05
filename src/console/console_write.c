#include "console_write.h"

void consoleAddChar(Console *console, char currentChar) {
    ConsoleLine *line = console->visual->lastLine;
    //int lineOffset = console->visual->lineOffset;
    //int width = console->visual->widthChars;
    /*int width = 5;

    if(lineOffset == width) {
        addLineToConsole(console);
    }*/

    *(line->content + console->visual->lineOffset) = currentChar;
    console->visual->lineOffset++;
}

void consoleDeleteChar(Console *console) {
    ConsoleLine *line = console->visual->lastLine;

    *(line->content + console->visual->lineOffset - 1) = '\0';
    console->visual->lineOffset--;
    /*char *buffer = console->buffer;
    int offset = console->offset;
    bool isCursorAfterPrompt = (*(buffer + offset - 2) == '>' && *(buffer + offset - 1) == ' ');

    if(!isCursorAfterPrompt) {
        console->offset--;
        *(buffer + console->offset) = '\0';
    }*/
}

void consoleNewLine(Console *console) {
    int maxLine = 14; //TODO Hardcoded variable
    consoleAddChar(console, '\n');

    console->visual->currentLineNumber++;

    if(console->visual->currentLineNumber > maxLine) {
        calculateWindowOffset(console);
    }
}

void consoleAddString(Console *console, char *string) {
    char *buffer = console->buffer;
    int length = strlen(string);

    memcpy(buffer + console->offset, string, length);
    console->offset += length;
}

void consoleAddStringLine(Console *console, char *string) {
    consoleAddString(console, string);
    consoleNewLine(console);
    console->visual->lineOffset = console->offset;
}

//TODO This function placed here seems to be a design error
void calculateWindowOffset(Console *console) {
    int position = console->visual->windowOffset;

    while(*(console->buffer + position) != '\n') {
        position++;
    }

    console->visual->windowOffset = position + 1;
}
