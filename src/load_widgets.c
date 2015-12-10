#include <stdio.h>
#include <stdlib.h>

#include "menus.h"
#include "load_widgets.h"
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
    printf("[INFO] ===== Load dialog %s =====\n", dialogName);
    Dialog *dialog = loadDialogFake(dialogName);
    dialog->buttons = loadButtons(dialogName);
    dialog->checkBoxes = loadCheckBoxes(dialogName);
    dialog->textBoxes = loadTextBoxes(dialogName);
    dialog->texts = loadTexts(dialogName);

    return dialog;
}

Button **loadButtons(char *dialogName) {
    printf("[INFO] Load buttons %s\n", dialogName);
    return loadButtonsFake(dialogName);
}

CheckBox **loadCheckBoxes(char *dialogName) {
    printf("[INFO] Load checkBoxes %s\n", dialogName);
    return loadCheckBoxesFake(dialogName);
}

TextBox **loadTextBoxes(char *dialogName) {
    printf("[INFO] Load textBoxes %s\n", dialogName);
    return loadTextBoxesFake(dialogName);
}

Text **loadTexts(char *dialogName) {
    printf("[INFO] Load texts %s\n", dialogName);
    return loadTextsFake(dialogName);
}

void freeDialogs(Dialog **dialogs) {
    Dialog *dialog = NULL;
    int i;

    for(i = 0; i < NUM_DIALOGS; i++) {
        dialog = *(dialogs + i);
        /*freeTextBoxes(dialog->textBoxes);
        freeTexts(dialog->texts);
        freeCheckBoxes(dialog->checkBoxes);
        freeButtons(dialog->buttons);*/
    }
}

void freeTextBoxes(TextBox **textBoxes) {

}

void freeTexts(Text **texts) {

}

void freeCheckBoxes(CheckBox **checkBoxes) {

}
