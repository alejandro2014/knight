#ifndef __MENUS_H__
#define __MENUS_H__

#include "global.h"

typedef struct {
	//Menu *menu;
	int x;
	int y;
	int width;
	int height;
	char *title;
	int padding;
    //Action action;
} Button;

typedef struct {
	//DialogBox *dialogBox;
	int x;
	int y;
	int width;
	int height;
	char *title;
    //SDL_Texture *titleTexture;
} TextBox;

typedef struct {
	int x;
	int y;
	char *string;
    //SDL_Texture *titleTexture;
} Text;

typedef struct {
    int x;
    int y;
    int width;
    int height;
    char *text;
    bool enabled;
} CheckBox;

typedef struct {
    char *name;
	int x;
	int y;
	int width;
	int height;
	char *title;

    TextBox **textBoxes;
    Button **buttons;
    CheckBox **checkBoxes;
    Text **texts;

    int numTextBoxes;
    int numButtons;
    int numCheckBoxes;
    int numTexts;

    bool show;
} Dialog;

Dialog *loadDialog(char *dialogId);

#endif
