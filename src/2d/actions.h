#ifndef ACTIONS_H
#define ACTIONS_H

#include <SDL2/SDL_events.h>
#include "global.h"

void move_on_minimap();
void move_minimap();
void move_toolbar();
void move_statusbar();

bool status_bar_press ();

bool check_mouse_minimap(); //check if the mouse is on the minimap
void check_toolbar_mouse_over(); //check the tool bar buttons for being pointed by the mouse
bool check_toolbar_press(); //check the tool bar buttons for being pressed (left down button)
bool check_toolbar_release(); //check the tool bar buttons for being released (left button)

void process_menu_commands(int custom_message);

void rise_terrain();
void sink_terrain();
void smooth_terrain();

void rise_selection();
void sink_selection();
void smooth_selection();

void clear_selection();
void new_terrain_menu();

#endif
