#include <stdio.h>
#include <stdlib.h>

#include "menus.h"
#include "widgets.h"
#include "load_widgets_fake.h"

//TODO Replace the fakes for real parsing
Dialog **loadDialogs() {
    char *arrayDialogs[] = {"newTerrain", "generateTerrain", "object", "view",
                            "replace", "globalReplace", "rotation", "error"};
    int i;

    Dialog **dialogs = (Dialog **) malloc(sizeof(Dialog *) * NUM_DIALOGS);

    for(i = 0; i < NUM_DIALOGS; i++) {
        *(dialogs + i) = loadDialog(arrayDialogs[i]);
    }

    return dialogs;
}

Dialog *loadDialog(char *dialogName) {
    Dialog *dialog = loadDialogFake(dialogName);
    dialog->buttons = loadButtons(dialogName);
    dialog->checkBoxes = loadCheckBoxes(dialogName);
    dialog->textBoxes = loadTextBoxes(dialogName);
    dialog->texts = loadTexts(dialogName);

    return dialog;
}

Button **loadButtons(char *dialogName) {
    return loadButtonsFake(dialogName);
}

CheckBox **loadCheckBoxes(char *dialogName) {
    return loadCheckBoxesFake(dialogName);
}

TextBox **loadTextBoxes(char *dialogName) {
    return loadTextBoxesFake(dialogName);
}

Text **loadTexts(char *dialogName) {
    return loadTextsFake(dialogName);
}

void freeDialogs(Dialog **dialogs) {
    Dialog *dialog = NULL;
    int i;

    for(i = 0; i < NUM_DIALOGS; i++) {
        dialog = *(dialogs + i);
        freeButtons(dialog);
        freeCheckBoxes(dialog);
        freeTextBoxes(dialog);
        freeTexts(dialog);
        free(dialog);
    }
}

void freeButtons(Dialog *dialog) {
    int i;

    for(i = 0; i < dialog->numButtons; i++) {
        free(*(dialog->buttons + i));
    }
}

void freeCheckBoxes(Dialog *dialog) {
    int i;

    for(i = 0; i < dialog->numCheckBoxes; i++) {
        free(*(dialog->checkBoxes + i));
    }
}

void freeTextBoxes(Dialog *dialog) {
    int i;

    for(i = 0; i < dialog->numTextBoxes; i++) {
        free(*(dialog->textBoxes + i));
    }
}

void freeTexts(Dialog *dialog) {
    int i;

    for(i = 0; i < dialog->numTexts; i++) {
        free(*(dialog->texts + i));
    }
}
