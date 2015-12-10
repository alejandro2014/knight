#ifndef LOAD_WIDGETS_FAKE_H
#define LOAD_WIDGETS_FAKE_H

#include "menus.h"

Dialog *loadDialogFake(char *dialogName);
Dialog *loadDialogFake2(char *title, int x, int y, int width, int height);

TextBox **loadTextBoxesFake(char *dialogName);
CheckBox **loadCheckBoxesFake(char *dialogName);
Button **loadButtonsFake(char *dialogName);
Text **loadTextsFake(char *dialogName);

Text *loadTextFake(char *string, int x, int y);
TextBox *loadTextBoxFake(char *text, int x, int y, int width, int height);
CheckBox *loadCheckBoxFake(char *text, int x, int y, int width, int height);
Button *loadButtonFake(char *text, int x, int y, int width, int height);
/*ButtonContainer *loadButtonContainer(Menu *menu);
TextBoxContainer *loadTextBoxContainer(Menu *menu);*/

#endif
