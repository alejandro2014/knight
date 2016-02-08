#include "console_draw.h"
#include "console_write.h"

void consoleAddChar(Console *console, char currentChar) {
    ConsoleVisualParams *visual = console->visual;
    ConsoleLine *line = visual->lastLine;
    int width = visual->widthChars;

    *(line->content + visual->lineOffset) = currentChar;
    visual->lineOffset++;

    if(visual->lineOffset == width) {
        if(line->next == NULL) {
            addLineToConsole(console);
        } else {
            visual->lastLine = line->next;
            visual->lineOffset = 0;
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
    ConsoleVisualParams *visual = console->visual;
    ConsoleLine *line = visual->lastLine;

    if(line->next == NULL) {
        addLineToConsole(console);
    } else {
        visual->lastLine = line->next;
        visual->lineOffset = 0;
    }

    visual->lastLine->newLine = true;
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
