#ifndef LOAD_WIDGETS_FAKE_H
#define LOAD_WIDGETS_FAKE_H

#include "menus.h"

TextBox **loadTextBoxesFake(char *dialogName);
CheckBox **loadCheckBoxesFake(char *dialogName);
Button **loadButtonsFake(char *dialogName);
Text **loadTextsFake(char *dialogName);

Text *loadTextFake(char *string, int x, int y);
TextBox *loadTextBoxFake(char *text, int x, int y, int width, int height);
CheckBox *loadCheckBoxFake(char *text, int x, int y, int width, int height);
Button *loadButtonFake(char *text, int x, int y, int width, int height);


void registerDialog(char *dialogName, int x1, int y1, int x2, int y2);
Dialog *getDialog(char *dialogName);
void dialogSetNumberElements(Dialog *dialog, int numButtons, int numCheckBoxes, int numTextBoxes, int numTexts);

void allocateDialogWidgets(Dialog *dialog);

#endif
