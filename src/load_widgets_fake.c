#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "load_widgets_fake.h"

Dialog *loadDialogFake(char *dialogName) {
    Dialog *dialog = NULL;

    if(!strcmp(dialogName, "newTerrain")) {
        dialog = loadDialogFake2("New terrain", 200, 100, 100, 150);
    } else if(!strcmp(dialogName, "generateTerrain")) {
        dialog = loadDialogFake2("Generate terrain", 200, 50, 100, 220);
    } else if(!strcmp(dialogName, "object")) {
        dialog = loadDialogFake2("Object", 200, 50, 120, 200);
    } else if(!strcmp(dialogName, "view")) {
        dialog = loadDialogFake2("View", 200, 50, 240, 120);
    } else if(!strcmp(dialogName, "replace")) {
        dialog = loadDialogFake2("Replace", 200, 50, 300, 240);
    } else if(!strcmp(dialogName, "globalReplace")) {
        dialog = loadDialogFake2("Global replace", 200, 50, 300, 240);
    } else if(!strcmp(dialogName, "rotation")) {
        dialog = loadDialogFake2("Rotation", 200, 50, 160, 160);
    } else if(!strcmp(dialogName, "error")) {
        dialog = loadDialogFake2("Error", 200, 200, 70, 400);
    }

    return dialog;
}

Dialog *loadDialogFake2(char *title, int x, int y, int width, int height) {
  Dialog *dialog = (Dialog *) malloc(sizeof(Dialog));
  memset(dialog, 0, sizeof(Dialog));

  dialog->x = x;
  dialog->y = y;
  dialog->width = width;
  dialog->height = height;
  dialog->title = title;

  printf("    * Loaded dialog (%s, %d, %d, %d, %d)\n", title, x, y, width, height);

  return dialog;
}

Text **loadTextsFake(char *dialogName, int numTexts) {
    /*Text **texts = (Text **) malloc(sizeof(Text *) * numTexts);
    memset(texts, 0, sizeof(Text *) * numTexts);

    if(!strcmp(dialogName, "newTerrain")) {

    } else if(!strcmp(dialogName, "generateTerrain")) {

    } else if(!strcmp(dialogName, "object")) {
        *(texts + 0) = loadTextFake("Put object mode:", 4, 22);
    } else if(!strcmp(dialogName, "view")) {
    } else if(!strcmp(dialogName, "replace")) {
        *(texts + 0) = loadTextFake("Tolerance mode", 4, 42);
        *(texts + 1) = loadTextFake("Replace mode", 4, 122);
        *(texts + 2) = loadTextFake("Replace with:", 4, 202);
    } else if(!strcmp(dialogName, "globalReplace")) {
        *(texts + 0) = loadTextFake("Tolerance mode", 4, 42);
        *(texts + 1) = loadTextFake("Replace mode", 4, 122);
        *(texts + 2) = loadTextFake("Replace with:", 4, 202);
    } else if(!strcmp(dialogName, "rotation")) {
    } else if(!strcmp(dialogName, "error")) {
        *(texts + 0) = loadTextFake(&error_msg_1, , );
        *(texts + 1) = loadTextFake(&error_msg_2, , );
    } else if(!strcmp(dialogName, "file")) {
        *(texts + 0) = loadTextFake("<<", 4, -34);
        *(texts + 1) = loadTextFake(">>", 0, 334);
    }

	return textBoxes;*/
    return NULL;
}

TextBox **loadTextBoxesFake(char *dialogName, int numTextboxes) {
	/*TextBox **textBoxes = (TextBox **) malloc(sizeof(TextBox *) * numTextboxes);
    memset(textBoxes, 0, sizeof(TextBox *) * numTextboxes);

    if(!strcmp(dialogName, "newTerrain")) {
        *(textBoxes + 0) = loadTextBoxFake("X Size:", 2, 2, 42, 14);
    	*(textBoxes + 1) = loadTextBoxFake("Y Size:", 2, 22, 42, 14);
        *(textBoxes + 2) = loadTextBoxFake("Base Height:", 2, 42, 24, 14);
    } else if(!strcmp(dialogName, "generateTerrain")) {
        *(textBoxes + 0) = loadTextBoxFake("Seed", 52, 18, 76, 14);
    	*(textBoxes + 1) = loadTextBoxFake("Random", 140, 18, 50, 14);
    } else if(!strcmp(dialogName, "object")) {
    } else if(!strcmp(dialogName, "view")) {
    } else if(!strcmp(dialogName, "replace")) {
        *(textBoxes + 0) = loadTextBoxFake("Tolerance:", 2, 20, 25, 14); //numeric_dialog_boxes[tolerance].dialog_text
        *(textBoxes + 1) = loadTextBoxFake("Pattern:", 2, 262, 172, 14); //current_pattern.object_mem ? &pattern_file_name : "None";
    } else if(!strcmp(dialogName, "globalReplace")) {
        *(textBoxes + 0) = loadTextBoxFake("Tolerance:", 2, 20, 25, 14); //numeric_dialog_boxes[global_tolerance].dialog_text
        *(textBoxes + 1) = loadTextBoxFake("Pattern:", 2, 262, 172, 14); //current_pattern.object_mem ? &pattern_file_name : "None";
    } else if(!strcmp(dialogName, "rotation")) {
    } else if(!strcmp(dialogName, "error")) {
    } else if(!strcmp(dialogName, "file")) {
        *(texts + 0) = loadTextFake(&cur_file_name, , );
    }

	return textBoxes;*/
    return NULL;
}

CheckBox **loadCheckBoxesFake(char *dialogName, int numCheckBoxes) {
	/*CheckBox **checkBoxes = (CheckBox **) malloc(sizeof(CheckBox *) * numCheckBoxes);
	memset(checkBoxes, 0, sizeof(CheckBox) * numCheckBoxes);

    if(!strcmp(dialogName, "newTerrain")) {
    } else if(!strcmp(dialogName, "generateTerrain")) {
        *(checkBoxes + 0) = loadCheckboxesFake("Overwrite existing terrain", 2, 40, 14, 14);
    } else if(!strcmp(dialogName, "object")) {
        *(checkBoxes + 0) = loadCheckboxesFake("Place over terrain", 40, 40, 14, 14);
      	*(checkBoxes + 1) = loadCheckboxesFake("Increase terrain", 40, 60, 14, 14);
      	*(checkBoxes + 2) = loadCheckboxesFake("Decrease terrain", 40, 80, 14, 14);
    } else if(!strcmp(dialogName, "view")) {
        *(checkBoxes + 0) = loadCheckboxesFake("Toolbar", 2, 20, 14, 14);
        *(checkBoxes + 1) = loadCheckboxesFake("Minimap", 2, 40, 14, 14);
    	*(checkBoxes + 2) = loadCheckboxesFake("Status bar", 2, 60, 14, 14);
    	*(checkBoxes + 3) = loadCheckboxesFake("Grid: Off", 2, 80, 14, 14);
    	//groupCheckbox "Grid"
    	*(checkBoxes + 0) = loadCheckboxesFake("16x16", 2, 100, 14, 14);
    	*(checkBoxes + 1) = loadCheckboxesFake("32x32", 2, 120, 14, 14);
    	*(checkBoxes + 2) = loadCheckboxesFake("64x64", 2, 140, 14, 14);
    	*(checkBoxes + 3) = loadCheckboxesFake("128x128", 2, 160, 14, 14);
    	*(checkBoxes + 4) = loadCheckboxesFake("256x256", 2, 180, 14, 14);
    } else if(!strcmp(dialogName, "replace")) {
        *(checkBoxes + 0) = loadCheckboxesFake("+", 40, 60, 14, 14);
    	*(checkBoxes + 1) = loadCheckboxesFake("-", 40, 80, 14, 14);
    	*(checkBoxes + 2) = loadCheckboxesFake("+/-", 40, 100, 14, 14);

        *(checkBoxes + 0) = loadCheckboxesFake("+", 40, 140, 14, 14);
    	*(checkBoxes + 1) = loadCheckboxesFake("-", 40, 160, 14, 14);
    	*(checkBoxes + 2) = loadCheckboxesFake("=", 40, 180, 14, 14);

        *(checkBoxes + 0) = loadCheckboxesFake("Solid", 40, 220, 14, 14);
    	*(checkBoxes + 1) = loadCheckboxesFake("Pattern", 40, 240, 14, 14);
    } else if(!strcmp(dialogName, "globalReplace")) {
        *(checkBoxes + 0) = loadCheckboxesFake("+", 40, 60, 14, 14);
    	*(checkBoxes + 1) = loadCheckboxesFake("-", 40, 80, 14, 14);
    	*(checkBoxes + 2) = loadCheckboxesFake("+/-", 40, 100, 14, 14);

    	*(checkBoxes + 0) = loadCheckboxesFake("+", 40, 140, 14, 14);
    	*(checkBoxes + 1) = loadCheckboxesFake("-", 40, 160, 14, 14);
    	*(checkBoxes + 2) = loadCheckboxesFake("=", 40, 180, 14, 14);

        *(checkBoxes + 0) = loadCheckboxesFake("Solid", 40, 220, 14, 14);
      	*(checkBoxes + 1) = loadCheckboxesFake("Pattern", 40, 240, 14, 14);
    } else if(!strcmp(dialogName, "rotation")) {
        *(checkBoxes + 0) = loadCheckboxesFake("Horizontal (x) flip", 2, 20, 14, 14);
        *(checkBoxes + 1) = loadCheckboxesFake("Vertical (y) flip", 2, 40, 14, 14);
        *(checkBoxes + 2) = loadCheckboxesFake("Height (z) flip", 2, 60, 14, 14);
        *(checkBoxes + 3) = loadCheckboxesFake("Rotate 90 CW", 2, 80, 14, 14);
        *(checkBoxes + 4) = loadCheckboxesFake("Rotate 90 CCW", 2, 100, 14, 14);
        *(checkBoxes + 5) = loadCheckboxesFake("Rotate 180 CCW", 2, 120, 14, 14);
    } else if(!strcmp(dialogName, "error")) {
    }

	return checkBoxes;*/
    return NULL;
}

Button **loadButtonsFake(char *dialogName, int numButtons) {
	/*Button **buttons = (Button **) malloc(sizeof(Button *) * numButtons);
	memset(buttons, 0, sizeof(Button) * numButtons);

    if(!strcmp(dialogName, "newTerrain")) {
        *(buttons + 0) = loadButtonFake("Ok", 40, 60, 20, 14);
    	*(buttons + 1) = loadButtonFake("Cancel", 70, 60, 50, 14);
    } else if(!strcmp(dialogName, "generateTerrain")) {
        *(buttons + 0) = loadButtonFake("Ok", 40, 80, 20, 14);
      	*(buttons + 1) = loadButtonFake("Cancel", 70, 80, 50, 14);
    } else if(!strcmp(dialogName, "object")) {
        *(buttons + 0) = loadButtonFake("Ok", 60, 100, 20, 14);
      	*(buttons + 1) = loadButtonFake("Cancel", 90, 100, 50, 14);
    } else if(!strcmp(dialogName, "view")) {
        *(buttons + 0) = loadButtonFake("Ok", 50, 220, 20, 14);
    } else if(!strcmp(dialogName, "replace")) {
        *(buttons + 0) = loadButtonFake("Ok", 30, 280, 20, 14);
    	*(buttons + 1) = loadButtonFake("Cancel", 60, 280, 50, 14);
    	*(buttons + 2) = loadButtonFake("Change pattern", 120, 280, 110, 14);
    } else if(!strcmp(dialogName, "globalReplace")) {
        *(buttons + 0) = loadButtonFake("Ok", 30, 280, 20, 14);
    	*(buttons + 1) = loadButtonFake("Cancel", 60, 280, 50, 14);
    	*(buttons + 2) = loadButtonFake("Change pattern", 120, 280, 110, 14);
    } else if(!strcmp(dialogName, "rotation")) {
        *(buttons + 0) = loadButtonFake("Ok", 70, 140, 20, 14);
    } else if(!strcmp(dialogName, "error")) {
        *(buttons + 0) = loadButtonFake("Ok", 200, 52, 20, 14);
    } else if(!strcmp(dialogName, "file")) {
        *(buttons + 0) = loadButtonFake("Ok", 200, 52, 20, 14); //Ok/save
        *(buttons + 1) = loadButtonFake("Cancel", 200, 52, 20, 14);
    }

	return buttons;*/
    return NULL;
}

Text *loadTextFake(char *string, int x, int y) {
    /*Text *text = (Text *) malloc(sizeof(Text));
    memset(text, 0, sizeof(Text));

    text->string = string;
    text->x = x;
    text->y = y;

    return text;*/
    return NULL;
}

TextBox *loadTextBoxFake(char *text, int x, int y, int width, int height) {
    /*TextBox *textBox = (Textbox *) malloc(sizeof(TextBox));
    memset(textBox, 0, sizeof(Textbox));

	textBox->title = text;
	textBox->x = x;
	textBox->y = y;
	textBox->width = width;
	textBox->height = height;
	//textBox->dialogBox = &numeric_dialog_boxes[base_height_dialog];*/
    return NULL;
}

CheckBox *loadCheckBoxFake(char *text, int x, int y, int width, int height) {
    /*TextBox *textBox = (checkBox *) malloc(sizeof(checkBox));
    memset(checkBox, 0, sizeof(checkBox));

    checkBox->title = text;
    checkBox->x = x;
    checkBox->y = y;
    checkBox->width = width;
    checkBox->height = height;
    checkbox->action = cb_dialog_text;
    return checkBox;*/
    return NULL;
}

Button *loadButtonFake(char *text, int x, int y, int width, int height) {
    /*Button *button = (Button *) malloc(sizeof(Button));
    memset(button, 0, sizeof(Button));

    button->title = text;
	button->x = x;
	button->y = y;
	button->width = width;
	button->height = height;
    button->action = cb_dialog_text;

    return button;*/
    return NULL;
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
