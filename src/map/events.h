#ifndef EVENTS_H
#define EVENTS_H

#include <SDL2/SDL_events.h>

#include "../global.h"
#include "../console/console.h"
#include "../console/console_write.h"

#include "global_map.h"

void readEvents(Console *console, Events *events);

//void resizeScreen(SDL_Event *event);
//void events_loop (void);
//char getTypedChar(SDL_Event *event);
//void mouse_click (bool left_b, bool right_b, int mouse_x, int mouse_y);

#endif
