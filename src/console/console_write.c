#include "console_draw.h"
#include "console_write.h"

void consoleAddChar(Console *console, char currentChar) {
    ConsoleVisualParams *visual = console->visual;
    ConsoleLine *line = visual->lastLine;
    int width = visual->widthChars;

    *(line->content + visual->lineOffset) = currentChar;
    visual->lineOffset++;

    if(visual->lineOffset == width) {
        printf("offset = %d. New line\n", width);
        if(line->next == NULL) {
            addLineToConsole(console);
        } else {
            visual->lastLine = line->next;
            visual->lineOffset = 0;
        }
    }
}

void consoleDeleteChar(Console *console) {
    ConsoleVisualParams *visual = console->visual;
    ConsoleLine *line = visual->lastLine;

    if(visual->lineOffset > 0) {
        visual->lineOffset--;
        *(visual->lastLine->content + visual->lineOffset) = '\0';
    } else if(!visual->lastLine->newLine) {
        visual->lastLine = visual->lastLine->previous;
        visual->lineOffset = visual->widthChars - 1;
        *(visual->lastLine->content + visual->lineOffset) = '\0';
    }

    /*char *buffer = console->buffer;
    int offset = console->offset;
    bool isCursorAfterPrompt = (*(buffer + offset - 2) == '>' && *(buffer + offset - 1) == ' ');

    if(!isCursorAfterPrompt) {
        console->offset--;
        *(buffer + console->offset) = '\0';
    }*/
}

void consoleNewLine(Console *console) {
    addLineToConsole(console);
    console->visual->lastLine->newLine = true;
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
    //console->visual->lineOffset = console->offset;
}

//TODO This function placed here seems to be a design error
void calculateWindowOffset(Console *console) {
    int position = console->visual->windowOffset;

    while(*(console->buffer + position) != '\n') {
        position++;
    }

    console->visual->windowOffset = position + 1;
}
