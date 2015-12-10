#ifndef LOAD_WIDGETS_H
#define LOAD_WIDGETS_H

#define NUM_DIALOGS 8

Dialog **loadDialogs();
Button **loadButtons(char *dialogName);
TextBox **loadTextBoxes(char *dialogName);
CheckBox **loadCheckBoxes(char *dialogName);
Text **loadTexts(char *dialogName);

#endif
