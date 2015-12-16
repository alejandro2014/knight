#ifndef CONSOLE_H
#define CONSOLE_H

typedef struct {
    char *key;
    char *value;
} Param;

typedef struct {
    char *string;
    Param *params;
    char *target;
} Command;

Command *parseCommand(char *stringCommand);

#endif
