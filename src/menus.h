#ifndef __MENUS_H__
#define __MENUS_H__

#include "global.h"

void load_tool_bar();
void drawWindowTitle(Menu *menu, SDL_Surface *currentScreen);

void draw_new_terrain_menu (SDL_Surface * this_screen);
void draw_generate_menu (SDL_Surface * this_screen);
void draw_view_menu (SDL_Surface * this_screen);
void draw_replace_menu (SDL_Surface * this_screen);
void draw_object_menu (SDL_Surface * this_screen);
void draw_global_replace_menu (SDL_Surface * this_screen);
void draw_rotate_menu (SDL_Surface * this_screen);
void draw_file_menu (SDL_Surface * this_screen);
void draw_error_box(SDL_Surface * this_screen);

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
