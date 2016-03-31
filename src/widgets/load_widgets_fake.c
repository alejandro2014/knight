#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "widgets.h"
#include "load_widgets_fake.h"

#include "../draw.h"

Dialog *registeredDialogs = NULL;
int currentRegDialog = 0;

void registerDialog(char *dialogName, int x1, int y1, int x2, int y2) {
    Dialog *dialog = getDialog(dialogName);

    dialog = registeredDialogs + currentRegDialog;
    dialog->name = dialogName;
    dialog->title = dialogName;
    setRect(&dialog->coords, x1, y1, x2, y2);
    currentRegDialog++;

    allocateDialogWidgets(dialog);
}

Dialog *getDialog(char *dialogName) {
    Dialog *dialog = NULL;
    int i;

    for(i = 0; i < NUM_DIALOGS; i++) {
        dialog = registeredDialogs + i;
        if(!dialog->name) return NULL;
        if(!strcmp(dialogName, dialog->name)) return dialog;
    }

    return NULL;
}

void dialogSetNumberElements(Dialog *dialog, int numButtons, int numCheckBoxes, int numTextBoxes, int numTexts) {
    dialog->numButtons = numButtons;
    dialog->numCheckBoxes = numCheckBoxes;
    dialog->numTextBoxes = numTextBoxes;
    dialog->numTexts = numTexts;
}

void allocateDialogWidgets(Dialog *dialog) {
    int maxElements = 20;

    allocExist(dialog->buttons, Button, maxElements);
    allocExist(dialog->checkBoxes, CheckBox, maxElements);
    allocExist(dialog->textBoxes, TextBox, maxElements);
    allocExist(dialog->texts, Text, maxElements);
}

Text *loadTextFake(char *string, int x, int y) {
    alloc(text, Text, 1);

    text->string = string;
    setRect(&text->coords, x, y, 0, 0);

    return text;
}

TextBox *loadTextBoxFake(char *text, int x, int y, int width, int height) {
    alloc(textBox, TextBox, 1);

	textBox->title = text;
    setRect(&textBox->coords, x, y, x + width, y + height);

    return textBox;
}

CheckBox *loadCheckBoxFake(char *text, int x, int y, int width, int height) {
    alloc(checkBox, CheckBox, 1);

    checkBox->text = text;
    setRect(&checkBox->coords, x, y, x + width, y + height);

    return checkBox;
}

/*ButtonContainer *loadButtonContainer(Menu *menu) {
	ButtonContainer *buttonContainer = (ButtonContainer *) malloc(sizeof(ButtonContainer));
	memset(buttonContainer, 0, sizeof(ButtonContainer));

    buttonContainer->buttonsNo = 2;
	buttonContainer->buttons = loadButtons(menu);

	return buttonContainer;
    return NULL;
}

TextBoxContainer *loadTextBoxContainer(Menu *menu) {
	TextBoxContainer *textBoxContainer = (TextBoxContainer *) malloc(sizeof(TextBoxContainer));
	memset(textBoxContainer, 0, sizeof(TextBoxContainer));

    textBoxContainer->textBoxesNo = 3;
	textBoxContainer->textBoxes = loadTextBoxes(menu);

	return textBoxContainer;
    return NULL;
}*/
