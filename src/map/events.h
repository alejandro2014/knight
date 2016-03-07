#ifndef EVENTS_H
#define EVENTS_H

#include <SDL2/SDL_events.h>

#include "../global.h"
#include "../console/console_lang.h"
#include "../console/console_write.h"

#include "global_map.h"

void readEvents(Console *console, Events *events);
void processKeyboardEvent(SDL_Event *event, Console *console);
void processMouseButtonDownEvent(SDL_Event *event);

#endif
