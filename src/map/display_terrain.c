#include "display_terrain.h"

#include "actions.h"
#include "cursors.h"
#include "draw_stuff.h"
#include "menus.h"
#include "objects.h"
#include "generate_terrain.h"

void draw_grid (SDL_Surface * this_screen) { //draw the grid
    Uint8 *screen_buffer = (Uint8 *) this_screen->pixels;
    int my_pitch = this_screen->pitch;
    int x_grid_start = x_screen_offset + (grid - xoffset % grid) * terrain_ratio;
    int y_grid_start = y_screen_offset + (grid - yoffset % grid) * terrain_ratio;
    int x, y;

    //draw x grid (|)
    for (x = x_grid_start; x < window_width - x_screen_offset; x += grid * terrain_ratio)
        for (y = y_screen_offset; y < window_height - y_screen_offset; y++)
            putPixel(x, y, 255);

    //draw y grid (-)
    for (y = y_grid_start; y < window_height - y_screen_offset;  y += grid * terrain_ratio)
        for (x = x_screen_offset; x < window_width - x_screen_offset; x++)
            putPixel(x, y, 255);
}

//draws the select area (in fact, the lines)
void draw_selection(SDL_Surface * this_screen) {
    char str[800];//debug
    int line_1_x,line_1_y,line_2_x,line_2_y;
    int hor_line_len,ver_line_len;
    int s_selection_x_1,s_selection_x_2,s_selection_y_1,s_selection_y_2;
    int x, y;

    Uint8 *screen_buffer = (Uint8 *) this_screen->pixels;
    int my_pitch = this_screen->pitch;

    if(selection_x_2==-1 && selection_y_2==-1)return;//no selection to draw

    getScreenSelection(&s_selection_x_1, ...)

    //ok, now let's try to get the SCREEN coordinates of this shit.
    line_1_x=(s_selection_x_1-xoffset+x_screen_offset)*terrain_ratio;
    line_1_y=(s_selection_y_1-yoffset+y_screen_offset)*terrain_ratio;
    line_2_x=(s_selection_x_2-xoffset+x_screen_offset)*terrain_ratio;
    line_2_y=(s_selection_y_2-yoffset+y_screen_offset)*terrain_ratio;

    hor_line_len=line_2_x-line_1_x;
    ver_line_len=line_2_y-line_1_y;

    //now, test the lenght of the lines (and adjust them, if neccesary)
    if(line_1_x+hor_line_len>window_width)
        hor_line_len = window_width - line_1_x;

    if(line_1_y+ver_line_len>window_height)
        ver_line_len = window_height - line_1_y;

    if(line_1_y < 0) {
    	ver_line_len += line_1_y;
    	line_1_y = 0;
    }

    if(line_1_x < 0) {
    	hor_line_len += line_1_x;
    	line_1_x=0;
    }

    if(line_1_y>0 && line_1_y<=window_height)
        for (x=line_1_x; x<line_1_x+hor_line_len; x+=2)
            putPixel(x, line_1_y, black);

    if(line_2_y>0 && line_2_y<=window_height)
        for (x=line_1_x; x<line_1_x+hor_line_len; x+=2)
            putPixel(x, line_2_y, black);

    if(line_1_x>0 && line_1_x<=window_width)
        for (y=line_1_y; y<line_1_y+ver_line_len; y+=2)
            putPixel(line_1_x, y, black);

    if(line_2_x>0 && line_2_x<=window_width)
        for (y=line_1_y; y<line_1_y+ver_line_len; y+=2)
            putPixel(line_2_x, y, black);
}

void getScreenSelection(...) {
    //ok now, put in s_selection_x_1,s_selection_y_1 the upper left corner of the selection
    if(selection_x_1 < selection_x_2) {
  		s_selection_x_1 = selection_x_1;
  		s_selection_x_2 = selection_x_2;
	} else {
  		s_selection_x_1 = selection_x_2;
  		s_selection_x_2 = selection_x_1;
	}

    if(selection_y_1 < selection_y_2) {
  		s_selection_y_1 = selection_y_1;
  		s_selection_y_2 = selection_y_2;
	} else {
  		s_selection_y_1 = selection_y_2;
  		s_selection_y_2 = selection_y_1;
	}
}

void put_right_cursor() {
	bool mouse_shape_arrow=0;
	if(current_cursor==cursor_wait)return;

	if(show_new_terrain_menu || show_generate_terrain_menu || show_view_menu || show_replace_menu || show_rotate_menu || show_object_menu || show_global_replace_menu || view_error_menu) {
        if(current_cursor!=cursor_arrow) {
			change_cursor(cursor_arrow);
		}

		return;
    }

    if (view_file_menu) {
        if(current_cursor!=cursor_arrow) {
            change_cursor(cursor_arrow);
        }

        return;
    }

	//now, check and see if the mouse is over the toolbar, minimap, or status bar,
	//and, if it is, the cursor's shape is arrow.
    if(last_click_on!=click_terrain || (last_click_on==click_terrain && long_pressed_button_l==0)) {
        if(status_bar) {
            if(x_mouse_pos < status_bar_x || x_mouse_pos > (status_bar_x + status_bar_x_lenght) ||
               y_mouse_pos < status_bar_y || y_mouse_pos > (status_bar_y + status_bar_y_lenght))
	              mouse_shape_arrow=0;
	        else if(current_cursor!=cursor_arrow) {
		  	    change_cursor_show(cursor_arrow);
		  		return;
		  	}
			else return;
        }

	    if(mini_map) {
            if(x_mouse_pos > min_map_x && x_mouse_pos < (min_map_x + 255) &&
               y_mouse_pos > min_map_y && y_mouse_pos < (min_map_y + 255)) {
		        if(current_cursor!=cursor_arrow) {
		  		    change_cursor_show(cursor_arrow);
		  	    }
				return;
            }
        }

        if(tool_bar) {
            if(x_mouse_pos >= tool_bar_x && x_mouse_pos <= tool_bar_x + tool_bar_x_lenght &&
               y_mouse_pos >= tool_bar_y && y_mouse_pos <= tool_bar_y + tool_bar_y_lenght) {
			    if(current_cursor!=cursor_arrow) {
			  	    change_cursor_show(cursor_arrow);
			  	}
				return;
            }
        }
	}

    if(!caps_look_on) {
        switch(current_tool) {
            case t_place: changeCursor(cursor_put); break;
            case t_escavate: changeCursor(cursor_dig); break;
            case t_elevate: changeCursor(cursor_elevate); break;
            case t_peek: changeCursor(cursor_peek); break;
            case t_replace: changeCursor(cursor_replace); break;
            case t_flood: changeCursor(cursor_flood); break;
            case t_zoom_in: changeCursor(cursor_zoom); break;
            case t_select: changeCursor(cursor_select); break;
            case t_object: changeCursor(cursor_null); break;
            case t_global_replace: changeCursor(cursor_global_replace); break;
        }
    }
  else
  //draw the target cursor
  if(current_cursor!=cursor_target)change_cursor_show(cursor_target);
}

void changeCursor(int cursor) {
    if(current_cursor != cursor)
        change_cursor_show(cursor);
}

void drawScreen() {
  /*put_right_cursor();
  check_toolbar_mouse_over();
  if(no_update_now) {
    no_update_now=0;
    return some_int;
  }*/

  //terrain_on_screen(screen);
  //draw_selection(screen);
  //  debug_info();
  //if (current_tool == t_object && current_cursor!=cursor_arrow)draw_object_on_screen(screen);
  //if (grid)draw_grid (screen);
  //if (status_bar)draw_status_bar ();
  //if (mini_map)draw_minimap (screen);

  //if (tool_bar)draw_tool_bar (screen);
  /*if (show_tip)draw_tool_tip();*/

  if (show_new_terrain_menu) drawMenu("newTerrain");
  if (show_generate_terrain_menu) drawMenu("generateTerrain");
  if (show_view_menu) drawMenu("view");
  if (show_object_menu) drawMenu("object");
  if (show_replace_menu) drawMenu("replace");
  if (show_global_replace_menu) drawMenu("globalReplace");
  if (show_rotate_menu) drawMenu("rotation");
  if (view_error_menu) drawMenu("error");
  if (view_file_menu)draw_file_menu(screen);
}
