#include "menus.h"
#include "load_widgets.h"

/*
TODO The loaders have been hardcoded on purpose. The next step is to extract all
the values to a configuration file, like an XML or a JSON
*/
Menu *loadMenu(char *dialog) {
  Menu *menu = (Menu *) malloc(sizeof(Menu));
  memset(menu, 0, sizeof(Menu));

	menu->x = x_new_terrain_menu;
	menu->y = y_new_terrain_menu;
	menu->width = x_new_terrain_menu_lenght;
	menu->height = y_new_terrain_menu_lenght;
	menu->title = "New terrain";

  return menu;
}

TextBox *loadTextBoxes(Menu *menu) {
	TextBox *textBoxes = (TextBox *) malloc(sizeof(TextBox) * 3);
	TextBox *currentTextBox;
	memset(textBoxes, 0, sizeof(TextBox) * 3);

  currentTextBox = textBoxes + 0;
	currentTextBox->menu = menu;
	currentTextBox->title = "X Size:";
	currentTextBox->x = 2;
	currentTextBox->y = 2;
	currentTextBox->width = 42;
	currentTextBox->height = 14;
	currentTextBox->dialogBox = &numeric_dialog_boxes[x_map_size_dialog];

	currentTextBox = textBoxes + 1;
	currentTextBox->menu = menu;
	currentTextBox->title = "Y Size:";
	currentTextBox->x = 2;
	currentTextBox->y = 22;
	currentTextBox->width = 42;
	currentTextBox->height = 14;
	currentTextBox->dialogBox = &numeric_dialog_boxes[y_map_size_dialog];

	currentTextBox = textBoxes + 2;
	currentTextBox->menu = menu;
	currentTextBox->title = "Base Height:";
	currentTextBox->x = 2;
	currentTextBox->y = 42;
	currentTextBox->width = 24;
	currentTextBox->height = 14;
	currentTextBox->dialogBox = &numeric_dialog_boxes[base_height_dialog];

	return textBoxes;
}

Button *loadButtons(Menu *menu) {
	Button *buttons = (Button *) malloc(sizeof(Button) * 2);
	memset(buttons, 0, sizeof(Button) * 2);

	Button *currentButton;

	currentButton = buttons + 0;
	currentButton->menu = menu;
	currentButton->x = 40;
	currentButton->y = 60;
	currentButton->width = 20;
	currentButton->height = 14;
	currentButton->title = "Ok";

	currentButton = buttons + 1;
	currentButton->menu = menu;
	currentButton->x = 70;
	currentButton->y = 60;
	currentButton->width = 50;
	currentButton->height = 14;
	currentButton->title = "Cancel";

	return buttons;
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
