#include "console.h"
#include "api.h"
#include "hme_lowlevel.h"
#include "global.h"

#include "main.h" //TODO Isn't this an error?
#include "helper.h"

extern HeightMapEditor heightMapEditor;

Console *createConsole(int sizeKb) {
    int i;

    alloc(console, Console, 1);
    allocExist(console->text, char, sizeKb * 1024);
    allocExist(console->currentLine, char, LINE_LENGTH);
    allocExist(console->commands, Command, NUM_COMMANDS);
    console->sizeLine = LINE_LENGTH;

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
    addCommand("flipx", console);
    addCommand("flipy", console);

    addCommand("invheight", console);
    addCommandParams("gterr", (char *[]){"width", "height"}, 2, console);

    addCommand("prterr", console);
    addCommandParams("setp", (char *[]){"x", "y", "height"}, 3, console);

    addCommandParams("riseterr", (char *[]){"delta"}, 1, console);
    addCommandParams("sinkterr", (char *[]){"delta"}, 1, console);
    addCommandParams("sethterr", (char *[]){"height"}, 1, console);
    addCommand("smoothterr", console);

    addCommandParams("risesel", (char *[]){"x1", "x2", "y1", "y2", "delta"}, 5, console);
    addCommandParams("sinksel", (char *[]){"x1", "x2", "y1", "y2", "delta"}, 5, console);
    addCommandParams("sethsel", (char *[]){"x1", "x2", "y1", "y2", "delta"}, 5, console);
    addCommandParams("smoothsel", (char *[]){"x1", "x2", "y1", "y2"}, 4, console);

    return console->commands;
}

void addCommandParams(char *commandName, char *params[], int numParams, Console *console) {
    addCommand(commandName, console);

    int i;
    for(i = 0; i < numParams; i++) {
        addParam(params[i], commandName, console);
    }
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
    printf("List of commands\n");
    printf("----------------\n");

    int i;
    for(i = 0; i < console->numCommands; i++)
        printCommand(console->commands + i);
}

void printCommand(Command *command) {
    Param *params = command->params;
    Param *currentParam = NULL;
    int j;

    printf("%s( ", command->name);

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
    *(console->currentLine + sizeLineRead - 1) = '\0';
}

Command *parseCommand(char *strCommand, Console *console) {
    char stringCommand[100];
    int length = strlen(strCommand);
    memcpy(stringCommand, strCommand, length);
    stringCommand[length] = '\0';

    char *commandName = strtok(stringCommand, " ");
    Command *command = lookupCommand(commandName, console);

    if(!command) {
        printf("Unknown command: '%s'\n", commandName);
        return NULL;
    }

    if(getCommandParams(command)) {
        return command;
    }

    return NULL;
}

bool getCommandParams(Command *command) {
    char *key = NULL;
    char *value = NULL;
    Param *param = NULL;
    char *typedParam = strtok(NULL, " ");
    bool execute = true;

    while(typedParam) {
        parseParam(typedParam, &key, &value);
        param = lookupParam(key, command);

        if(param) {
            param->value = value;
        } else {
            printf("Param not found [%s]\n", typedParam);
            execute = false;
            break;
        }

        typedParam = strtok(NULL, " ");
    }

    return execute;
}

void parseParam(char *paramString, char **key, char **value) {
    int length = strlen(paramString);
    int i;
    int colonPos = -1;

    for(i = 0; i < length; i++) {
        if(*(paramString + i) == ':') {
            colonPos = i;
            break;
        }
    }

    if(colonPos > 0) {
        allocExist(*key, char, colonPos + 1);
        memcpy(*key, paramString, colonPos);

        allocExist(*value, char, length - colonPos + 1);
        memcpy(*value, paramString + i + 1, length - colonPos + 1);
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
    bool error = false;
    int p1, p2, p3, p4, p5;
    alloc(params, int, 5);
    bool validParams = false;

    if(!strcmp("flipx", command->name)) {
        heightMapEditor.terrain = api_rotate(FLIP_XAXIS, heightMapEditor.terrain);
    } else if(!strcmp("flipy", command->name)) {
        heightMapEditor.terrain = api_rotate(FLIP_YAXIS, heightMapEditor.terrain);
    } else if(!strcmp("invheight", command->name)) {
        api_invertHeight(heightMapEditor.terrain);
    } else if(!strcmp("gterr", command->name)) {
        if(areParamsValid(command, params)) {
            heightMapEditor.terrain = api_generateTerrain(*(params + 0), *(params + 1));
        }
        /*p1 = getParamValueInt("width", command, &error);
        p2 = getParamValueInt("height", command, &error);
        if(!error) {
            heightMapEditor.terrain = api_generateTerrain(p1, p2);
        }*/
    } else if(!strcmp("prterr", command->name)) {
        showTerrainCmd(heightMapEditor.terrain);
    } else if(!strcmp("rotate90", command->name)) {
        heightMapEditor.terrain = api_rotate(ROTATE_90, heightMapEditor.terrain);
    } else if(!strcmp("rotate180", command->name)) {
        heightMapEditor.terrain = api_rotate(ROTATE_180, heightMapEditor.terrain);
    } else if(!strcmp("rotate270", command->name)) {
        heightMapEditor.terrain = api_rotate(ROTATE_270, heightMapEditor.terrain);
    } else if(!strcmp("setp", command->name)) {
        p1 = getParamValueInt("x", command, &error);
        p2 = getParamValueInt("y", command, &error);
        p3 = getParamValueInt("height", command, &error);
        if(!error) {
            api_setHeight(heightMapEditor.terrain, p1, p2, p3);
        }
    } else if(!strcmp("riseterr", command->name)) {
        p1 = getParamValueInt("delta", command, &error);
        if(!error) {
            api_riseTerrain(heightMapEditor.terrain, p1);
        }
    } else if(!strcmp("sinkterr", command->name)) {
        p1 = getParamValueInt("delta", command, &error);
        if(!error) {
            api_sinkTerrain(heightMapEditor.terrain, p1);
        }
    } else if(!strcmp("sethterr", command->name)) {
        p1 = getParamValueInt("height", command, &error);
        if(!error) {
            api_setHeightTerrain(heightMapEditor.terrain, p1);
        }
    } else if(!strcmp("smoothterr", command->name)) {
        api_smoothTerrain(heightMapEditor.terrain);
    } else if(!strcmp("risesel", command->name)) {
        p1 = getParamValueInt("x1", command, &error);
        p2 = getParamValueInt("y1", command, &error);
        p3 = getParamValueInt("x2", command, &error);
        p4 = getParamValueInt("y2", command, &error);
        p5 = getParamValueInt("delta", command, &error);
        api_riseSelection(heightMapEditor.terrain, p1, p2, p3, p4, p5);
    } else if(!strcmp("sinksel", command->name)) {
        p1 = getParamValueInt("x1", command, &error);
        p2 = getParamValueInt("y1", command, &error);
        p3 = getParamValueInt("x2", command, &error);
        p4 = getParamValueInt("y2", command, &error);
        p5 = getParamValueInt("delta", command, &error);
        api_sinkSelection(heightMapEditor.terrain, p1, p2, p3, p4, p5);
    } else if(!strcmp("sethsel", command->name)) {
        p1 = getParamValueInt("x1", command, &error);
        p2 = getParamValueInt("y1", command, &error);
        p3 = getParamValueInt("x2", command, &error);
        p4 = getParamValueInt("y2", command, &error);
        p5 = getParamValueInt("height", command, &error);
        api_setHeightSelection(heightMapEditor.terrain, p1, p2, p3, p4, p5);
    } else if(!strcmp("smoothsel", command->name)) {
        p1 = getParamValueInt("x1", command, &error);
        p2 = getParamValueInt("y1", command, &error);
        p3 = getParamValueInt("x2", command, &error);
        p4 = getParamValueInt("y2", command, &error);
        api_smoothSelection(heightMapEditor.terrain, p1, p2, p3, p4);
    }

    deleteParamsValue(command);
}

bool areParamsValid(Command *command, int *params) {
    bool validParams = false;
    int i;
    for(i = 0; i < command->numParams; i++) {
        printf("Checking param> %s\n", (command->params + i)->key);
        *(params + i) = getParamValueInt((command->params + i)->key, command, &validParams);
        if(!validParams) break;
    }

    return validParams;
}

int getParamValueInt(char *paramName, Command *command, bool *validParam) {
    Param *param = lookupParam(paramName, command);

    if(!param->value) {
        printf("[ERROR] The '%s' parameter is not present\n", paramName);
        *validParam = false;
        return -1;
    }

    *validParam = true;
    return atoi(param->value);
}

void deleteParamsValue(Command *command) {
    int i;

    for(i = 0; i < MAX_PARAMS; i++) {
        (command->params + i)->value = NULL;
    }
}
