#ifndef LOAD_WIDGETS_H
#define LOAD_WIDGETS_H

#include <string.h>

#include "menus.h"

#define NUM_DIALOGS 8

Dialog **loadDialogs(Font *font);
Button **loadButtons(char *dialogName);
TextBox **loadTextBoxes(char *dialogName);
CheckBox **loadCheckBoxes(char *dialogName);
Text **loadTexts(char *dialogName);

void freeDialogs(Dialog **dialogs);
void freeButtons(Dialog *dialog);
void freeCheckBoxes(Dialog *dialog);
void freeTextBoxes(Dialog *dialog);
void freeTexts(Dialog *dialog);

#endif
