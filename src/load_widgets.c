#include <stdlib.h>

#include "menus.h"
#include "load_widgets.h"
#include "load_widgets_fake.h"

//TODO Replace the fakes for real parsing
Dialog *loadDialog(char *dialogName) {
    Dialog *dialog = loadDialogFake(dialogName);
    dialog->buttons = loadButtons(dialogName);
    dialog->checkBoxes = loadCheckBoxes(dialogName);
    dialog->textBoxes = loadTextBoxes(dialogName);

    return dialog;
}

Button *loadButtons(char *dialogName) {
    //return loadButtonsFake(dialogName);
    return NULL;
}

CheckBox *loadCheckBoxes(char *dialogName) {
    //return loadCheckboxesFake(dialogName);
    return NULL;
}

TextBox *loadTextBoxes(char *dialogName) {
    //return loadTextBoxesFake(dialogName);
    return NULL;
}
