#ifndef __MENUS_H__
#define __MENUS_H__

#include "global.h"
//#include <SDL2/SDL.h>

//#define DialogBox numeric_dialog_box_struct
/*typedef struct numeric_dialog_box_struct DialogBox;
typedef void (*action)(void) Action;*/

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


/*void load_tool_bar();
void drawWindowTitle(Menu *menu);
void draw_file_menu (SDL_Surface * this_screen);

void check_file_menu (unsigned char text_input_char);*/
Dialog *loadDialog(char *dialogId);

#endif
