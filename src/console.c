#include "console.h"
#include "api.h"
#include "global.h"

Console *createConsole(int sizeKb) {
    alloc(console, Console, 1);
    console->sizeLine = LINE_LENGTH;

    int sizeBytes = sizeKb * 1024 * sizeof(char);
    console->text = (char *) malloc(sizeBytes);
    memset(console->text, 0, sizeBytes);

    console->currentLine = (char *) malloc(LINE_LENGTH * sizeof(char));
    memset(console->currentLine, 0, sizeof(LINE_LENGTH));

    allocExist(console->commands, Command, NUM_COMMANDS);

    int i;
    for(i = 0; i < NUM_COMMANDS; i++) {
        allocExist((console->commands + i)->params, Param, MAX_PARAMS);
    }

    printf("[INFO] Created console. size: %dkb maxCommands: %d maxParams: %d\n", sizeKb, NUM_COMMANDS, MAX_PARAMS);

    return console;
}

void freeConsole(Console *console) {
    free(console->text);
    free(console);
}

Command *loadCommands(Console *console) {
    Command *command = NULL;

    addCommand("rotate90", console);
    addCommand("rotate180", console);
    addCommand("rotate270", console);

    addCommand("gterr", console);
    addParam("width", "gterr", console);
    addParam("height", "gterr", console);

    return console->commands;
}

void addCommand(char *commandName, Console *console) {
    int positionCommand = console->numCommands;
    Command *command = console->commands + positionCommand;
    command->name = commandName;
    console->numCommands++;
}

void addParam(char *paramName, char *commandName, Console *console) {
    Command *command = lookupCommand(commandName, console);
    int positionParam = command->numParams;
    Param *param = command->params + positionParam;
    param->key = paramName;
    command->numParams++;
}

void printPrompt() {
    printf("> ");
}

void printCommands(Console *console) {
    Command *command = NULL;
    int i;

    printf("List of commands\n");
    printf("----------------\n");

    for(i = 0; i < console->numCommands; i++) {
        command = console->commands + i;
        printCommand(command);
    }
}

void printCommand(Command *command) {
    Param *params = NULL;
    Param *currentParam = NULL;
    int j;

    printf("%s( ", command->name);

    params = command->params;
    for(j = 0; j < command->numParams; j++) {
        currentParam = params + j;
        printf("%s ", currentParam->key);

        if(currentParam->value)
            printf("-> %s ", currentParam->value);
    }

    printf(")\n");
}

void readShellLine(Console *console) {
    size_t sizeLineRead = getline(&console->currentLine, &console->sizeLine, stdin);
    *(console->currentLine + sizeLineRead - 1) = 0x00;
}

bool parseCommand(char *strCommand, Console *console) {
    char stringCommand[100];
    int length = strlen(strCommand);
    memcpy(stringCommand, strCommand, length);
    stringCommand[length] = 0x00;

    char *commandName = strtok(stringCommand, " ");
    Command *command = lookupCommand(commandName, console);

    if(!command) {
        printf("Unknown command: '%s'\n", commandName);
        return false;
    }

    printf("Executing command [%s]\n", commandName);
    if(getCommandParams(command)) {
        console->currentCommand = command;
        return true;
    }

    return false;
}

bool getCommandParams(Command *command) {
    char *key = NULL;
    char *value = NULL;
    Param *param = NULL;
    char *paramName = strtok(NULL, " ");
    bool execute = true;

    while(paramName) {
        printf("[%s] -> ", paramName);
        parseParam(paramName, &key, &value);
        printf(" %s, %s\n", key, value);

        param = lookupParam(key, command);
        if(param) {
            printf("Found param: %s\n", param->key);
            param->value = value;
        } else {
            printf("Param not found [%s]\n", paramName);
            execute = false;
            break;
        }

        paramName = strtok(NULL, " ");
    }

    return execute;
}

void parseParam(char *paramString, char **key, char **value) {
    Param *param = (Param *) malloc(sizeof(Param));
    int length = strlen(paramString);
    int i;

    for(i = 0; i < length; i++) {
        if(*(paramString + i) == ':') {
            *key = (char *) malloc((i + 1) * sizeof(char));
            memcpy(*key, paramString, i);
            *(*key + i) = 0x00;

            *value = (char *) malloc((length - i + 1) * sizeof(char));
            memcpy(*value, paramString + i + 1, length - i + 1);
            *(*value + length + 1) = 0x00;
            break;
        }
    }
}

Command *lookupCommand(char *commandName, Console *console) {
    Command *currentCommand = NULL;
    int i;

    for(i = 0; i < console->numCommands; i++) {
        currentCommand = console->commands + i;

        if(!strcmp(currentCommand->name, commandName)) {
            return currentCommand;
        }
    }

    return NULL;
}

Param *lookupParam(char *paramName, Command *command) {
    Param *currentParam = NULL;
    int i;

    for(i = 0; i < command->numParams; i++) {
        currentParam = command->params + i;

        if(!strcmp(paramName, currentParam->key)) {
            return currentParam;
        }
    }

    return NULL;
}

void executeCommand(Command *command) {
    if(!strcmp("gterr", command->name)) {
        api_generateTerrain(getParamValueInt("width", command),
                            getParamValueInt("height", command));
    }
}

int getParamValueInt(char *paramName, Command *command) {
    Param *param = lookupParam(paramName, command);
    return atoi(param->value);
}
