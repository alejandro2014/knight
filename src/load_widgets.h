#ifndef LOAD_WIDGETS_H
#define LOAD_WIDGETS_H

typedef struct {
  int type;
  char content[128];
} Token;

Token *newToken(int type, char *content);
Menu *loadMenus(char *nameOfFile);
char *getToken(char *string, int *position);

Menu *loadMenu(char *dialog);
Menu *loadNewTerrainDialog();
Menu *loadGenerateTerrainDialog();

Button *loadButtons(Menu *menu);
TextBox *loadTextBoxes(Menu *menu);

ButtonContainer *loadButtonContainer(Menu *menu);
TextBoxContainer *loadTextBoxContainer(Menu *menu);
#endif
