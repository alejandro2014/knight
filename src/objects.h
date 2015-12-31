#ifndef OBJECTS_H
#define OBJECTS_H

#include "global.h"

void do_load_object(char * FileName, terrain_object *this_current_object);
bool load_bmp_object(char * FileName, terrain_object *this_current_object);
void draw_object_on_screen(SDL_Surface * this_screen);
void pre_load_object();

#endif
