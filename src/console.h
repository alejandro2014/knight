#ifndef CONSOLE_H
#define CONSOLE_H

#define LINE_LENGTH 100

#define NUM_COMMANDS 4
#define MAX_PARAMS 10

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
    int numParams;
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
void setCommand(Command *commands, int numCommand, char *name);
void setParam(Command *commands, int numCommand, int positionParam, char *name);
void executeCommand(Command *command);

Console *createConsole(int sizeKb);
void freeConsole(Console *console);

void printPrompt();

void readShellLine(Console *console);
Command *parseCommand(char *strCommand, Command *listCommands);
Command *getCommand(char *command, Command *listCommands);
Param *getCommandParams(Command *command, char *paramName);
Param *getParam(char *paramName, Command *command);

Param *parseParam(char *paramString);
Param *createParam(char *key, char *value);

#endif
