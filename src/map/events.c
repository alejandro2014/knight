#include "events.h"

Events *events;

void readEvents(Console *console, Events *events) {
    SDL_Event event;
    Uint8 *keystate;
    char currentChar;

    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                events->finish = true;
                break;

            case SDL_KEYDOWN:
                currentChar = (char)event.key.keysym.sym;

                switch(currentChar) {
                    case SDLK_RETURN: consoleNewLine(console); break;
                    case SDLK_BACKSPACE: consoleDeleteChar(console); break;
                    default: consoleAddChar(console, currentChar, true); break;
                }

                break;

            case SDL_MOUSEBUTTONDOWN:
                printf("Coords(%d, %d)\n", event.button.x, event.button.y);
                break;
        }
    }
}

/*#include "actions.h"
#include "global_tools.h"
#include "menus.h"
#include "tools.h"

void resizeScreen(SDL_Event *event) {
    no_update_now=1;
    window_width = event->window.data1;
    window_height = event->window.data2;
    if (window_width < 680)window_width = 680;
    if (window_height < 450)window_height = 450;
    window_width=window_width|3;
    //screen = SDL_SetVideoMode (window_width, window_height,8,SDL_HWSURFACE | SDL_RESIZABLE | SDL_HWPALETTE);
    SDL_Window *window = SDL_CreateWindow("[No title]", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_RESIZABLE);
    screen = screen = SDL_GetWindowSurface(window);
    //screen = SDL_SetVideoMode (window_width, window_height,8,SDL_HWSURFACE | SDL_RESIZABLE);
    //SDL_SetPalette (screen, SDL_LOGPAL | SDL_PHYSPAL, colors, 0, 256);
}

void manageButtonClick(SDL_Event *event) {
    while (SDL_PollEvent (event));	//clears all the events

    if((selection_x_1!=-1 && selection_x_2==-1) || selection_x_1==selection_x_2 || selection_y_1==selection_y_2) {
        selection_x_1=-1;
        selection_y_1=-1;
        selection_x_2=-1;
        selection_y_2=-1;
    }

    drag_minimap = 0;
    drag_toolbar = 0;
    drag_statusbar = 0;

    last_drawn_x = -1;
    last_drawn_y = -1;
    //mark buttons as unpressed at all, so they are fresh.
    long_pressed_button_l = 0;
    long_pressed_button_r = 0;

    button_l = (SDL_GetMouseState (NULL, NULL) & SDL_BUTTON (SDL_BUTTON_LEFT)) ? 1 : 0;
    button_r = (SDL_GetMouseState (NULL, NULL) & SDL_BUTTON (SDL_BUTTON_RIGHT)) ? 1 : 0;

    //now, check to see if there is any button up on the toolbar
    check_toolbar_release ();
}

//NEW xSize ySize baseHeight ok cancel - base_height_dialog x_map_size_dialog y_map_size_dialog
//GENERATE overwriteTerrain seed ok cancel - seed_dialog
//VIEW  toolbar minimap statusBar gridOff grid16/32/64/128/256 ok - void
// ROTATE x y z 90 180 270 ok - textboxes: void
// REPLACE greater leaser greaterLeaser plus minus equal Solid Pattern changePattern cancel ok - textbox: tolerance
// GLOBAL REPLACE greater leaser greaterLeaser plus minus equal Solid Pattern changePattern cancel ok - textbox: global_tolerance
// OBJECT buttons: placeOver increase decrease cancel ok - textbox: void
// ERROR buttons: ok - textbox: void
void checkDialog(char *dialogId, char text_input_char) {
    if(long_pressed_button_r == 1) show_object_menu = 0;
    checkButtons();
    checkOkCancelKeys();
    checkTab();
    checkNumericTextBoxes();
}

void checkNumericTextBox(TextBox *textbox, int inputChar) {
    int dialog_text_offset;

    if (textbox.has_focus == 1) {
        if (isNumeric(inputChar) && !maxLengthExcedeed(textbox)) {
            dialog_text_offset = textbox.text_offset;
            textbox.dialog_text[dialog_text_offset] = inputChar;
            textbox.dialog_text[dialog_text_offset + 1] = 0;
            textbox.text_offset++;
        }
        else if (inputChar == SDLK_BACKSPACE && textbox.text_offset > 0) {
            textbox.text_offset--;
            textbox.dialog_text[textbox.text_offset] = 0;
        }
    }
}

void checkButtons() {
    menu = currentMenu;

    buttons = getButtonsMenu(menu);

    for(i = 0; i < buttons; i++) {
        if (buttonPressed("greater")) cb_replace_greater(); //With all the names
    }
}

void checkTab() {
    //Taken from Generate menu
    if (text_input_char == SDLK_TAB) {
        if (numeric_dialog_boxes[base_height_dialog].has_focus) {
            numeric_dialog_boxes[x_map_size_dialog].has_focus = 1;
            numeric_dialog_boxes[x_map_size_dialog].text_offset = 0;
            numeric_dialog_boxes[y_map_size_dialog].has_focus = 0;
            numeric_dialog_boxes[base_height_dialog].has_focus = 0;
        } else if (numeric_dialog_boxes[x_map_size_dialog].has_focus) {
            numeric_dialog_boxes[x_map_size_dialog].has_focus = 0;
            numeric_dialog_boxes[y_map_size_dialog].has_focus = 1;
            numeric_dialog_boxes[y_map_size_dialog].text_offset = 0;
            numeric_dialog_boxes[base_height_dialog].has_focus = 0;
        } else if (numeric_dialog_boxes[y_map_size_dialog].has_focus) {
            numeric_dialog_boxes[x_map_size_dialog].has_focus = 0;
            numeric_dialog_boxes[y_map_size_dialog].has_focus = 0;
            numeric_dialog_boxes[base_height_dialog].has_focus = 1;
            numeric_dialog_boxes[base_height_dialog].text_offset = 0;
        }
    }
}

void checkNumericTextBoxes() {
    textboxes = getTextBoxes(dialogName)

    if(text_input_char) {
        for(i = 0 i < textboxes.lenght; i++) {
            checkNumericTextBox(textboxes[i], text_input_char);
        }
    }
}*/
