#ifndef CONSOLE_H
#define CONSOLE_H

#define LINE_LENGTH 100

typedef struct {
    char *key;
    char *value;
} Param;

typedef struct {
    char *string;
    Param *params;
    char *target;
} Command;

typedef struct {
    int offset;
    int cursorPosition;
    int size;
    char *text;
    char *currentLine;
    size_t sizeLine;

} Console;

Command *loadCommands();
Console *createConsole(int sizeKb);
void freeConsole(Console *console);

void printPrompt();
void readShellLine(Console *console);
Command *parseCommand(char *stringCommand);

#endif
