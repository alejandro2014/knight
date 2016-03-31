#ifndef LOAD_WIDGETS_H
#define LOAD_WIDGETS_H

#include <string.h>

#include "menus.h"

#define NUM_DIALOGS 8

void loadDialogs(Font *font);
void addButtonToDialog(char *dialogName, char *buttonName, int x, int y, int w, int h);
void addCheckboxToDialog(char *dialogName, char *checkBoxName, int x, int y);
void addTextBoxToDialog(char *dialogName, char *textBoxName, int x, int y, int w);
void addTextToDialog(char *dialogName, char *textName, int x, int y);

void freeDialogs();

#endif
