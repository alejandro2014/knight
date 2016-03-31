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

Text **loadTextsFake(char *dialogName) {
    Text **texts = NULL;

    if(!strcmp(dialogName, "newTerrain")) {
    } else if(!strcmp(dialogName, "generateTerrain")) {
    } else if(!strcmp(dialogName, "object")) {
        texts = (Text **) malloc(sizeof(Text *) * 1);
        memset(texts, 0, sizeof(Text *) * 1);
        *(texts + 0) = loadTextFake("Put object mode:", 4, 22);
    } else if(!strcmp(dialogName, "view")) {
    } else if(!strcmp(dialogName, "replace")) {
        texts = (Text **) malloc(sizeof(Text *) * 3);
        memset(texts, 0, sizeof(Text *) * 3);
        *(texts + 0) = loadTextFake("Tolerance mode", 4, 42);
        *(texts + 1) = loadTextFake("Replace mode", 4, 122);
        *(texts + 2) = loadTextFake("Replace with:", 4, 202);
    } else if(!strcmp(dialogName, "globalReplace")) {
        texts = (Text **) malloc(sizeof(Text *) * 3);
        memset(texts, 0, sizeof(Text *) * 3);
        *(texts + 0) = loadTextFake("Tolerance mode", 4, 42);
        *(texts + 1) = loadTextFake("Replace mode", 4, 122);
        *(texts + 2) = loadTextFake("Replace with:", 4, 202);
    } else if(!strcmp(dialogName, "rotation")) {
    } else if(!strcmp(dialogName, "error")) {
        //*(texts + 0) = loadTextFake(&error_msg_1, , );
        //*(texts + 1) = loadTextFake(&error_msg_2, , );
    } else if(!strcmp(dialogName, "file")) {
        texts = (Text **) malloc(sizeof(Text *) * 2);
        memset(texts, 0, sizeof(Text *) * 2);
        *(texts + 0) = loadTextFake("<<", 4, -34);
        *(texts + 1) = loadTextFake(">>", 0, 334);
    }

	return texts;
}

TextBox **loadTextBoxesFake(char *dialogName) {
    TextBox **textBoxes = NULL;

    if(!strcmp(dialogName, "newTerrain")) {
    	textBoxes = (TextBox **) malloc(sizeof(TextBox *) * 3);
        memset(textBoxes, 0, sizeof(TextBox *) * 3);

        *(textBoxes + 0) = loadTextBoxFake("X Size:", 2, 2, 42, 14);
    	*(textBoxes + 1) = loadTextBoxFake("Y Size:", 2, 22, 42, 14);
        *(textBoxes + 2) = loadTextBoxFake("Base Height:", 2, 42, 24, 14);
    } else if(!strcmp(dialogName, "generateTerrain")) {
        textBoxes = (TextBox **) malloc(sizeof(TextBox *) * 2);
        memset(textBoxes, 0, sizeof(TextBox *) * 2);
        *(textBoxes + 0) = loadTextBoxFake("Seed", 52, 18, 76, 14);
    	*(textBoxes + 1) = loadTextBoxFake("Random", 140, 18, 50, 14);
    } else if(!strcmp(dialogName, "object")) {
    } else if(!strcmp(dialogName, "view")) {
    } else if(!strcmp(dialogName, "replace")) {
        textBoxes = (TextBox **) malloc(sizeof(TextBox *) * 2);
        memset(textBoxes, 0, sizeof(TextBox *) * 2);
        *(textBoxes + 0) = loadTextBoxFake("Tolerance:", 2, 20, 25, 14); //numeric_dialog_boxes[tolerance].dialog_text
        *(textBoxes + 1) = loadTextBoxFake("Pattern:", 2, 262, 172, 14); //current_pattern.object_mem ? &pattern_file_name : "None";
    } else if(!strcmp(dialogName, "globalReplace")) {
        textBoxes = (TextBox **) malloc(sizeof(TextBox *) * 2);
        memset(textBoxes, 0, sizeof(TextBox *) * 2);
        *(textBoxes + 0) = loadTextBoxFake("Tolerance:", 2, 20, 25, 14); //numeric_dialog_boxes[global_tolerance].dialog_text
        *(textBoxes + 1) = loadTextBoxFake("Pattern:", 2, 262, 172, 14); //current_pattern.object_mem ? &pattern_file_name : "None";
    } else if(!strcmp(dialogName, "rotation")) {
    } else if(!strcmp(dialogName, "error")) {
    } else if(!strcmp(dialogName, "file")) {
        //*(texts + 0) = loadTextFake(&cur_file_name, , );
    }

	return textBoxes;
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
