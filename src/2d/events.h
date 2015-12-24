#ifndef __EVENTS_H__
#define __EVENTS_H__

#include "global.h"

void resizeScreen(SDL_Event *event);

void events_loop (void);

char getTypedChar(SDL_Event *event);

void mouse_click (bool left_b, bool right_b, int mouse_x, int mouse_y);

#endif