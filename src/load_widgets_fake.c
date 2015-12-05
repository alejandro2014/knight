
Dialog *loadDialogName(char *dialogName) {
    Dialog *dialog = NULL;

    if(!strcmp(dialogName, "newTerrain")) {
        menu = loadDialogFake("New terrain", 200, 100, 100, 150);
    } else if(!strcmp(dialogName, "generateTerrain")) {
        menu = loadDialogFake("Generate terrain", 200, 50, 100, 220);
    } else if(!strcmp(dialogName, "object")) {
        menu = loadDialogFake("Object", 200, 50, 120, 200);
    } else if(!strcmp(dialogName, "view")) {
        menu = loadDialogFake("View", 200, 50, 240, 120);
    } else if(!strcmp(dialogName, "replace")) {
        menu = loadDialogFake("Replace", 200, 50, 300, 240);
    } else if(!strcmp(dialogName, "globalReplace")) {
        menu = loadDialogFake("Global replace", 200, 50, 300, 240);
    } else if(!strcmp(dialogName, "rotation")) {
        menu = loadDialogFake("Rotation", 200, 50, 160, 160);
    } else if(!strcmp(dialogName, "error")) {
        menu = loadDialogFake("Error", 200, 200, 70, 400);
    }

    return menu;
}

Menu *loadDialogFake(char *title, int x, int y, int width, int height) {
  Menu *menu = (Menu *) malloc(sizeof(Menu));
  memset(menu, 0, sizeof(Menu));

  menu->x = x;
  menu->y = y;
  menu->width = width;
  menu->height = height;
  menu->title = title;

  return menu;
}

TextBox **loadTextBoxesFake(char *dialogName, int numTextboxes) {
	TextBox **textBoxes = (TextBox **) malloc(sizeof(TextBox *) * numTextboxes);
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

    } else if(!strcmp(dialogName, "globalReplace")) {

    } else if(!strcmp(dialogName, "rotation")) {

    } else if(!strcmp(dialogName, "error")) {

    }

	return textBoxes;
}

CheckBox **loadCheckBoxesFake(char *dialogName, int numCheckBoxes) {
	CheckBox **checkBoxes = (CheckBox **) malloc(sizeof(CheckBox *) * numCheckBoxes);
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

	return checkBoxes;
}

Button **loadButtonsFake(char *dialogName, int numButtons) {
	Button **buttons = (Button **) malloc(sizeof(Button *) * numButtons);
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
    }

	return buttons;
}

Textbox *loadTextBoxFake(char *text, int x, int y, int width, int height) {
    TextBox *textBox = (Textbox *) malloc(sizeof(TextBox));
    memset(textBox, 0, sizeof(Textbox));

	textBox->title = text;
	textBox->x = x;
	textBox->y = y;
	textBox->width = width;
	textBox->height = height;
	//textBox->dialogBox = &numeric_dialog_boxes[base_height_dialog];
}

Checkbox *loadCheckBoxFake(char *text, int x, int y, int width, int height) {
    TextBox *textBox = (checkBox *) malloc(sizeof(checkBox));
    memset(checkBox, 0, sizeof(checkBox));

    checkBox->title = text;
    checkBox->x = x;
    checkBox->y = y;
    checkBox->width = width;
    checkBox->height = height;
    return checkBox;
}

Button *loadButtonFake(char *text, int x, int y, int width, int height) {
    Button *button = (Button *) malloc(sizeof(Button));
    memset(button, 0, sizeof(Button));

    button->title = text;
	button->x = x;
	button->y = y;
	button->width = width;
	button->height = height;

    return button;
}

ButtonContainer *loadButtonContainer(Menu *menu) {
	ButtonContainer *buttonContainer = (ButtonContainer *) malloc(sizeof(ButtonContainer));
	memset(buttonContainer, 0, sizeof(ButtonContainer));

  buttonContainer->buttonsNo = 2;
	buttonContainer->buttons = loadButtons(menu);

	return buttonContainer;
}

TextBoxContainer *loadTextBoxContainer(Menu *menu) {
	TextBoxContainer *textBoxContainer = (TextBoxContainer *) malloc(sizeof(TextBoxContainer));
	memset(textBoxContainer, 0, sizeof(TextBoxContainer));

    textBoxContainer->textBoxesNo = 3;
	textBoxContainer->textBoxes = loadTextBoxes(menu);

	return textBoxContainer;
}
