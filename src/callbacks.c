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
