#include "menus.h"
#include "load_widgets.h"

//TODO Replace the fakes for real parsing
Dialog *loadDialog(char *dialogName) {
    Dialog *dialog = loadDialogFake(dialogName);
    dialog->buttons = loadButtons(dialogName);
    dialog->checkboxes = loadCheckBoxes(dialogName);
    dialog->textboxes = loadTextBoxes(dialogName);

    return dialog
}

Button *loadButtons(char *dialogName) {
    return loadButtonsFake(dialogName);
}

Checkbox *loadCheckboxes(char *dialogName) {
    return loadCheckboxesFake(dialogName);
}

TextBox *loadTextBoxes(char *dialogName) {
    return loadTextBoxesFake(dialogName);
}
