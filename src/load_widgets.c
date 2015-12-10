#include <stdio.h>
#include <stdlib.h>

#include "menus.h"
#include "load_widgets.h"
#include "load_widgets_fake.h"

//TODO Replace the fakes for real parsing
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
