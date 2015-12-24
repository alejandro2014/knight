#include <SDL2/SDL_events.h>
#include "events.h"

#include "actions.h"
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

void readEvents(int *finish) {
    /*SDL_Event event;

    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            *finish = 1;
        }
    }*/
}

void events_loop() {
    SDL_Event event;
    SDL_Keymod mod_key_status;
    int i;

    while (1) {
        SDL_WaitEvent (&event);
        if (event.type == SDL_QUIT) break;

        mod_key_status=SDL_GetModState();
        caps_look_on = (mod_key_status & KMOD_CAPS) ? 1 : 0;

        switch(event.type) {
            //case SDL_QUIT: break;
            case SDL_MOUSEBUTTONUP: manageButtonClick(&event); break;
            case SDL_WINDOWEVENT_RESIZED: resizeScreen(&event); break;
        }

        if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN) {
            x_mouse_pos = event.motion.x;
            y_mouse_pos = event.motion.y;
            mouse_delta_x = event.motion.xrel;
            mouse_delta_y = event.motion.yrel;

            //get the buttons state
            if (SDL_GetMouseState (NULL, NULL) & SDL_BUTTON (SDL_BUTTON_LEFT)) {
                button_l = 1;
                long_pressed_button_l++;
            } else
                button_l = 0;

            if (SDL_GetMouseState (NULL, NULL) & SDL_BUTTON (SDL_BUTTON_RIGHT)) {
                button_r = 1;
                long_pressed_button_r++;
            } else
                button_r = 0;

            if (drag_minimap) move_minimap ();
            else if (drag_toolbar) move_toolbar ();
            else if (drag_statusbar) move_statusbar ();

            if (view_file_menu)	{ checkDialog("file", 0); continue; }
            if (view_error_menu) { checkDialog("error", 0); continue; }
            if (show_new_terrain_menu) { checkDialog("new", 0); continue; }
            if (show_generate_terrain_menu) { checkDialog("generate", 0); continue; }
            if (show_view_menu) { checkDialog("view", 0); continue; }
            if (show_replace_menu) { checkDialog("replace", 0); continue; }
            if (show_global_replace_menu) { checkDialog("global_replace", 0); continue; }
            if (show_rotate_menu) { checkDialog("rotate", 0); continue; }
            if (show_object_menu) { checkDialog("object", 0); continue; }

            check_toolbar_mouse_over ();

            if (button_l || button_r)
                mouse_click (button_l, button_r, x_mouse_pos, y_mouse_pos);
        }//end of SDL_MOUSEMOTION event

        if (view_file_menu) { checkDialog("file", getTypedChar(&event)); continue; }
        if (view_error_menu) { checkDialog("error", getTypedChar(&event)); continue; }
        if (show_new_terrain_menu) { checkDialog("newTerrain", getTypedChar(&event)); continue; }
        if (show_generate_terrain_menu) { checkDialog("generateTerrain", getTypedChar(&event)); continue; }
        if (show_replace_menu) { checkDialog("replace", getTypedChar(&event)); continue; }
        if (show_global_replace_menu) { checkDialog("global_replace", getTypedChar(&event)); continue; }
        if (show_object_menu) { checkDialog("object", getTypedChar(&event)); continue; }

        if (event.type == SDL_KEYDOWN) {
            Uint8 *keystate = SDL_GetKeyboardState (NULL);
            if (keystate[SDLK_DOWN]&& (HEIGHT * terrain_ratio - yoffset) > window_height)yoffset += 4;
            if (keystate[SDLK_UP]&& yoffset > 0)yoffset -= 4;
            if (keystate[SDLK_LEFT] && xoffset > 0)xoffset -= 4;
            if (keystate[SDLK_RIGHT]&& (WIDTH * terrain_ratio - xoffset) > window_width)xoffset += 4;

            if (keystate[SDLK_z]) {
                mod_key_status=SDL_GetModState();
            }
        }
    }
}

char getTypedChar(SDL_Event *event) {
    return ((*event).type == SDL_KEYDOWN) ? (*event).key.keysym.sym : 0;
}

void mouse_click (bool left_b, bool right_b, int mouse_x, int mouse_y) {
    if (tool_bar && check_toolbar_press()) return;
    if (mini_map && check_mouse_minimap()) return;
    if (status_bar && status_bar_press()) return;

    //check if there is a right click on the terrain, to show the view menu
    if(long_pressed_button_r == 1) {
        //see if we are dragging a terrain object
        if(current_tool==t_object) {
            int i;

            free(current_object.object_mem);
            current_object.object_mem=0;
            //change the tool to the draw tool
            current_tool=t_place;

            for(i=0;i<no_of_main_tool_bar_icons;i++) {
                main_tool_bar[i].icon_active = 0;
            }

            main_tool_bar[0].icon_active = 1;
        } else {
            show_view_menu = 1;
        }
    }

    //don't do any terain related things, if the right button is pressed
    if (long_pressed_button_r != 0) return;

    //after all tests ended
    if (last_click_on != click_terrain) {
        if (long_pressed_button_l != 1)
            return;
        else {
            last_click_on = click_terrain;
        }
    }

    switch (current_tool) {
        case t_peek: pick_height (left_b, right_b); break;
        case t_place: draw_brush_line (); break;
        case t_elevate: draw_brush_line (); break;
        case t_escavate: draw_brush_line (); break;
        case t_flood: change_cursor(cursor_wait);pre_flood_area (); change_cursor(last_cursor);break;
        case t_replace: pre_change_area (); break;
        case t_global_replace: global_replace(); break;
        case t_zoom_in: zoom_in (); break;
        case t_select: select_area(); break;
        case t_object:
            if(long_pressed_button_l==1)
                stamp_object();
            break;
    }
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
}
