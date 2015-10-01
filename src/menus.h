#ifndef __MENUS_H__
#define __MENUS_H__

#include "global.h"

void load_tool_bar ();

/////////////////////////////////////////////////
//draw the new terrain menu
void draw_new_terrain_menu (SDL_Surface * this_screen);

void check_new_terrain_menu (char text_input_char);

/////////////////////////////////////////////////
//draw the generate terrain menu
void draw_generate_menu (SDL_Surface * this_screen);

void check_generate_terrain_menu (char text_input_char);


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/////Draw the "view menu"
void draw_view_menu (SDL_Surface * this_screen);

void check_view_menu (char text_input_char);


/////////////////////////////////////////////////
//draw the generate terrain menu
void draw_replace_menu (SDL_Surface * this_screen);
void check_replace_menu (char text_input_char);

void draw_object_menu (SDL_Surface * this_screen);
void check_object_menu (char text_input_char);

void draw_global_replace_menu (SDL_Surface * this_screen);
void check_global_replace_menu (char text_input_char);

void draw_rotate_menu (SDL_Surface * this_screen);
void check_rotate_menu (char text_input_char);

void draw_file_menu (SDL_Surface * this_screen);
void check_file_menu (unsigned char text_input_char);

void draw_error_box(SDL_Surface * this_screen);

void check_error_menu (char text_input_char);

#endif
