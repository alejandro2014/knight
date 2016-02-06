#include "console_draw.h"
#include "console_write.h"

void consoleAddChar(Console *console, char currentChar) {
    ConsoleLine *line = console->visual->lastLine;
    int width = console->visual->widthChars;

    *(line->content + console->visual->lineOffset) = currentChar;
    console->visual->lineOffset++;

    if(console->visual->lineOffset == width) {
        if(line->next == NULL) {
            addLineToConsole(console);
        } else {
            console->visual->lastLine = line->next;
            console->visual->lineOffset = 0;
        }
    }
}

void consoleDeleteChar(Console *console) {
    ConsoleLine *line = console->visual->lastLine;

    if(console->visual->lineOffset > 0) {
        console->visual->lineOffset--;
    } else {
        console->visual->lastLine = console->visual->lastLine->previous;
        console->visual->lineOffset = console->visual->widthChars - 1;
    }

    *(console->visual->lastLine->content + console->visual->lineOffset) = '\0';
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
