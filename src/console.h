#ifndef CONSOLE_H
#define CONSOLE_H

#define LINE_LENGTH 100

#define NUM_COMMANDS 4
#define GENERATE_TERRAIN 0
#define ROTATE90 1
#define ROTATE180 2
#define ROTATE270 3

typedef struct {
    char *key;
    char *value;
} Param;

typedef struct {
    char *name;
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
void setCommand(Command *commands, int numCommand, char *name, Param *params);

Console *createConsole(int sizeKb);
void freeConsole(Console *console);

void printPrompt();
void readShellLine(Console *console);
Command *parseCommand(char *strCommand, Command *listCommands);

int getIndexCommand(char *command, Command *listCommands);
int getIndexParam(char *param, Command *command);

#endif
