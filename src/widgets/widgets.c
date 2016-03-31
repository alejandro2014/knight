#include <stdio.h>
#include <stdlib.h>

#include "menus.h"
#include "widgets.h"
#include "load_widgets_fake.h"

#include "../draw.h"

extern Dialog *registeredDialogs;

//TODO Replace the fakes for real parsing
void loadDialogs(Font *font) {
    Dialog *dialog = NULL;
    allocExist(registeredDialogs, Dialog, NUM_DIALOGS);

    registerDialog("New terrain", 200, 100, 350, 250);
    dialog = getDialog("New terrain");
    dialog->font = font;
    addButtonToDialog("New terrain", "Ok", 40, 60, 20, 14);
    addButtonToDialog("New terrain", "Cancel", 70, 60, 50, 14);
    addCheckboxToDialog("New terrain", "Overwrite existing terrain", 2, 40);

    registerDialog("Generate terrain", 200, 50, 300, 420);
    dialog = getDialog("Generate terrain");
    dialog->font = font;
    addButtonToDialog("Generate terrain", "Ok", 40, 80, 20, 14);
    addButtonToDialog("Generate terrain", "Cancel", 70, 80, 50, 14);

    registerDialog("Object", 200, 50, 320, 250);
    dialog = getDialog("Object");
    dialog->font = font;
    addButtonToDialog("Object", "Ok", 60, 100, 20, 14);
    addButtonToDialog("Object", "Cancel", 90, 100, 50, 14);
    addCheckboxToDialog("Object", "Place over terrain", 40, 40);
    addCheckboxToDialog("Object", "Increase terrain", 40, 60);
    addCheckboxToDialog("Object", "Decrease terrain", 40, 80);

    registerDialog("View", 200, 50, 440, 170);
    dialog = getDialog("View");
    dialog->font = font;
    addButtonToDialog("View", "Ok", 50, 220, 20, 14);
    addCheckboxToDialog("View", "Toolbar", 2, 20);
    addCheckboxToDialog("View", "Minimap", 2, 40);
    addCheckboxToDialog("View", "Status bar", 2, 60);
    addCheckboxToDialog("View", "Grid: Off", 2, 80);
    //groupCheckbox "Grid"
    addCheckboxToDialog("View", "16x16", 2, 100);
    addCheckboxToDialog("View", "32x32", 2, 120);
    addCheckboxToDialog("View", "64x64", 2, 140);
    addCheckboxToDialog("View", "128x128", 2, 160);
    addCheckboxToDialog("View", "256x256", 2, 180);

    registerDialog("Replace", 200, 50, 500, 290);
    dialog = getDialog("Replace");
    dialog->font = font;
    addButtonToDialog("Replace", "Ok", 30, 280, 20, 14);
    addButtonToDialog("Replace", "Cancel", 60, 280, 50, 14);
    addButtonToDialog("Replace", "Change pattern", 120, 280, 110, 14);
    addCheckboxToDialog("Replace", "+", 40, 60);
    addCheckboxToDialog("Replace", "-", 40, 80);
    addCheckboxToDialog("Replace", "+/-", 40, 100);
    addCheckboxToDialog("Replace", "+", 40, 140);
    addCheckboxToDialog("Replace", "-", 40, 160);
    addCheckboxToDialog("Replace", "=", 40, 180);
    addCheckboxToDialog("Replace", "Solid", 40, 220);
    addCheckboxToDialog("Replace", "Pattern", 40, 240);

    registerDialog("Global replace", 200, 50, 500, 290);
    dialog = getDialog("Global replace");
    dialog->font = font;
    addButtonToDialog("Global replace", "Ok", 30, 280, 20, 14);
    addButtonToDialog("Global replace", "Cancel", 60, 280, 50, 14);
    addButtonToDialog("Global replace", "Change pattern", 120, 280, 110, 14);
    addCheckboxToDialog("Global replace", "+", 40, 60);
    addCheckboxToDialog("Global replace", "-", 40, 80);
    addCheckboxToDialog("Global replace", "+/-", 40, 100);
    addCheckboxToDialog("Global replace", "+", 40, 140);
    addCheckboxToDialog("Global replace", "-", 40, 160);
    addCheckboxToDialog("Global replace", "=", 40, 180);
    addCheckboxToDialog("Global replace", "Solid", 40, 220);
    addCheckboxToDialog("Global replace", "Pattern", 40, 240);

    registerDialog("Rotation", 200, 50, 360, 210);
    dialog = getDialog("Rotation");
    dialog->font = font;
    addButtonToDialog("Rotation", "Ok", 70, 140, 20, 14);
    addCheckboxToDialog("Rotation", "Horizontal (x) flip", 2, 20);
    addCheckboxToDialog("Rotation", "Vertical (y) flip", 2, 40);
    addCheckboxToDialog("Rotation", "Height (z) flip", 2, 60);
    addCheckboxToDialog("Rotation", "Rotate 90 CW", 2, 80);
    addCheckboxToDialog("Rotation", "Rotate 90 CCW", 2, 100);
    addCheckboxToDialog("Rotation", "Rotate 180 CCW", 2, 120);

    registerDialog("Error", 200, 200, 270, 600);
    dialog = getDialog("Error");
    dialog->font = font;
    addButtonToDialog("Error", "Ok", 200, 52, 20, 14);
}

void addButtonToDialog(char *dialogName, char *buttonName, int x, int y, int w, int h) {
    Dialog *dialog = getDialog(dialogName);
    Button *button = dialog->buttons + dialog->numButtons;

    setRect(&button->coords, x, y, x + w, y + h);
    button->title = buttonName;

    dialog->numButtons++;
}

void addCheckboxToDialog(char *dialogName, char *checkBoxName, int x, int y) {
    Dialog *dialog = getDialog(dialogName);
    CheckBox *checkBox = dialog->checkBoxes + dialog->numCheckBoxes;
    int checkboxSize = 14;

    setRect(&checkBox->coords, x, y, x + checkboxSize, y + checkboxSize);
    checkBox->text = checkBoxName;

    dialog->numCheckBoxes++;
}

void freeDialogs() {
    Dialog *dialog = NULL;
    int i;

    for(i = 0; i < NUM_DIALOGS; i++) {
        dialog = registeredDialogs + i;
        free(dialog->buttons);
        free(dialog->checkBoxes);
        free(dialog->textBoxes);
        free(dialog->texts);
    }

    free(registeredDialogs);
}
