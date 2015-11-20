#include "menus.h"
#include "load_widgets.h"

Menu *loadMenus(char *nameOfFile) {
    /*Menu *menu = (Menu *) malloc(sizeof(Menu));
    memset(menu, 0, sizeof(Menu))*/
    
    return NULL;
}

/*
TODO The loaders have been hardcoded on purpose. The next step is to extract all
the values to a configuration file, like an XML or a JSON, and get rid of all
these functions
*/

Menu *loadMenu(char *dialogName) {
  Menu *menu = NULL;

  if(!strcmp(dialogName, "newTerrainMenu")) {
    menu = loadNewTerrainDialog();
    TextBoxContainer *textBoxes = loadTextBoxContainer(menu);
  } else if(!strcmp(dialogName, "generateTerrainMenu")) {
    menu = loadGenerateTerrainDialog();
  }

  return menu;
}

Menu *loadNewTerrainDialog() {
  Menu *menu = (Menu *) malloc(sizeof(Menu));
  memset(menu, 0, sizeof(Menu));

  menu->x = 100;
  menu->y = 100;
  menu->width = x_new_terrain_menu_lenght;
  menu->height = y_new_terrain_menu_lenght;
  menu->title = "New terrain";
  
  menu->textBoxes = loadTextBoxes(menu);

  return menu;
}

Menu *loadGenerateTerrainDialog() {
  Menu *menu = (Menu *) malloc(sizeof(Menu));
  memset(menu, 0, sizeof(Menu));

  menu->x = x_generate_terrain_menu;
  menu->y = y_generate_terrain_menu;
  menu->width = x_generate_terrain_menu_lenght;
  menu->height = y_generate_terrain_menu_lenght;
  menu->title = "Generate terrain";

  return menu;
}

TextBox *loadTextBoxes(Menu *menu) {
	TextBox *textBoxes = (TextBox *) malloc(sizeof(TextBox) * 3);
	TextBox *currentTextBox;
    memset(textBoxes, 0, sizeof(TextBox) * 3);

    int basex = menu->x;
    int basey = menu->y;
    
    currentTextBox = textBoxes + 0;
	currentTextBox->title = "X Size:";
	currentTextBox->x = basex + 2;
	currentTextBox->y = basey + 2;
	currentTextBox->width = 42;
	currentTextBox->height = 14;
	currentTextBox->dialogBox = &numeric_dialog_boxes[x_map_size_dialog];

	currentTextBox = textBoxes + 1;
	currentTextBox->title = "Y Size:";
	currentTextBox->x = basex + 2;
	currentTextBox->y = basey + 22;
	currentTextBox->width = 42;
	currentTextBox->height = 14;
	currentTextBox->dialogBox = &numeric_dialog_boxes[y_map_size_dialog];

	currentTextBox = textBoxes + 2;
	currentTextBox->title = "Base Height:";
	currentTextBox->x = basex + 2;
	currentTextBox->y = basey + 42;
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
  currentButton->padding = 2;

	currentButton = buttons + 1;
	currentButton->menu = menu;
	currentButton->x = 70;
	currentButton->y = 60;
	currentButton->width = 50;
	currentButton->height = 14;
	currentButton->title = "Cancel";
  currentButton->padding = 2;

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
