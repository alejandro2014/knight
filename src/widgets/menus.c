#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_events.h>

#include "font.h"
#include "menus.h"
#include "load_widgets.h"

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

void cb_generateTerrain_overwriteTerrain() {
    overwrite_terrain = !overwrite_terrain;
}

void cb_generateTerrain_seed() {
    int this_seed;
    this_seed = rand ();
    this_seed = this_seed * rand ();
    sprintf (numeric_dialog_boxes[seed_dialog].dialog_text, "%d", this_seed);
    numeric_dialog_boxes[seed_dialog].text_offset = 0;
}

void cb_generateTerrain_okButton() {
  seed = atoi (numeric_dialog_boxes[seed_dialog].dialog_text);
  srand (atoi (numeric_dialog_boxes[seed_dialog].dialog_text));

  if(overwrite_terrain)overdraw_terrain(WIDTH, HEIGHT);
  else make_terrain (WIDTH, HEIGHT);
  show_generate_terrain_menu = 0;
}

void cb_generateTerrain_cancelButton() {
    show_generate_terrain_menu = 0;
}

void cb_globalReplace_ok() {
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

void cb_globalReplace_changePattern() {
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

void cb_newTerrain_xSize() {
    numeric_dialog_boxes[base_height_dialog].has_focus = 0;
    numeric_dialog_boxes[y_map_size_dialog].has_focus = 0;
    numeric_dialog_boxes[x_map_size_dialog].has_focus = 1;
    numeric_dialog_boxes[x_map_size_dialog].text_offset = 0;
}

void cb_newTerrain_ySize() {
    numeric_dialog_boxes[base_height_dialog].has_focus = 0;
    numeric_dialog_boxes[y_map_size_dialog].has_focus = 1;
    numeric_dialog_boxes[y_map_size_dialog].text_offset = 0;
    numeric_dialog_boxes[x_map_size_dialog].has_focus = 0;
}

void cb_newTerrain_baseHeight() {
    numeric_dialog_boxes[base_height_dialog].has_focus = 1;
    numeric_dialog_boxes[base_height_dialog].text_offset = 0;
    numeric_dialog_boxes[y_map_size_dialog].has_focus = 0;
    numeric_dialog_boxes[x_map_size_dialog].has_focus = 0;
}

void cb_newTerrain_ok() {
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

void cb_newTerrain_cancel() {
    show_new_terrain_menu = 0;
}

void cb_replace_changePattern() {
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

void cb_replace_ok() {
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

void cb_view_toolbar() { tool_bar = !tool_bar; }
void cb_view_minimap() { mini_map = !mini_map; }
void cb_view_statusBar() { status_bar = !status_bar; }
void cb_view_gridOff() { grid = 0; }
void cb_view_grid16() { grid = 16; }
void cb_view_grid32() { grid = 32; }
void cb_view_grid64() { grid = 64; }
void cb_view_grid128() { grid = 128; }
void cb_view_grid256() { grid = 256; }
void cb_view_okButton() { show_view_menu = 0; }

void cb_rotate_x() { rotation_type = rotation_flip_x; }
void cb_rotate_y() { rotation_type = rotation_flip_y; }
void cb_rotate_z() { rotation_type = rotation_flip_z; }
void cb_rotate_90() { rotation_type = rotation_CW_90; }
void cb_rotate_270() { rotation_type = rotation_CCW_90; }
void cb_rotate_180() { rotation_type = rotation_180; }
void cb_rotate_ok() {
    change_cursor(cursor_wait);

    //TODO Fix the calls
    /*switch(rotation_type) {
        case rotation_flip_x: api_(); break;
        case rotation_flip_y: api_flipY(); break;
        case rotation_flip_z: api_flipZ(); break;
        case rotation_CW_90: api_rotate(90); break;
        case rotation_CCW_90: api_rotate(270); break;
        case rotation_180: api_rotate(180); break;
    }*/

    change_cursor(last_cursor);

    show_rotate_menu = 0;
}

void cb_replace_greater() { temp_tolerance_mode = greater; }
void cb_replace_leaser() { temp_tolerance_mode = leaser; }
void cb_replace_greaterLeaser() { temp_tolerance_mode = greater_or_leaser; }
void cb_replace_plus() { temp_tolerance_replace_mode = tolerance_replace_plus; }
void cb_replace_minus() { temp_tolerance_replace_mode = tolerance_replace_minus; }
void cb_replace_equal() { temp_tolerance_replace_mode = tolerance_replace_equal; }
void cb_replace_Solid() { temp_tolerance_replace_mode_2 = replace_mode_solid; }
void cb_replace_Pattern() { temp_tolerance_replace_mode_2 = replace_mode_pattern; }
void cb_replace_cancel() { show_replace_menu = 0; }

void cb_globalReplace_greater() { temp_tolerance_mode = greater; }
void cb_globalReplace_leaser() { temp_tolerance_mode = leaser; }
void cb_globalReplace_greaterLeaser() { temp_tolerance_mode = greater_or_leaser; }
void cb_globalReplace_plus() { temp_tolerance_replace_mode = tolerance_replace_plus; }
void cb_globalReplace_minus() { temp_tolerance_replace_mode = tolerance_replace_minus; }
void cb_globalReplace_equal() { temp_tolerance_replace_mode = tolerance_replace_equal; }
void cb_globalReplace_Solid() { temp_tolerance_replace_mode_2 = replace_mode_solid; }
void cb_globalReplace_Pattern() { temp_tolerance_replace_mode_2 = replace_mode_pattern; }
void cb_globalReplace_cancel() { show_replace_menu = 0; }

void cb_object_placeOver() { object_mode = put_object; }
void cb_object_increase() { object_mode = add_object; }
void cb_object_decrease() { object_mode = sub_object; }
void cb_object_cancel() { show_object_menu = 0; }
void cb_object_ok() { show_object_menu = 0; }

void cb_error_ok() { view_error_menu = 0; }
