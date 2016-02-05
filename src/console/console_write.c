#include "write_console.h"

void consoleAddChar(Console *console, char currentChar) {
    char *buffer = console->buffer;

    *(buffer + console->offset) = currentChar;
    console->offset++;
}

void consoleDeleteChar(Console *console) {
    char *buffer = console->buffer;
    int offset = console->offset;
    bool isCursorAfterPrompt = (*(buffer + offset - 2) == '>' && *(buffer + offset - 1) == ' ');

    if(!isCursorAfterPrompt) {
        console->offset--;
        *(buffer + console->offset) = '\0';
    }
}

void consoleNewLine(Console *console) {
    int maxLine = 14; //TODO Hardcoded variable
    consoleAddChar(console, '\n');

    console->currentLineNumber++;

    if(console->currentLineNumber > maxLine) {
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
    console->lastLineOffset = console->offset;
}

//TODO This function placed here seems to be a design error
void calculateWindowOffset(Console *console) {
    int position = console->windowOffset;

    while(*(console->buffer + position) != '\n') {
        position++;
    }

    console->windowOffset = position + 1;
}
