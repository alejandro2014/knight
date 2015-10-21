#include "menus.h"
#include "load_widgets.h"

#define INITIAL 0
#define DOUBLE_QUOTE_OPEN 1

void copyContentToken(Token *token, int initialPos, int finalPos, char *string) {
  memcpy(token->content, string + initialPos, finalPos - initialPos);
}

Token *newToken(int type, char *content) {
    Token *token = (Token *) malloc(sizeof(Token));
    memset(token, 0, sizeof(Token));

    token->type = type;

    //int sizeContent = sizeof(char) * strlen(content);
    token->content = (char *) malloc(sizeContent);
    memset(&token->content, 0, 128);

    return token;
}

Token *getToken(char *string, int *position) {
    char *token = NULL;
    char currentChar;
    int currentStatus = INITIAL;
    int currentPos = *position;

    printf("getToken position %d\n", currentPos);

    while(token == NULL) {
        currentChar = *(string + currentPos);

        switch(currentStatus) {
          case INITIAL:
            switch(currentChar) {
              case '{':
                token = newToken(TOK_CURLY_OPEN, "{");
                break;
              case '\"':
                currentStatus = DOUBLE_QUOTE_OPEN;
                break;
            }
            break;
          case DOUBLE_QUOTE_OPEN:
            if(currentChar == '\"') {
              token = newToken(TOK_STRING, "{");
              copyContentToken(token, string, *position, currentPos);
              token = "string";
            }
            break;
        }

        currentPos++;
    }

    *position = currentPos;

    return token;
}

Menu *loadMenus(char *nameOfFile) {
    /*Menu *menu = (Menu *) malloc(sizeof(Menu));
    memset(menu, 0, sizeof(Menu))*/
    char *fileContent = "{\"dialogs\": {\"newTerrain\": {\"x\": 10,\"y\": 10,\"width\": 30,\"height\": 20,\"title\": \"New terrain\"}}}";
    int stringLength = strlen(fileContent);

    printf("Content of the file: %s\n", fileContent);
    printf("length: %d\n", stringLength);

    int position = 0;
    printf(">> %s\n", getToken(fileContent, &position));
    printf(">> %s\n", getToken(fileContent, &position));

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

  menu->x = x_new_terrain_menu;
  menu->y = y_new_terrain_menu;
  menu->width = x_new_terrain_menu_lenght;
  menu->height = y_new_terrain_menu_lenght;
  menu->title = "New terrain";

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

/*TextBox *loadTextBoxes(char *dialogName, Menu *menu) {
    if(!strcmp(dialogName))
}*/

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
