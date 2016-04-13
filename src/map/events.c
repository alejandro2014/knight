#include "events.h"

Events *events;

void readEvents(Console *console, Events *eventsInfo) {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT: eventsInfo->finish = true; break;
            case SDL_KEYDOWN: processKeyboardEvent(&event, console); break;
            case SDL_MOUSEBUTTONDOWN: processMouseButtonDownEvent(&event, eventsInfo); break;
        }
    }
}

void processKeyboardEvent(SDL_Event *event, Console *console) {
    char currentChar = (char)event->key.keysym.sym;

    switch(currentChar) {
        case SDLK_RETURN: consoleNewLine(console); break;
        case SDLK_BACKSPACE: consoleDeleteChar(console); break;
        default: consoleAddChar(console, currentChar, true); break;
    }
}

void processMouseButtonDownEvent(SDL_Event *event, Events *eventsInfo) {
    int x = event->button.x;
    int y = event->button.y;
}

//NEW xSize ySize baseHeight ok cancel - base_height_dialog x_map_size_dialog y_map_size_dialog
//GENERATE overwriteTerrain seed ok cancel - seed_dialog
//VIEW  toolbar minimap statusBar gridOff grid16/32/64/128/256 ok - void
// ROTATE x y z 90 180 270 ok - textboxes: void
// REPLACE greater leaser greaterLeaser plus minus equal Solid Pattern changePattern cancel ok - textbox: tolerance
// GLOBAL REPLACE greater leaser greaterLeaser plus minus equal Solid Pattern changePattern cancel ok - textbox: global_tolerance
// OBJECT buttons: placeOver increase decrease cancel ok - textbox: void
// ERROR buttons: ok - textbox: void
