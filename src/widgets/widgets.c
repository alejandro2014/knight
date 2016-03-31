#include <stdio.h>
#include <stdlib.h>

#include "menus.h"
#include "widgets.h"
#include "load_widgets_fake.h"

extern Dialog *registeredDialogs;
//TODO Replace the fakes for real parsing
void loadDialogs(Font *font) {
    Dialog *dialog = NULL;
    allocExist(registeredDialogs, Dialog, NUM_DIALOGS);

    registerDialog("New terrain", 200, 100, 350, 250);
    dialog = getDialog("New terrain");
    dialogSetNumberElements(dialog, 2, 0, 3, 0);
    dialog->font = font;

    registerDialog("Generate terrain", 200, 50, 300, 420);
    dialog = getDialog("Generate terrain");
    dialogSetNumberElements(dialog, 2, 1, 2, 0);
    dialog->font = font;

    registerDialog("Object", 200, 50, 320, 250);
    dialog = getDialog("Object");
    dialogSetNumberElements(dialog, 2, 3, 0, 1);
    dialog->font = font;

    registerDialog("View", 200, 50, 440, 170);
    dialog = getDialog("View");
    dialogSetNumberElements(dialog, 1, 9, 0, 0);
    dialog->font = font;

    registerDialog("Replace", 200, 50, 500, 290);
    dialog = getDialog("Replace");
    dialogSetNumberElements(dialog, 3, 8, 2, 3);
    dialog->font = font;

    registerDialog("Global replace", 200, 50, 500, 290);
    dialog = getDialog("Global replace");
    dialogSetNumberElements(dialog, 3, 8, 2, 3);
    dialog->font = font;

    registerDialog("Rotation", 200, 50, 360, 210);
    dialog = getDialog("Rotation");
    dialogSetNumberElements(dialog, 1, 6, 0, 0);
    dialog->font = font;

    registerDialog("Error", 200, 200, 270, 600);
    dialog = getDialog("Error");
    dialogSetNumberElements(dialog, 1, 0, 0, 0);
    dialog->font = font;
}

Dialog *loadDialog(char *dialogName, Font *font) {
    Dialog *dialog = NULL;
    //dialog->buttons = loadButtons(dialogName);
    //dialog->checkBoxes = loadCheckBoxes(dialogName);
    //dialog->textBoxes = loadTextBoxes(dialogName);
    //dialog->texts = loadTexts(dialogName);
    dialog->font = font;

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
        //dialog = *(dialogs + i);
        //freeButtons(dialog);
        //freeCheckBoxes(dialog);
        //freeTextBoxes(dialog);
        //freeTexts(dialog);
    }

    free(registeredDialogs);
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
