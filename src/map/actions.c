#include "actions.h"

void move_on_minimap() {
    int x_on_minimap, y_on_minimap, min_map_x_pos_lenght, min_map_y_pos_lenght;
    float x_ratio, y_ratio;

    x_on_minimap = x_mouse_pos - min_map_x;
    y_on_minimap = y_mouse_pos - min_map_y;
    x_ratio = (float) WIDTH / 256;
    y_ratio = (float) HEIGHT / 256;
    min_map_x_pos_lenght = (int) (window_width / x_ratio / terrain_ratio);
    min_map_y_pos_lenght = (int) (window_height / y_ratio / terrain_ratio);
    xoffset = (int) ((x_on_minimap * x_ratio) - (min_map_x_pos_lenght * x_ratio) / 2);
    yoffset = (int) ((y_on_minimap * y_ratio) - (min_map_y_pos_lenght * y_ratio) / 2);
}

void move_minimap() {
    min_map_x += mouse_delta_x;
    min_map_y += mouse_delta_y;
}

void move_toolbar() {
tool_bar_x += mouse_delta_x;
tool_bar_y += mouse_delta_y;
}

void move_statusbar() {
status_bar_x += mouse_delta_x;
status_bar_y += mouse_delta_y;
}

bool status_bar_press () {
    if (x_mouse_pos < status_bar_x || x_mouse_pos > (status_bar_x + status_bar_x_lenght) || y_mouse_pos < status_bar_y || y_mouse_pos > (status_bar_y + status_bar_y_lenght))
    return false;

    if (last_click_on != click_status_bar) {
      if (long_pressed_button_l != 1 && long_pressed_button_r != 1) {
        return false;
      }
      else {
        last_click_on = click_status_bar;
      }
    }

    if (long_pressed_button_r == 1)
        drag_statusbar = 1;
    return true;
}

//check if the mouse is on the minimap
bool check_mouse_minimap() {
    //is the mouse inside the minimap?
    if (x_mouse_pos > min_map_x && x_mouse_pos < (min_map_x + 255) && y_mouse_pos > min_map_y && y_mouse_pos < (min_map_y + 255)) {
        if (last_click_on != click_mini_map) {
            if (long_pressed_button_l != 1 && long_pressed_button_r != 1) {
                return false;
            } else {
                last_click_on = click_mini_map;
            }
        }

        if (button_l) {
            move_on_minimap ();
            return true;
        }

        if (button_r) {
            drag_minimap = true;
            return true;
        }
    }
    return false;

}


//check the tool bar buttons for being pointed by the mouse
void check_toolbar_mouse_over() {
    int i;
    bool any_tip=0;
    for (i = 0; i < no_of_main_tool_bar_icons; i++) {
        if (x_mouse_pos >= (tool_bar_x + (i * 36) + 3) && x_mouse_pos <= (tool_bar_x + (i * 36) + 3 + 32) && y_mouse_pos >= (tool_bar_y + 3) && y_mouse_pos <= (tool_bar_y + 3 + 32)) {
            main_tool_bar[i].icon_mouse_over = 1;
            sprintf(tip_text, "%s", main_tool_bar[i].tool_tip);
            tip_x=x_mouse_pos+16;
            tip_y=y_mouse_pos+16;
            main_tool_bar[i].mouse_over_timer++;

            if(main_tool_bar[i].mouse_over_timer>10 && main_tool_bar[i].mouse_over_timer <100) {
                show_tip=1;
                any_tip=1;
            }
        } else {
            main_tool_bar[i].icon_mouse_over = 0;
            main_tool_bar[i].mouse_over_timer=0;//reset the timer.
            if(!any_tip)show_tip=0;
        }
    }

    //now, check the small icons, for any tool tips
    if(!any_tip) { //don't check, if we already have a tip.
        for (i = 0; i < no_of_small_tool_bar_icons; i++) {
            if (x_mouse_pos >= (tool_bar_x + (i * 20) + 3) && x_mouse_pos <= (tool_bar_x + (i * 20) + 3 + 16) && y_mouse_pos >= (tool_bar_y + 3 + 32 +3) && y_mouse_pos <= (tool_bar_y + 3 + 32 +3+16)) {
                sprintf(tip_text, "%s", small_tool_bar[i].tool_tip);
                tip_x=x_mouse_pos+16;
                tip_y=y_mouse_pos+16;
                small_tool_bar[i].mouse_over_timer++;

                if(small_tool_bar[i].mouse_over_timer>10 && small_tool_bar[i].mouse_over_timer <100) {
                    show_tip=1;
                    any_tip=1;
                }
            } else {
                small_tool_bar[i].icon_mouse_over = 0;
                small_tool_bar[i].mouse_over_timer=0;//reset the timer.
                if(!any_tip)show_tip=0;
            }
        }
    }
}

//check the tool bar buttons for being pressed (left down button)
bool check_toolbar_press() {
    int i;

    if (x_mouse_pos < tool_bar_x || x_mouse_pos > (tool_bar_x + tool_bar_x_lenght) || y_mouse_pos < tool_bar_y || y_mouse_pos > (tool_bar_y + tool_bar_y_lenght))
        return false;

    if (last_click_on != click_tool_bar) {
        if (long_pressed_button_l != 1 && long_pressed_button_r != 1)
            return false;
        else
            last_click_on = click_tool_bar;
    }

    for (i = 0; i < no_of_main_tool_bar_icons; i++) {
        //check to see if we have any right click
        if (x_mouse_pos >= (tool_bar_x + (i * 36) + 3) && x_mouse_pos <= (tool_bar_x + (i * 36) + 3 + 32) && y_mouse_pos >= (tool_bar_y + 3) && y_mouse_pos <= (tool_bar_y + 3 + 32) && (long_pressed_button_l == 1 || long_pressed_button_r == 1)) {
            if (long_pressed_button_r == 1) {
                if (main_tool_bar[i].right_click_message != do_nothing) {
                    process_menu_commands (main_tool_bar[i].right_click_message);
                    return true;
                }
            }

            if (long_pressed_button_r == 0)
                main_tool_bar[i].icon_pressed = 1;
        }
	}

	//small icons now
	for (i = 0; i < no_of_small_tool_bar_icons; i++) {
        if (x_mouse_pos >= (tool_bar_x + (i * 20) + 3) && x_mouse_pos <= (tool_bar_x + (i * 20) + 3 + 20) && y_mouse_pos >= (tool_bar_y + 3 + 38) && y_mouse_pos <= (tool_bar_y + 3 + 38 + 16) && long_pressed_button_l == 1)
            small_tool_bar[i].icon_pressed = 1;
	}

	//check the height bar
	if (x_mouse_pos >= (tool_bar_x + no_of_small_tool_bar_icons * 20 + 4) && x_mouse_pos < (tool_bar_x + no_of_small_tool_bar_icons * 20 + 4 + 256) && y_mouse_pos >= (tool_bar_y + 2 + 40) && y_mouse_pos <= (tool_bar_y + 2 + 40 + 14) && long_pressed_button_l != 0)
	color_1 = x_mouse_pos - (tool_bar_x + no_of_small_tool_bar_icons * 20 + 4);

	//ok, now, if the right button is pressed, drag the toolbar
	if (long_pressed_button_r != 0)
        drag_toolbar = 1;
	return true;
}

//check the tool bar buttons for being released (left button)
 bool check_toolbar_release() {
    int i;
	int activated_icon = -1;

	for (i = 0; i < no_of_main_tool_bar_icons; i++) {
        if (x_mouse_pos >= (tool_bar_x + (i * 36) + 3) && x_mouse_pos <= (tool_bar_x + (i * 36) + 3 + 32) && y_mouse_pos >= (tool_bar_y + 3) && y_mouse_pos <= (tool_bar_y + 3 + 32) && !button_l) {

            if (main_tool_bar[i].icon_pressed == 1) {
                activated_icon = i;
                process_menu_commands (main_tool_bar[i].associated_window_message);
            }
        }

        main_tool_bar[i].icon_pressed = 0;	//clear the pressed icon flag[s]
	}

	/*now, in case there was an icon activated, mark it a activated, and clear the previous
	activated icon flag (we may have only one icon active at a time, right? */
	if (activated_icon != -1)
	if (!main_tool_bar[activated_icon].icon_dont_stay_pressed)
	for (i = 0; i < no_of_main_tool_bar_icons; i++)
	main_tool_bar[i].icon_active = (i != activated_icon) ? 0 : 1;

	//now, the small icons
	activated_icon = -1;
    for (i = 0; i < no_of_small_tool_bar_icons; i++) {
        if (x_mouse_pos >= (tool_bar_x + (i * 20) + 3) && x_mouse_pos <= (tool_bar_x + (i * 20) + 3 + 20) && y_mouse_pos >= (tool_bar_y + 3 + 38) && y_mouse_pos <= (tool_bar_y + 3 + 38 + 16) && !button_l) {
            if (small_tool_bar[i].icon_pressed == 1) {
                activated_icon = i;
                process_menu_commands (small_tool_bar[i].associated_window_message);
            }
        }

        small_tool_bar[i].icon_pressed = 0;	//clear the pressed icon flag[s]
	}

	if (activated_icon != -1 && !small_tool_bar[activated_icon].icon_dont_stay_pressed) {
        for (i = 0; i < no_of_small_tool_bar_icons; i++)
            small_tool_bar[i].icon_active = (i != activated_icon) ? 0 : 1;
    }

	return false;
}

void process_menu_commands (int custom_message) {
	SDL_Event event;

	switch (custom_message) {
        case change_tool_place: current_tool = t_place; break;
        case change_tool_elevate: current_tool = t_elevate; break;
        case change_tool_escavate: current_tool = t_escavate; break;
        case change_tool_peek: current_tool = t_peek; break;
        case change_tool_replace: current_tool = t_replace; break;
        case change_tool_global_replace: current_tool = t_global_replace; break;
        case change_tool_flood: current_tool = t_flood; break;
        case change_tool_zoom_in: current_tool = t_zoom_in; break;
        case change_tool_select:  current_tool = t_select;  break;

        case do_new_terrain:
            if(selection_x_1!=-1)
                clear_selection();
            else
                new_terrain_menu();
            break;

        case do_rise_terrain:
            if(selection_x_1!=-1)
                rise_selection();
            else
                rise_terrain ();
            break;

        case do_sink_terrain:
            if(selection_x_1!=-1)
                sink_selection();
            else
                sink_terrain ();
            break;

        case do_smooth_terrain:
            if(selection_x_1!=-1)
                smooth_selection();
            else
                smooth_terrain ();
            break;

        case do_display_object_menu:
            show_object_menu=1;
            long_pressed_button_r = 2;	//if we let it 1, the menu will dissapear
            break;

        case do_load:
            selection_x_1=-1;
            selection_y_1=-1;
            selection_x_2=-1;
            selection_y_2=-1;
            load_object=0;
            DoFileOpenSave (0);
            while (SDL_PollEvent (&event));	//clears all the events
            return;
            break;

        case do_save:
            DoFileOpenSave (1);
            while (SDL_PollEvent (&event));	//clears all the events
            return;
            break;

        case do_generate:
            generate_menu (seed);
            break;

        case do_display_replace_menu:
            show_replace_menu = 1;
            sprintf (numeric_dialog_boxes[tolerance].dialog_text, "%d",tolerance_value);
            numeric_dialog_boxes[tolerance].text_offset = 0;
            temp_tolerance_mode = tolerance_mode;
            temp_tolerance_replace_mode = tolerance_replace_mode;
            temp_tolerance_replace_mode_2 = tolerance_replace_mode_2;
            long_pressed_button_r = 2;	//if we let it 1, the menu will dissapear
            break;

        case do_display_global_replace_menu:
            show_global_replace_menu = 1;
            sprintf (numeric_dialog_boxes[global_tolerance].dialog_text, "%d",global_tolerance_value);
            numeric_dialog_boxes[global_tolerance].text_offset = 0;
            temp_global_tolerance_mode = global_tolerance_mode;
            temp_global_tolerance_replace_mode = global_tolerance_replace_mode;
            temp_global_tolerance_replace_mode_2 = global_tolerance_replace_mode_2;
            long_pressed_button_r = 2;	//if we let it 1, the menu will dissapear
            break;

        case change_tool_object:
            current_tool = t_object;
            pre_load_object();
            break;

        case do_decrease_zoom:
            if (terrain_ratio > 1) {
                int some_x_lenght = (window_width / terrain_ratio - 1) / 2;
                int some_y_lenght = (window_height / terrain_ratio - 1) / 2;

                xoffset -= some_x_lenght;
                yoffset -= some_y_lenght;
                terrain_ratio--;
            }
            break;

        case change_brush_1: brush_size = 1; break;
        case change_brush_2: brush_size = 2; break;
        case change_brush_3: brush_size = 3; break;
        case change_brush_4: brush_size = 4; break;
        case change_brush_5: brush_size = 5; break;

        case do_display_rotate_menu:
            show_rotate_menu=1;
            rotation_type=rotation_none;
            break;

        case do_decrease_tools_height:
            if (color_1 > 0) color_1--;
            break;

        case do_increase_tools_height:
            if (color_1 < 255) color_1++;
            break;
    }
}