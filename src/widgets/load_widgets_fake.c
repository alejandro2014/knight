#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "load_widgets_fake.h"

Dialog *loadDialogFake(char *dialogName) {
    Dialog *dialog = NULL;

    if(!strcmp(dialogName, "newTerrain")) {
        dialog = loadDialogFake2("New terrain", 200, 100, 100, 150);
        dialog->numButtons = 2;
        dialog->numCheckBoxes = 0;
        dialog->numTextBoxes = 3;
        dialog->numTexts = 0;
    } else if(!strcmp(dialogName, "generateTerrain")) {
        dialog = loadDialogFake2("Generate terrain", 200, 50, 100, 220);
        dialog->numButtons = 2;
        dialog->numCheckBoxes = 1;
        dialog->numTextBoxes = 2;
        dialog->numTexts = 0;
    } else if(!strcmp(dialogName, "object")) {
        dialog = loadDialogFake2("Object", 200, 50, 120, 200);
        dialog->numButtons = 2;
        dialog->numCheckBoxes = 3;
        dialog->numTextBoxes = 0;
        dialog->numTexts = 1;
    } else if(!strcmp(dialogName, "view")) {
        dialog = loadDialogFake2("View", 200, 50, 240, 120);
        dialog->numButtons = 1;
        dialog->numCheckBoxes = 9;
        dialog->numTextBoxes = 0;
        dialog->numTexts = 0;
    } else if(!strcmp(dialogName, "replace")) {
        dialog = loadDialogFake2("Replace", 200, 50, 300, 240);
        dialog->numButtons = 3;
        dialog->numCheckBoxes = 8;
        dialog->numTextBoxes = 2;
        dialog->numTexts = 3;
    } else if(!strcmp(dialogName, "globalReplace")) {
        dialog = loadDialogFake2("Global replace", 200, 50, 300, 240);
        dialog->numButtons = 3;
        dialog->numCheckBoxes = 8;
        dialog->numTextBoxes = 2;
        dialog->numTexts = 3;
    } else if(!strcmp(dialogName, "rotation")) {
        dialog = loadDialogFake2("Rotation", 200, 50, 160, 160);
        dialog->numButtons = 1;
        dialog->numCheckBoxes = 6;
        dialog->numTextBoxes = 0;
        dialog->numTexts = 0;
    } else if(!strcmp(dialogName, "error")) {
        dialog = loadDialogFake2("Error", 200, 200, 70, 400);
        dialog->numButtons = 1;
        dialog->numCheckBoxes = 0;
        dialog->numTextBoxes = 0;
        dialog->numTexts = 0;
    }

    dialog->name = dialogName;

    return dialog;
}

Dialog *loadDialogFake2(char *title, int x, int y, int width, int height) {
    alloc(dialog, Dialog, 1);
    allocExist(dialog->coords, SDL_Rect, 1);

    dialog->coords->x = x;
    dialog->coords->y = y;
    dialog->coords->w = width;
    dialog->coords->h = height;
    dialog->title = title;

    //printf("    * Loaded dialog (%s, %d, %d, %d, %d)\n", title, x, y, width, height);

    return dialog;
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

CheckBox **loadCheckBoxesFake(char *dialogName) {
    int numCheckBoxes = 0;
    CheckBox **checkBoxes = NULL;

    if(!strcmp(dialogName, "newTerrain")) {
    } else if(!strcmp(dialogName, "generateTerrain")) {
        checkBoxes = (CheckBox **) malloc(sizeof(CheckBox *) * 1);
    	memset(checkBoxes, 0, sizeof(CheckBox) * 1);
        *(checkBoxes + 0) = loadCheckBoxFake("Overwrite existing terrain", 2, 40, 14, 14);
    } else if(!strcmp(dialogName, "object")) {
        checkBoxes = (CheckBox **) malloc(sizeof(CheckBox *) * 3);
    	memset(checkBoxes, 0, sizeof(CheckBox) * 3);
        *(checkBoxes + 0) = loadCheckBoxFake("Place over terrain", 40, 40, 14, 14);
      	*(checkBoxes + 1) = loadCheckBoxFake("Increase terrain", 40, 60, 14, 14);
      	*(checkBoxes + 2) = loadCheckBoxFake("Decrease terrain", 40, 80, 14, 14);
    } else if(!strcmp(dialogName, "view")) {
        checkBoxes = (CheckBox **) malloc(sizeof(CheckBox *) * 9);
    	memset(checkBoxes, 0, sizeof(CheckBox) * 9);
        *(checkBoxes + 0) = loadCheckBoxFake("Toolbar", 2, 20, 14, 14);
        *(checkBoxes + 1) = loadCheckBoxFake("Minimap", 2, 40, 14, 14);
    	*(checkBoxes + 2) = loadCheckBoxFake("Status bar", 2, 60, 14, 14);
    	*(checkBoxes + 3) = loadCheckBoxFake("Grid: Off", 2, 80, 14, 14);
    	//groupCheckbox "Grid"
    	*(checkBoxes + 4) = loadCheckBoxFake("16x16", 2, 100, 14, 14);
    	*(checkBoxes + 5) = loadCheckBoxFake("32x32", 2, 120, 14, 14);
    	*(checkBoxes + 6) = loadCheckBoxFake("64x64", 2, 140, 14, 14);
    	*(checkBoxes + 7) = loadCheckBoxFake("128x128", 2, 160, 14, 14);
    	*(checkBoxes + 8) = loadCheckBoxFake("256x256", 2, 180, 14, 14);
    } else if(!strcmp(dialogName, "replace")) {
        checkBoxes = (CheckBox **) malloc(sizeof(CheckBox *) * 8);
    	memset(checkBoxes, 0, sizeof(CheckBox) * 8);
        *(checkBoxes + 0) = loadCheckBoxFake("+", 40, 60, 14, 14);
    	*(checkBoxes + 1) = loadCheckBoxFake("-", 40, 80, 14, 14);
    	*(checkBoxes + 2) = loadCheckBoxFake("+/-", 40, 100, 14, 14);

        *(checkBoxes + 3) = loadCheckBoxFake("+", 40, 140, 14, 14);
    	*(checkBoxes + 4) = loadCheckBoxFake("-", 40, 160, 14, 14);
    	*(checkBoxes + 5) = loadCheckBoxFake("=", 40, 180, 14, 14);

        *(checkBoxes + 6) = loadCheckBoxFake("Solid", 40, 220, 14, 14);
    	*(checkBoxes + 7) = loadCheckBoxFake("Pattern", 40, 240, 14, 14);
    } else if(!strcmp(dialogName, "globalReplace")) {
        checkBoxes = (CheckBox **) malloc(sizeof(CheckBox *) * 8);
    	memset(checkBoxes, 0, sizeof(CheckBox) * 8);
        *(checkBoxes + 0) = loadCheckBoxFake("+", 40, 60, 14, 14);
    	*(checkBoxes + 1) = loadCheckBoxFake("-", 40, 80, 14, 14);
    	*(checkBoxes + 2) = loadCheckBoxFake("+/-", 40, 100, 14, 14);

    	*(checkBoxes + 3) = loadCheckBoxFake("+", 40, 140, 14, 14);
    	*(checkBoxes + 4) = loadCheckBoxFake("-", 40, 160, 14, 14);
    	*(checkBoxes + 5) = loadCheckBoxFake("=", 40, 180, 14, 14);

        *(checkBoxes + 6) = loadCheckBoxFake("Solid", 40, 220, 14, 14);
      	*(checkBoxes + 7) = loadCheckBoxFake("Pattern", 40, 240, 14, 14);
    } else if(!strcmp(dialogName, "rotation")) {
        checkBoxes = (CheckBox **) malloc(sizeof(CheckBox *) * 6);
    	memset(checkBoxes, 0, sizeof(CheckBox) * 6);
        *(checkBoxes + 0) = loadCheckBoxFake("Horizontal (x) flip", 2, 20, 14, 14);
        *(checkBoxes + 1) = loadCheckBoxFake("Vertical (y) flip", 2, 40, 14, 14);
        *(checkBoxes + 2) = loadCheckBoxFake("Height (z) flip", 2, 60, 14, 14);
        *(checkBoxes + 3) = loadCheckBoxFake("Rotate 90 CW", 2, 80, 14, 14);
        *(checkBoxes + 4) = loadCheckBoxFake("Rotate 90 CCW", 2, 100, 14, 14);
        *(checkBoxes + 5) = loadCheckBoxFake("Rotate 180 CCW", 2, 120, 14, 14);
    } else if(!strcmp(dialogName, "error")) {
    }

	return checkBoxes;
}

Button **loadButtonsFake(char *dialogName) {
    Button **buttons = NULL;

    if(!strcmp(dialogName, "newTerrain")) {
        buttons = (Button **) malloc(sizeof(Button *) * 2);
    	memset(buttons, 0, sizeof(Button *) * 2);
        *(buttons + 0) = loadButtonFake("Ok", 40, 60, 20, 14);
    	*(buttons + 1) = loadButtonFake("Cancel", 70, 60, 50, 14);
    } else if(!strcmp(dialogName, "generateTerrain")) {
        buttons = (Button **) malloc(sizeof(Button *) * 2);
    	memset(buttons, 0, sizeof(Button *) * 2);
        *(buttons + 0) = loadButtonFake("Ok", 40, 80, 20, 14);
      	*(buttons + 1) = loadButtonFake("Cancel", 70, 80, 50, 14);
    } else if(!strcmp(dialogName, "object")) {
        buttons = (Button **) malloc(sizeof(Button *) * 2);
    	memset(buttons, 0, sizeof(Button *) * 2);
        *(buttons + 0) = loadButtonFake("Ok", 60, 100, 20, 14);
      	*(buttons + 1) = loadButtonFake("Cancel", 90, 100, 50, 14);
    } else if(!strcmp(dialogName, "view")) {
        buttons = (Button **) malloc(sizeof(Button *) * 1);
    	memset(buttons, 0, sizeof(Button *) * 1);
        *(buttons + 0) = loadButtonFake("Ok", 50, 220, 20, 14);
    } else if(!strcmp(dialogName, "replace")) {
        buttons = (Button **) malloc(sizeof(Button *) * 3);
    	memset(buttons, 0, sizeof(Button *) * 3);
        *(buttons + 0) = loadButtonFake("Ok", 30, 280, 20, 14);
    	*(buttons + 1) = loadButtonFake("Cancel", 60, 280, 50, 14);
    	*(buttons + 2) = loadButtonFake("Change pattern", 120, 280, 110, 14);
    } else if(!strcmp(dialogName, "globalReplace")) {
        buttons = (Button **) malloc(sizeof(Button *) * 3);
    	memset(buttons, 0, sizeof(Button *) * 3);
        *(buttons + 0) = loadButtonFake("Ok", 30, 280, 20, 14);
    	*(buttons + 1) = loadButtonFake("Cancel", 60, 280, 50, 14);
    	*(buttons + 2) = loadButtonFake("Change pattern", 120, 280, 110, 14);
    } else if(!strcmp(dialogName, "rotation")) {
        buttons = (Button **) malloc(sizeof(Button *) * 1);
    	memset(buttons, 0, sizeof(Button *) * 1);
        *(buttons + 0) = loadButtonFake("Ok", 70, 140, 20, 14);
    } else if(!strcmp(dialogName, "error")) {
        buttons = (Button **) malloc(sizeof(Button *) * 1);
    	memset(buttons, 0, sizeof(Button *) * 1);
        *(buttons + 0) = loadButtonFake("Ok", 200, 52, 20, 14);
    } else if(!strcmp(dialogName, "file")) {
        buttons = (Button **) malloc(sizeof(Button *) * 2);
    	memset(buttons, 0, sizeof(Button *) * 2);
        *(buttons + 0) = loadButtonFake("Ok", 200, 52, 20, 14); //Ok/save
        *(buttons + 1) = loadButtonFake("Cancel", 200, 52, 20, 14);
    }

	return buttons;
}

Text *loadTextFake(char *string, int x, int y) {
    alloc(text, Text, 1);
    allocExist(text->coords, SDL_Rect, 1);

    text->string = string;
    text->coords->x = x;
    text->coords->y = y;

    //printf("    * Loaded text (%s, %d, %d)\n", string, x, y);
    return text;
}

TextBox *loadTextBoxFake(char *text, int x, int y, int width, int height) {
    alloc(textBox, TextBox, 1);
    allocExist(textBox->coords, SDL_Rect, 1);

	textBox->title = text;
    textBox->coords->x = x;
    textBox->coords->y = y;
    textBox->coords->w = width;
    textBox->coords->h = height;

    //printf("    * Loaded textBox (%s, %d, %d, %d, %d)\n", text, x, y, width, height);
    return textBox;
}

CheckBox *loadCheckBoxFake(char *text, int x, int y, int width, int height) {
    alloc(checkBox, CheckBox, 1);
    allocExist(checkBox->coords, SDL_Rect, 1);

    checkBox->text = text;
    checkBox->coords->x = x;
    checkBox->coords->y = y;
    checkBox->coords->w = width;
    checkBox->coords->h = height;

    //printf("    * Loaded checkBox (%s, %d, %d, %d, %d)\n", text, x, y, width, height);
    return checkBox;
}

Button *loadButtonFake(char *text, int x, int y, int width, int height) {
    alloc(button, Button, 1);
    allocExist(button->coords, SDL_Rect, 1);

    button->title = text;
    button->coords->x = x;
    button->coords->y = y;
    button->coords->w = width;
    button->coords->h = height;

    //printf("    * Loaded button (%s, %d, %d, %d, %d)\n", text, x, y, width, height);
    return button;
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
