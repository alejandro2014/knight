#ifndef LOAD_WIDGETS_H
#define LOAD_WIDGETS_H

Menu *loadMenu(char *dialog);
Button *loadButtons(Menu *menu);
TextBox *loadTextBoxes(Menu *menu);

ButtonContainer *loadButtonContainer(Menu *menu);
TextBoxContainer *loadTextBoxContainer(Menu *menu);
#endif
