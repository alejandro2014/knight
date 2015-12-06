#ifndef __MENUS_H__
#define __MENUS_H__

#include <SDL2/SDL.h>
#include "global.h"

//#define DialogBox numeric_dialog_box_struct
typedef struct numeric_dialog_box_struct DialogBox;

typedef struct {
	DialogBox *dialogBox;
	int x;
	int y;
	int width;
	int height;
	char *title;
    SDL_Texture *titleTexture;
} TextBox;

typedef struct {
	int x;
	int y;
	int width;
	int height;
	char *title;
    TextBox *textBoxes;
    bool show;
} Dialog;

typedef struct {
	Menu *menu;
	int x;
	int y;
	int width;
	int height;
	char *title;
	int padding;
} Button;

typedef struct {
	int buttonsNo;
	Button *buttons;
} ButtonContainer;

typedef struct {
	int textBoxesNo;
	TextBox *textBoxes;
} TextBoxContainer;

void load_tool_bar();
void drawWindowTitle(Menu *menu);

void draw_replace_menu (SDL_Surface * this_screen);
void draw_global_replace_menu (SDL_Surface * this_screen);
void draw_file_menu (SDL_Surface * this_screen);

void check_new_terrain_menu (char text_input_char);
void check_generate_terrain_menu (char text_input_char);
void check_view_menu (char text_input_char);
void check_replace_menu (char text_input_char);
void check_object_menu (char text_input_char);
void check_global_replace_menu (char text_input_char);
void check_rotate_menu (char text_input_char);
void check_file_menu (unsigned char text_input_char);
void check_error_menu (char text_input_char);

#endif
