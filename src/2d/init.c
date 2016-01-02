#include "init.h"

void build_tool_bar() {
  main_tool_bar[0] = buildToolBarButton(icon_place, change_tool_place, 1, 0, 0, do_nothing, "Place", 0);
  main_tool_bar[1] = buildToolBarButton(icon_escavate, change_tool_escavate, 0, 0, 0, do_nothing, "Escavate", 0);
  main_tool_bar[2] = buildToolBarButton(icon_elevate, change_tool_elevate, 0, 0, 0, do_nothing, "Elevate", 0);
  main_tool_bar[3] = buildToolBarButton(icon_peek, change_tool_peek, 0, 0, 0, do_nothing, "Pick height", 0);
  main_tool_bar[4] = buildToolBarButton(icon_selection, change_tool_select, 0, 0, 0, do_nothing, "Select", 0);
  main_tool_bar[5] = buildToolBarButton(icon_replace, change_tool_replace, 0, 0, 0, do_display_replace_menu, "Replace", 0);
  main_tool_bar[6] = buildToolBarButton(icon_global_replace, change_tool_global_replace, 0, 0, 0, do_display_global_replace_menu, "Global Replace", 0);
  main_tool_bar[7] = buildToolBarButton(icon_flood, change_tool_flood, 0, 0, 0, do_nothing, "Fill", 0);
  main_tool_bar[8] = buildToolBarButton(icon_increase_zoom, change_tool_zoom_in, 0, 0, 0, do_decrease_zoom, "Zoom in", 0);
  main_tool_bar[9] = buildToolBarButton(icon_object, change_tool_object, 0, 0, 0, do_display_object_menu, "Place object", 0);
  main_tool_bar[10] = buildToolBarButton(icon_smooth, do_smooth_terrain, 0, 0, 1, do_nothing, "Smooth terrain", 0);
  main_tool_bar[11] = buildToolBarButton(icon_rise, do_rise_terrain, 0, 0, 1, do_nothing, "Rise terrain", 0);
  main_tool_bar[12] = buildToolBarButton(icon_sink, do_sink_terrain, 0, 0, 1, do_nothing, "Sink terrain", 0);
  main_tool_bar[13] = buildToolBarButton(icon_rotate, do_display_rotate_menu, 0, 0, 1, do_nothing, "Rotate/Flip terrain", 0);
  main_tool_bar[14] = buildToolBarButton(icon_new, do_new_terrain, 0, 0, 1, do_nothing, "New terrain", 0);
  main_tool_bar[15] = buildToolBarButton(icon_generate, do_generate, 0, 0, 1, do_nothing, "Generate terrain", 0);
  main_tool_bar[16] = buildToolBarButton(icon_open, do_load, 0, 0, 1, do_nothing, "Load terrain", 0);
  main_tool_bar[17] = buildToolBarButton(icon_save, do_save, 0, 0, 1, do_nothing, "Save terrain", 0);

  small_tool_bar[0] = buildToolBarButton(icon_brush_1, change_brush_1, 1, 0, 0, "Brush size 1x1", 0);
  small_tool_bar[1] = buildToolBarButton(icon_brush_2, change_brush_2, 0, 0, 0, "Brush size 3x3", 0);
  small_tool_bar[2] = buildToolBarButton(icon_brush_3, change_brush_3, 0, 0, 0, "Brush size 5x5", 0);
  small_tool_bar[3] = buildToolBarButton(icon_brush_4, change_brush_4, 0, 0, 0, "Brush size 7x7", 0);
  small_tool_bar[4] = buildToolBarButton(icon_brush_5, change_brush_5, 0, 0, 0, "Brush size 9x9", 0);
  small_tool_bar[5] = buildToolBarButton(icon_left_arrow, do_decrease_tools_height, 0, 0, 1, "Prev. height", 0);
  small_tool_bar[6] = buildToolBarButton(icon_right_arrow, do_increase_tools_height, 0, 0, 1, "Next height", 0);
}

void build_numeric_dialog_boxes () {
    numeric_dialog_boxes[x_map_size_dialog] = buildNumericTextbox(9999, 64, 256, 0, 4, 1, 0);
    numeric_dialog_boxes[y_map_size_dialog] = buildNumericTextbox(9999, 64, 256, 0, 4, 0, 0);
    numeric_dialog_boxes[base_height_dialog] = buildNumericTextbox(255, 0, 0, 0, 3, 0, 0);
    numeric_dialog_boxes[seed_dialog] = buildNumericTextbox(0xffffffff, 0, 0, 0, 10, 1, 0);
    numeric_dialog_boxes[tolerance] = buildNumericTextbox(255, 0, 0, 0, 3, 1, 0);
    numeric_dialog_boxes[global_tolerance] = buildNumericTextbox(255, 0, 0, 0, 3, 1, 0);
}

void buildToolBarButton(int iconId, int windowMessage, int iconActive, int iconPush,
                        int iconNotPush, int righClickMessage, char *tooltip, int mouseOverTimer) {
    Button *button;
    button->icon_id = iconId;
    button->associated_window_message = windowMessage;
    button->icon_active = 1;
    button->icon_pressed = 0;
    button->icon_dont_stay_pressed = 0;
    button->right_click_message = do_nothing;
    sprintf(button->tool_tip, "Place");
    button->mouse_over_timer=0;
}

TextBox *buildNumericTextbox(int max, int min, int current, int offset, int length, int hasFocus, int isPressed) {
    TextBox *textbox = (Textbox *) malloc(sizeof(TextBox));
    memset(textbox, 0, sizeof(Textbox));

    textbox.max_number = max;
    textbox.min_number = min;
    textbox.current_number = current;
    textbox.text_offset = offset;
    textbox.dialog_lenght = length;
    textbox.has_focus = hasFocus;
    textbox.is_pressed = isPressed;

    return textbox;
}

void build_cursors() {
    assignCursor(cursor_put, 0, 15);
    assignCursor(cursor_dig, 0, 15);
    assignCursor(cursor_elevate, 3, 15);
    assignCursor(cursor_peek, 0, 15);
    assignCursor(cursor_replace, 0, 15);
    assignCursor(cursor_global_replace, 0, 15);
    assignCursor(cursor_flood, 0, 14);
    assignCursor(cursor_wait, 0, 0);
    assignCursor(cursor_arrow, 3, 0);
    assignCursor(cursor_target, 8, 8);
    assignCursor(cursor_zoom, 4, 11);
    assignCursor(cursor_select, 8, 8);
}

void assignCursor(int cursor, int hotX, int hotY) {
    cursors_array[cursor].hot_x=8;
	cursors_array[cursor].hot_y=8;
	assign_cursor(cursor);
}