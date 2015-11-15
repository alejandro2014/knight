#ifndef LOAD_WIDGETS_H
#define LOAD_WIDGETS_H

Menu *loadMenus(char *nameOfFile);

Menu *loadMenu(char *dialog);
Menu *loadNewTerrainDialog();
Menu *loadGenerateTerrainDialog();

Button *loadButtons(Menu *menu);
TextBox *loadTextBoxes(Menu *menu);

ButtonContainer *loadButtonContainer(Menu *menu);
TextBoxContainer *loadTextBoxContainer(Menu *menu);
#endif
