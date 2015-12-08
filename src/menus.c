#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_events.h>

#include "font.h"
#include "menus.h"
#include "load_widgets.h"

void draw_file_menu(SDL_Surface * this_screen) {
    int x,y,i,j,k,l = 0;
    char cur_char;
    char str[120];
    Uint8 *screen_buffer = (Uint8 *) this_screen->pitch;

    int x1 = x_file_menu;
    int y1 = y_file_menu;
    int width = x_file_menu_lenght;
    int height = y_file_menu_lenght;
    int x2 = x_file_menu + width;
    int y2 = y_file_menu + height;

    draw_empty_menu (screen, white, width, y_file_menu,width, height);
    print_string (&cur_dir, black, white, x_file_menu + 2,y_file_menu+2);

    draw_empty_menu (screen, white, x_file_menu+2, y_file_menu+14,width-4, height-35);

    //ok, now, print the files from the current directory...
    if(no_of_files-start_file_offset<18) start_file_offset=no_of_files-18;
    if(start_file_offset<0)start_file_offset=0;

    for(i=start_file_offset;i<start_file_offset+18;i++) {
		j=0;
		k=0;

		//if it is a directory, add a / before
		if(file_names[i].is_directory==1) {
		    *(str+k)='/';
			k++;
		}

		while(j<55) {
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

    print_string ("<<", black, white, x_file_menu + 4,y2-34);
    print_string (">>", black, white, x2-20, y2-34);

    //draw the "current file" dialogue box
    draw_down_button (screen, x_file_menu + 2, y2-18, width-110, 14);
    print_string (&cur_file_name, black, white, x_file_menu + 4, y2-16);

    //draw the load/save button
    char *text = save_file ? "Save" : "Load";
    draw_empty_menu (screen, white, x2-104, y2-18, 35, 14);
    print_string (text, black, white, x2-102, y2-16);

    //draw the cancel button
    draw_empty_menu (screen, white, x2-64, y2-18,50, 14);
    print_string ("Cancel", black, white, x2-62, y2-16);
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
