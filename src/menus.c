#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_events.h>

#include "font.h"
#include "menus.h"
#include "load_widgets.h"

void draw_replace_menu (SDL_Surface * this_screen) {

	//draw the tolerance string and box
  print_string ("Tolerance:", black, white, x_replace_menu + 2,y_replace_menu + 20);
  draw_down_button (screen, x_replace_menu + 80, y_replace_menu + 18, 25, 14);
  print_string (numeric_dialog_boxes[tolerance].dialog_text, black, white,x_replace_menu + 82, y_replace_menu + 20);

  //draw the pattern file name.
  char *string = current_pattern.object_mem ? &pattern_file_name : "None";
  print_string ("Pattern:", black, white, x_replace_menu +2,y_replace_menu + 262);
  draw_empty_menu (screen, white, x_replace_menu + 60, y_replace_menu + 260,172, 14);
  print_string(string, black, white, x_replace_menu +62,y_replace_menu + 262);
}

void draw_global_replace_menu (SDL_Surface * this_screen) {
  //draw the tolerance string and box
  int x = x_global_replace_menu + 2;
  int y = y_global_replace_menu + 20;

  print_string ("Tolerance:", black, white, x, y);
  draw_down_button (screen, x_global_replace_menu + 80, y_global_replace_menu + 18, 25, 14);
  print_string (numeric_dialog_boxes[global_tolerance].dialog_text, black, x + 80, y);

  //draw the pattern file name.
  int x = x_global_replace_menu + 2;
  int y = y_global_replace_menu + 262;
  char *string = current_pattern.object_mem ? &pattern_file_name : "None";
  print_string ("Pattern:", black, white, x, y);
  draw_empty_menu (screen, white, x + 58, y_global_replace_menu + 260,172, 14);
  print_string(string, black, white, x + 60, y);
}

void draw_file_menu(SDL_Surface * this_screen) {
  int x, y, my_pitch,i,j,k,l;
  char cur_char;
  char str[120];
  Uint8 *screen_buffer;
  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;

  draw_empty_menu (screen, white, x_file_menu, y_file_menu,x_file_menu_lenght, y_file_menu_lenght);
	print_string (&cur_dir, black, white, x_file_menu + 2,y_file_menu+2);

  draw_empty_menu (screen, white, x_file_menu+2, y_file_menu+14,x_file_menu_lenght-4, y_file_menu_lenght-35);
  //ok, now, print the files from the current directory...
  if(no_of_files-start_file_offset<18)start_file_offset=no_of_files-18;
  if(start_file_offset<0)start_file_offset=0;
  l=0;
  for(i=start_file_offset;i<start_file_offset+18;i++)
  	{
		j=0;
		k=0;
		//if it is a directory, add a / before
		if(file_names[i].is_directory==1)
			{
				*(str+k)='/';
				k++;
			}
		while(j<55)
		{
			cur_char=file_names[i].file_name[j];
			*(str+k)=cur_char;
			if(cur_char==0)break;
			j++;
			k++;
		}
		*(str+k)=0;
		print_string (str, black, white, x_file_menu + 2,y_file_menu+16+(l*12));
		l++;
	}
print_string ("<<", black, white, x_file_menu + 4,y_file_menu+y_file_menu_lenght-34);
print_string (">>", black, white, x_file_menu + x_file_menu_lenght-20,y_file_menu+y_file_menu_lenght-34);

//draw the "current file" dialogue box
    draw_down_button (screen, x_file_menu + 2,y_file_menu+y_file_menu_lenght-18, x_file_menu_lenght-110, 14);
print_string (&cur_file_name, black, white, x_file_menu + 4,y_file_menu+y_file_menu_lenght-16);

//draw the load/save button
  draw_empty_menu (screen, white, x_file_menu_lenght+x_file_menu-104, y_file_menu+y_file_menu_lenght-18,35, 14);
  if(!save_file)print_string ("Load", black, white, x_file_menu_lenght+x_file_menu-102,y_file_menu+y_file_menu_lenght-16);
  else print_string ("Save", black, white, x_file_menu_lenght+x_file_menu-102,y_file_menu+y_file_menu_lenght-16);

//draw the cancel button
  draw_empty_menu (screen, white, x_file_menu_lenght+x_file_menu-64, y_file_menu+y_file_menu_lenght-18,50, 14);
  print_string ("Cancel", black, white, x_file_menu_lenght+x_file_menu-62,y_file_menu+y_file_menu_lenght-16);
}

/*--------------------
 Check menus functions
 *------------------*/
void check_new_terrain_menu (char text_input_char) {
  //right mouse button kills the menu (cancel)
  if (long_pressed_button_r == 1)
    show_new_terrain_menu = 0;
  else if (buttonPressed(x_replace_menu, y_replace_menu, 70, 80, 50, 14)) || text_input_char == SDLK_ESCAPE) //check the cancel button
    show_new_terrain_menu = 0;
  else if (buttonPressed(x_replace_menu, y_replace_menu, 40, 80, 20, 14)) || text_input_char == SDLK_RETURN) //check the OK button
  {
    int color_to_fill;
    int i = 0;
    color_to_fill = atoi(numeric_dialog_boxes[base_height_dialog].dialog_text);
    show_new_terrain_menu = 0;
    WIDTH = atoi (numeric_dialog_boxes[x_map_size_dialog].dialog_text);
    HEIGHT = atoi (numeric_dialog_boxes[y_map_size_dialog].dialog_text);
    //do a bounds check
    if (WIDTH > numeric_dialog_boxes[x_map_size_dialog].max_number) WIDTH = numeric_dialog_boxes[x_map_size_dialog].max_number;
    if (WIDTH < numeric_dialog_boxes[x_map_size_dialog].min_number) WIDTH = numeric_dialog_boxes[x_map_size_dialog].min_number;
    if (HEIGHT > numeric_dialog_boxes[y_map_size_dialog].max_number) HEIGHT = numeric_dialog_boxes[y_map_size_dialog].max_number;
    if (HEIGHT < numeric_dialog_boxes[y_map_size_dialog].min_number) HEIGHT = numeric_dialog_boxes[y_map_size_dialog].min_number;
    if (color_to_fill > 255 || color_to_fill < 0)
      color_to_fill = 0;

    //everything is OK now
    allocate_mem(WIDTH, HEIGHT);

    if(!terrain_height)return;
    for (i = 0; i < HEIGHT * WIDTH; i++)
      *(terrain_height + i) = color_to_fill;
  }
  else
    //check to see if the x_map_size_dialog got the focus
  if (buttonPressed(x_replace_menu, y_replace_menu, 52, 18, 42, 14)) {
    numeric_dialog_boxes[base_height_dialog].has_focus = 0;
    numeric_dialog_boxes[y_map_size_dialog].has_focus = 0;
    numeric_dialog_boxes[x_map_size_dialog].has_focus = 1;
    numeric_dialog_boxes[x_map_size_dialog].text_offset = 0;
  }
	else if (buttonPressed(x_replace_menu, y_replace_menu, 52, 36, 42, 14)) { //check to see if the y_map_size_dialog got the focus
    numeric_dialog_boxes[base_height_dialog].has_focus = 0;
    numeric_dialog_boxes[y_map_size_dialog].has_focus = 1;
    numeric_dialog_boxes[y_map_size_dialog].text_offset = 0;
    numeric_dialog_boxes[x_map_size_dialog].has_focus = 0;
  }
  else if (buttonPressed(x_replace_menu, y_replace_menu, 90, 54, 24, 14)) {
    numeric_dialog_boxes[base_height_dialog].has_focus = 1;
    numeric_dialog_boxes[base_height_dialog].text_offset = 0;
    numeric_dialog_boxes[y_map_size_dialog].has_focus = 0;
    numeric_dialog_boxes[x_map_size_dialog].has_focus = 0;
  }

  //check to see for the tab
  if (text_input_char == SDLK_TAB) {
    if (numeric_dialog_boxes[base_height_dialog].has_focus) {
      numeric_dialog_boxes[x_map_size_dialog].has_focus = 1;
      numeric_dialog_boxes[x_map_size_dialog].text_offset = 0;
      numeric_dialog_boxes[y_map_size_dialog].has_focus = 0;
      numeric_dialog_boxes[base_height_dialog].has_focus = 0;
    }
    else if (numeric_dialog_boxes[x_map_size_dialog].has_focus) {
      numeric_dialog_boxes[x_map_size_dialog].has_focus = 0;
      numeric_dialog_boxes[y_map_size_dialog].has_focus = 1;
      numeric_dialog_boxes[y_map_size_dialog].text_offset = 0;
      numeric_dialog_boxes[base_height_dialog].has_focus = 0;
    }
    else if (numeric_dialog_boxes[y_map_size_dialog].has_focus) {
      numeric_dialog_boxes[x_map_size_dialog].has_focus = 0;
      numeric_dialog_boxes[y_map_size_dialog].has_focus = 0;
      numeric_dialog_boxes[base_height_dialog].has_focus = 1;
      numeric_dialog_boxes[base_height_dialog].text_offset = 0;
    }
  }

  //now, check to see if we get any character
  if (text_input_char) {
    int dialog_text_offset;

    if (numeric_dialog_boxes[base_height_dialog].has_focus == 1) {
			if (isNumeric(text_input_char) && !maxLengthExcedeed(numeric_dialog_boxes[base_height_dialog])) {
					dialog_text_offset = numeric_dialog_boxes[base_height_dialog].text_offset;
					numeric_dialog_boxes[base_height_dialog].dialog_text[dialog_text_offset] = text_input_char;
					numeric_dialog_boxes[base_height_dialog].dialog_text[dialog_text_offset + 1] = 0;
					numeric_dialog_boxes[base_height_dialog].text_offset++;
      }
      else if (text_input_char == SDLK_BACKSPACE && numeric_dialog_boxes[base_height_dialog].text_offset > 0) {
				numeric_dialog_boxes[base_height_dialog].text_offset--;
				numeric_dialog_boxes[base_height_dialog].
	  		dialog_text[numeric_dialog_boxes[base_height_dialog].text_offset] = 0;
      }
    }

    //check the x_map_size_dialog
    if (numeric_dialog_boxes[x_map_size_dialog].has_focus == 1) {
			if (isNumeric(text_input_char) && !maxLengthExcedeed(numeric_dialog_boxes[x_map_size_dialog])) {
					dialog_text_offset = numeric_dialog_boxes[x_map_size_dialog].text_offset;
					numeric_dialog_boxes[x_map_size_dialog].dialog_text[dialog_text_offset] = text_input_char;
					numeric_dialog_boxes[x_map_size_dialog].dialog_text[dialog_text_offset + 1] = 0;
					numeric_dialog_boxes[x_map_size_dialog].text_offset++;
      }
      else if (text_input_char == SDLK_BACKSPACE && numeric_dialog_boxes[x_map_size_dialog].text_offset > 0) {
				numeric_dialog_boxes[x_map_size_dialog].text_offset--;
				numeric_dialog_boxes[x_map_size_dialog].dialog_text[numeric_dialog_boxes[x_map_size_dialog].text_offset] = 0;
      }
    }
    //check the y_map_size_dialog
    if (numeric_dialog_boxes[y_map_size_dialog].has_focus == 1) {
			if (isNumeric(text_input_char) && !maxLengthExcedeed(numeric_dialog_boxes[y_map_size_dialog])) {
					dialog_text_offset = numeric_dialog_boxes[y_map_size_dialog].text_offset;
					numeric_dialog_boxes[y_map_size_dialog].dialog_text[dialog_text_offset] = text_input_char;
					numeric_dialog_boxes[y_map_size_dialog].dialog_text[dialog_text_offset + 1] = 0;
					numeric_dialog_boxes[y_map_size_dialog].text_offset++;
      }
      else if (text_input_char == SDLK_BACKSPACE && numeric_dialog_boxes[y_map_size_dialog].text_offset > 0) {
				numeric_dialog_boxes[y_map_size_dialog].text_offset--;
				numeric_dialog_boxes[y_map_size_dialog].
	  		dialog_text[numeric_dialog_boxes[y_map_size_dialog].text_offset] = 0;
      }
    }
  }
}

void check_generate_terrain_menu (char text_input_char) {
  //right mouse button kills the menu (cancel)
  if (long_pressed_button_r == 1)
  	show_generate_terrain_menu = 0;
	//check the overwrite terrain button
  else if (buttonPressed(x_replace_menu, y_replace_menu, 2, 40, 14, 14))
    overwrite_terrain = !overwrite_terrain;
	//check the random seed button
  else if (buttonPressed(x_replace_menu, y_replace_menu, 140, 18, 50, 14)) {
    int this_seed;
    this_seed = rand ();
    this_seed = this_seed * rand ();
    sprintf (numeric_dialog_boxes[seed_dialog].dialog_text, "%d", this_seed);
    numeric_dialog_boxes[seed_dialog].text_offset = 0;
  }
	//check the cancel button
  else if (buttonPressed(x_replace_menu, y_replace_menu, 70, 80, 50, 14) || text_input_char == SDLK_ESCAPE)
    show_generate_terrain_menu = 0;
	//check the OK button
  else if (buttonPressed(x_replace_menu, y_replace_menu, 40, 80, 20, 14) || text_input_char == SDLK_RETURN) {
    seed = atoi (numeric_dialog_boxes[seed_dialog].dialog_text);
    srand (atoi (numeric_dialog_boxes[seed_dialog].dialog_text));

    /*if(overwrite_terrain)overdraw_terrain(WIDTH, HEIGHT);
    else make_terrain (WIDTH, HEIGHT);*/
    show_generate_terrain_menu = 0;
  }
	//now, check to see if we get any character
  else if (text_input_char) {
    int dialog_text_offset;

		if (isNumeric(text_input_char) && !maxLengthExcedeed(numeric_dialog_boxes[seed_dialog])) {
      	dialog_text_offset = numeric_dialog_boxes[seed_dialog].text_offset;
      	numeric_dialog_boxes[seed_dialog].dialog_text[dialog_text_offset] = text_input_char;
      	numeric_dialog_boxes[seed_dialog].dialog_text[dialog_text_offset + 1] = 0;
      	numeric_dialog_boxes[seed_dialog].text_offset++;
    }
    else if (text_input_char == SDLK_BACKSPACE && numeric_dialog_boxes[seed_dialog].text_offset > 0) {
      numeric_dialog_boxes[seed_dialog].text_offset--;
      numeric_dialog_boxes[seed_dialog].
			dialog_text[numeric_dialog_boxes[seed_dialog].text_offset] = 0;
    }
  }
}

void check_view_menu (char text_input_char) {
  //right mouse button kills the menu (cancel)
  if (long_pressed_button_r == 1)
    show_view_menu = 0;

  if (buttonPressed(x_replace_menu, y_replace_menu, 2, 20, 14, 14)) //check the toolbar button
    tool_bar = !tool_bar;
  else if (buttonPressed(x_replace_menu, y_replace_menu, 2, 40, 14, 14)) //check the minimap button
    mini_map = !mini_map;

  if (buttonPressed(x_replace_menu, y_replace_menu, 2, 60, 14, 14)) //check the statusbar button
    status_bar = !status_bar;
  else if (buttonPressed(x_replace_menu, y_replace_menu, 2,  80, 14, 14)) grid = 0;   //check the grid off button
  else if (buttonPressed(x_replace_menu, y_replace_menu, 2, 100, 14, 14)) grid = 16;  //check the grid 16 button
  else if (buttonPressed(x_replace_menu, y_replace_menu, 2, 120, 14, 14)) grid = 32;  //check the grid 32 button
  else if (buttonPressed(x_replace_menu, y_replace_menu, 2, 140, 14, 14)) grid = 64;  //check the grid 64 button
  else if (buttonPressed(x_replace_menu, y_replace_menu, 2, 160, 14, 14)) grid = 128; //check the grid 128 button
  else if (buttonPressed(x_replace_menu, y_replace_menu, 2, 180, 14, 14)) grid = 256; //check the grid 256 button
  else if (buttonPressed(x_replace_menu, y_replace_menu, 50, 220, 20, 14)) //check the OK button
    show_view_menu = 0;
}

void check_rotate_menu (char text_input_char) {
  //right mouse button kills the menu (cancel)
  if (long_pressed_button_r == 1)
    show_rotate_menu = 0;

  if (buttonPressed(x_replace_menu, y_replace_menu, 2, 20, 14, 14)) rotation_type = rotation_flip_x; //check the Hor. flip
  else if (buttonPressed(x_replace_menu, y_replace_menu, 2, 40, 14, 14)) rotation_type = rotation_flip_y; //check Ver. flip

  if (buttonPressed(x_replace_menu, y_replace_menu, 2, 60, 14, 14)) rotation_type = rotation_flip_z; //check the Height flip
  else if (buttonPressed(x_replace_menu, y_replace_menu, 2, 80, 14, 14)) rotation_type = rotation_CW_90; //check 90 CW rotation
  else if (buttonPressed(x_replace_menu, y_replace_menu, 2, 100, 14, 14)) rotation_type = rotation_CCW_90; //check the 90 CCW rotation
  else if (buttonPressed(x_replace_menu, y_replace_menu, 2, 120, 14, 14)) rotation_type = rotation_180; //check the 180 rotation
  else if (buttonPressed(x_replace_menu, y_replace_menu, 70, 140, 20, 14)) //check the OK button
	{
		switch(rotation_type) {
			case rotation_flip_x: flip_x(); break;
			case rotation_flip_y: flip_y(); break;
			case rotation_flip_z: flip_z(); break;
			case rotation_CW_90: rotate_90_CW(); break;
			case rotation_CCW_90: rotate_90_CCW(); break;
			case rotation_180: rotate_180(); break;
		}

		show_rotate_menu = 0;
	}
}

void check_replace_menu (char text_input_char) {
  //right mouse button kills the menu (cancel)
  if (long_pressed_button_r == 1)
    show_replace_menu = 0;
  else if (buttonPressed(x_replace_menu, y_replace_menu, 40, 60, 14, 14)) temp_tolerance_mode = greater; //check the greater than tolerance mode
  else if (buttonPressed(x_replace_menu, y_replace_menu, 40, 80, 14, 14)) temp_tolerance_mode = leaser; //check the leaser than tolerance mode
  else if (buttonPressed(x_replace_menu, y_replace_menu, 40, 100, 14, 14)) temp_tolerance_mode = greater_or_leaser; //check the leaser or greater tolerance mode
  else if (buttonPressed(x_replace_menu, y_replace_menu, 40, 140, 14, 14)) temp_tolerance_replace_mode = tolerance_replace_plus; //check the greater replace mode
  else if (buttonPressed(x_replace_menu, y_replace_menu, 40, 160, 14, 14)) temp_tolerance_replace_mode = tolerance_replace_minus; //check the leaser replace mode
  else if (buttonPressed(x_replace_menu, y_replace_menu, 40, 180, 14, 14)) temp_tolerance_replace_mode = tolerance_replace_equal; //check the equal replace mode
  else if (buttonPressed(x_replace_menu, y_replace_menu, 40, 220, 14, 14)) temp_tolerance_replace_mode_2 = replace_mode_solid; //check the pattern replace_mode_2
  else if (buttonPressed(x_replace_menu, y_replace_menu, 40, 240, 14, 14)) temp_tolerance_replace_mode_2 = replace_mode_pattern; //check the pattern replace_mode_2
  else if (buttonPressed(x_replace_menu, y_replace_menu, 60, 280, 50, 14) || text_input_char == SDLK_ESCAPE) //check the cancel button
    show_replace_menu = 0;
	//check the load pattern button
  else if (buttonPressed(x_replace_menu, y_replace_menu, 120, 280, 110, 14)) {
		SDL_Event event;

		if(current_pattern.object_mem) {
				free(current_pattern.object_mem);
				current_pattern.object_mem=0;
		}

		load_object=2;//tell the file open save function to load a pattern
		long_pressed_button_l = 0;
		DoFileOpenSave (0);
    while (SDL_PollEvent (&event));	//clears all the events
	}

  else if (buttonPressed(x_replace_menu, y_replace_menu, 30, 280, 20, 14) || text_input_char == SDLK_RETURN) //check the OK button
  {
    int box_tolerance;
    box_tolerance = atoi (numeric_dialog_boxes[tolerance].dialog_text);
    //bounds checking
    if (box_tolerance > numeric_dialog_boxes[tolerance].max_number)
      box_tolerance = numeric_dialog_boxes[tolerance].max_number;
    else if (box_tolerance < numeric_dialog_boxes[tolerance].min_number)
      box_tolerance = numeric_dialog_boxes[tolerance].min_number;

    tolerance_value = box_tolerance;
    tolerance_mode = temp_tolerance_mode;
    tolerance_replace_mode = temp_tolerance_replace_mode;
    tolerance_replace_mode_2 = temp_tolerance_replace_mode_2;
    show_replace_menu = 0;
  }
	//now, check to see if we get any character
  else if (text_input_char) {
    int dialog_text_offset;

		if (isNumeric(text_input_char) && !maxLengthExcedeed(numeric_dialog_boxes[tolerance])) {
      	dialog_text_offset = numeric_dialog_boxes[tolerance].text_offset;
      	numeric_dialog_boxes[tolerance].dialog_text[dialog_text_offset] = text_input_char;
      	numeric_dialog_boxes[tolerance].dialog_text[dialog_text_offset + 1] = 0;
      	numeric_dialog_boxes[tolerance].text_offset++;
    }
    else if (text_input_char == SDLK_BACKSPACE && numeric_dialog_boxes[tolerance].text_offset > 0) {
      numeric_dialog_boxes[tolerance].text_offset--;
      numeric_dialog_boxes[tolerance].dialog_text[numeric_dialog_boxes[tolerance].text_offset] = 0;
    }
  }
}

void check_global_replace_menu (char text_input_char) {
  //right mouse button kills the menu (cancel)
  if (long_pressed_button_r == 1)
    show_global_replace_menu = 0;
  else if (buttonPressed(x_global_replace_menu, y_global_replace_menu, 40, 60, 14, 14)) temp_global_tolerance_mode = greater; //check the greater than tolerance mode
  else if (buttonPressed(x_global_replace_menu, y_global_replace_menu, 40, 80, 14, 14)) temp_global_tolerance_mode = leaser; //check the leaser than tolerance mode
  else if (buttonPressed(x_global_replace_menu, y_global_replace_menu, 40, 100, 14, 14)) temp_global_tolerance_mode = greater_or_leaser; //check the leaser or greater tolerance mode
  else if (buttonPressed(x_global_replace_menu, y_global_replace_menu, 40, 140, 14, 14)) temp_global_tolerance_replace_mode = tolerance_replace_plus; //check the greater replace mode
  else if (buttonPressed(x_global_replace_menu, y_global_replace_menu, 40, 160, 14, 14)) temp_global_tolerance_replace_mode = tolerance_replace_minus; //check the leaser replace mode
  else if (buttonPressed(x_global_replace_menu, y_global_replace_menu, 40, 180, 14, 14)) temp_global_tolerance_replace_mode = tolerance_replace_equal; //check the equal replace mode
  else if (buttonPressed(x_global_replace_menu, y_global_replace_menu, 40, 220, 14, 14)) temp_global_tolerance_replace_mode_2 = replace_mode_solid; //check the pattern replace_mode_2
  else if (buttonPressed(x_global_replace_menu, y_global_replace_menu, 40, 240, 14, 14)) temp_global_tolerance_replace_mode_2 = replace_mode_pattern; //check the pattern replace_mode_2

	//check the cancel button
	else if (buttonPressed(x_global_replace_menu, y_global_replace_menu, 60, 280, 50, 14) || text_input_char == SDLK_ESCAPE)
    show_global_replace_menu = 0;
	//check the load pattern button
  else if (buttonPressed(x_global_replace_menu, y_global_replace_menu, 120, 280, 110, 14) {
		SDL_Event event;
		if(current_pattern.object_mem) {
				free(current_pattern.object_mem);
				current_pattern.object_mem=0;
		}

		load_object=2;//tell the file open save function to load a pattern
		long_pressed_button_l = 0;
		DoFileOpenSave (0);
    while (SDL_PollEvent (&event));	//clears all the events
	}

	//check the OK button
  else if (buttonPressed(x_global_replace_menu, y_global_replace_menu, 30, 280, 20, 14) || text_input_char == SDLK_RETURN) {
    int box_tolerance = atoi (numeric_dialog_boxes[global_tolerance].dialog_text);
    //bounds checking
    if (box_tolerance > numeric_dialog_boxes[global_tolerance].max_number)
      box_tolerance = numeric_dialog_boxes[global_tolerance].max_number;
    else if (box_tolerance < numeric_dialog_boxes[global_tolerance].min_number)
      box_tolerance = numeric_dialog_boxes[global_tolerance].min_number;

    global_tolerance_value = box_tolerance;
    global_tolerance_mode = temp_global_tolerance_mode;
    global_tolerance_replace_mode = temp_global_tolerance_replace_mode;
    global_tolerance_replace_mode_2 = temp_global_tolerance_replace_mode_2;
    show_global_replace_menu = 0;
  }

	//now, check to see if we get any character
  else if (text_input_char) {
    int dialog_text_offset;

    if (isNumeric(text_input_char) && !maxLengthExcedeed(numeric_dialog_boxes[global_tolerance])) {
      	dialog_text_offset = numeric_dialog_boxes[global_tolerance].text_offset;
      	numeric_dialog_boxes[global_tolerance].dialog_text[dialog_text_offset] = text_input_char;
      	numeric_dialog_boxes[global_tolerance].dialog_text[dialog_text_offset + 1] = 0;
      	numeric_dialog_boxes[global_tolerance].text_offset++;
    }
		else if (text_input_char == SDLK_BACKSPACE && numeric_dialog_boxes[global_tolerance].text_offset > 0) {
      numeric_dialog_boxes[global_tolerance].text_offset--;
      numeric_dialog_boxes[global_tolerance].
			dialog_text[numeric_dialog_boxes[global_tolerance].text_offset] = 0;
    }
  }
}

void check_object_menu (char text_input_char) {
	//right mouse button kills the menu (cancel)
  if(long_pressed_button_r == 1)
  	show_object_menu = 0;
  else if(buttonPressed(x_object_menu, y_object_menu, 40, 40, 14, 14)) object_mode = put_object; //check the put mode
  else if(buttonPressed(x_object_menu, y_object_menu, 40, 60, 14, 14)) object_mode = add_object; //check the leaser than mode
  else if (buttonPressed(x_object_menu, y_object_menu, 40, 80, 14, 14)) object_mode = sub_object;//check the leaser or greater mode

  //check the cancel and OK buttons
  if (buttonPressed(x_object_menu, y_object_menu, 90, 100, 50, 14) || text_input_char == SDLK_ESCAPE) show_object_menu = 0;
  else if (buttonPressed(x_object_menu, y_object_menu, 60, 100, 20, 14) || text_input_char == SDLK_RETURN) show_object_menu = 0;
}

void check_error_menu (char text_input_char) {
  //right mouse button kills the menu (cancel)
  if (long_pressed_button_r == 1 || text_input_char==SDLK_RETURN || text_input_char==SDLK_ESCAPE) view_error_menu = 0;
  else if (buttonPressed(x_error_menu, y_error_menu, 202, 54, 14, 14)) view_error_menu = 0;
}

void check_file_menu (unsigned char text_input_char) {
  //right mouse button kills the menu (cancel)
  if (long_pressed_button_r == 1)
    view_file_menu = 0;
  else
    //check the load/save button

  if (buttonPressed(x_file_menu, y_file_menu, -104, -18, 35, 14) || text_input_char == SDLK_RETURN) {
		if(save_file)SaveFile(&cur_file_name);
		else if(load_object)do_load_object(&cur_file_name,&current_object);
		else LoadFile(&cur_file_name);
	    view_file_menu = 0;
	}

	//check to see if we selected any file/dir
  else
  if (long_pressed_button_l == 1 && x_mouse_pos >= x_file_menu+2
	 && x_mouse_pos < x_file_menu+x_file_menu_lenght-4
	 && y_mouse_pos >= y_file_menu+14
	 && y_mouse_pos < y_file_menu+y_file_menu_lenght-35)
	 {
		 int i;
		 int j=0;
		 char cur_char;
		 i=((y_mouse_pos-y_file_menu-16)/12)+start_file_offset;

		 //see if it is dir, and, if so, change the current dir
		 if(file_names[i].is_directory)ChangeDir(file_names[i].file_name);
		 else
		 	while(1) {
		 		cur_char=file_names[i].file_name[j];
		 		*(cur_file_name+j)=cur_char;
		 		if(cur_char==0)break;
		 		j++;
			}
	 }
	 //check for the cancel button
	 else if (buttonPressed(x_file_menu, y_file_menu, -62, -18, 50, 14) || text_input_char == SDLK_ESCAPE)
		 	view_file_menu=0;
	else if (buttonPressed(x_file_menu, y_file_menu, 4, -34, 14, 14)) start_file_offset-=18; //check for the << button
	else if (buttonPressed(x_file_menu, y_file_menu, -20, -34, 14, 14)) start_file_offset+=18; //check for the >> button
	//now, check to see if we get any character
  else if (text_input_char) {
    int dialog_text_offset=0;

		while(1) {
			if(cur_file_name[dialog_text_offset]==0)break;
			dialog_text_offset++;
		}

    //check to see if it is a numeric char, and if we didn't exceede the max lenght limit
    if (text_input_char == SDLK_BACKSPACE && dialog_text_offset > 0)
			cur_file_name[dialog_text_offset-1]=0;
    else if (text_input_char >=32 && text_input_char<128 && dialog_text_offset<119) {
    	cur_file_name[dialog_text_offset]=text_input_char;
    	cur_file_name[dialog_text_offset+1]=0;
		}
  }
}

int buttonPressed(int xMenu, int yMenu, int x, int y, int w, int h) {
	return (long_pressed_button_l == 1 && x_mouse_pos >= xMenu + x
	 && x_mouse_pos < xMenu + x + w
	 && y_mouse_pos >= yMenu + y
	 && y_mouse_pos < yMenu + y + h) ? 1 : 0;
}

int isNumeric(char *charToTest) {
	return charToTest >= '0' && charToTest <= '9' ? 1 : 0;
}

int maxLengthExcedeed(numeric_dialog_box_struct dialogBox) {
	return dialogBox.text_offset >= dialogBox.dialog_lenght ? 1 : 0;
}

char *TOOLBARBMP_PATH_LINUX = "/home/alejandro/programs/height-map-editor/res/toolbar.bmp";
char *TOOLBARBMP_PATH_MAC = "/Users/alejandro/programs/height-map-editor/res/toolbar.bmp";

void load_tool_bar() {
	SDL_Surface *tempToolbarBmp = SDL_LoadBMP(TOOLBARBMP_PATH_LINUX);
	tool_bar_mem = SDL_DisplayFormat(tempToolbarBmp);
	return;

	char *temp_pointer = tool_bar_mem;
	int f_size, i;
	FILE *f = fopen (toolbarBmp, "rb");
	fseek (f, 0, SEEK_END);
	f_size = ftell (f);

	//ok, allocate memory for it
	tool_bar_mem = calloc ( f_size, sizeof(char) );
	handle_tool_bar_mem=tool_bar_mem;
	fseek (f, 0, SEEK_SET);
	fread (tool_bar_mem, 1, f_size, f);
	fclose (f);

	tool_bar_mem += 18;		//x lenght is at offset+18
	x_tool_bar_bmp = *((int *) tool_bar_mem);

	tool_bar_mem += 4;		//y lenght is at offset+22
	y_tool_bar_bmp = *((int *) tool_bar_mem);

	tool_bar_mem += 46 - 22;	//y lenght is at offset+22
	tool_bar_colors_no = *((int *) tool_bar_mem);

	tool_bar_mem += 54 - 46;	//ok, now, we are at the color pallete

	//get the color pallete
	for (i = 0; i < tool_bar_colors_no; i++) {
		colors[i + 128].b = *(tool_bar_mem++);
		colors[i + 128].g = *(tool_bar_mem++);
		colors[i + 128].r = *(tool_bar_mem++);
		tool_bar_mem++;
	}

	temp_pointer=tool_bar_mem;
	for (i = 0; i < x_tool_bar_bmp * y_tool_bar_bmp; i++)
		*(tool_bar_mem) = *(++tool_bar_mem) + 128;
	tool_bar_mem = temp_pointer;
}

void drawWindowTitle(Menu *menu) {
	SDL_Rect rectangleMenu;
	rectangleMenu.w = menu->width;
	rectangleMenu.h = 19;
	rectangleMenu.x = menu->x;
	rectangleMenu.y = menu->y;

    SDL_SetRenderDrawColor(renderer, 0, 0, 100, 255);
    SDL_RenderFillRect(renderer, &rectangleMenu);
    SDL_RenderPresent(renderer);

	printString(menu->title, menu->x + 1, menu->y + 1);
}

void drawTextBox(TextBox *textbox) {
	DialogBox *dialogBox = textbox->dialogBox;
	int barHeight = 19;
	int textWidth;

	SDL_Texture *printTexture = printString(textbox->title, textbox->x, textbox->y + barHeight);
    SDL_QueryTexture(printTexture, NULL, NULL, &textWidth, NULL);

	SDL_Rect rectangleTextBox;
	rectangleTextBox.w = textbox->width;
	rectangleTextBox.h = textbox->height;
	rectangleTextBox.x = textbox->x + textWidth + 1;
	rectangleTextBox.y = textbox->y + barHeight;

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderFillRect(renderer, &rectangleTextBox);
    SDL_RenderPresent(renderer);

	/*if (dialogBox->has_focus)
		draw_down_button (screen, menu->x + textbox->x, menu->y + textbox->y, textbox->width, textbox->height);
	else
		draw_up_button (screen, menu->x + textbox->x, menu->y + textbox->y, textbox->width, textbox->height);*/

	printString("1000", rectangleTextBox.x + 2, rectangleTextBox.y);
}

void drawTextBoxes(TextBoxContainer *textBoxContainer) {
	int i;

	for(i = 0; i < textBoxContainer->textBoxesNo; i++) {
		drawTextBox(textBoxContainer->textBoxes + i);
	}
}

void drawButton(Button *button) {
	/*Menu *menu = button->menu;
	int barWidth = 19;

	SDL_Rect buttonBox;
	buttonBox.w = button->width + (button->padding * 2);
	buttonBox.h = button->height + (button->padding * 2);
	buttonBox.x = menu->x + button->x + 2;
	buttonBox.y = menu->y + button->y + barWidth;

	SDL_FillRect(currentScreen, &buttonBox, YELLOW);
	printString(currentScreen, button->title, menu->x + button->x, menu->y + button->y + barWidth);*/
}

void drawButtons(ButtonContainer *buttonContainer) {
	/*int i;

	for(i = 0; i < buttonContainer->buttonsNo; i++) {
		drawButton(buttonContainer->buttons + i, currentScreen);
	}*/
}

void drawDialogWindow(Menu *menu) {
	SDL_Rect rectangleMenu;
	rectangleMenu.x = menu->x;
	rectangleMenu.y = menu->y;
	rectangleMenu.w = menu->width;
	rectangleMenu.h = menu->height;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rectangleMenu);
    SDL_RenderPresent(renderer);

	drawWindowTitle(menu);
}
