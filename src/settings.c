#include <stdio.h>
#include <string.h>
#include "settings.h"

//load the settings, at startup
void load_settings() {
  FILE *f = NULL;

  getcwd(200,conf_file_path);

  strcat(conf_file_path,"./settings.cfg");

  f = fopen (conf_file_path, "rb");
  if (!f)
    return;			//file not found
  fread (settings, 1, sizeof (settings), f);
  fclose (f);
//ok, now set the variables
  window_width = settings[0].window_x;
  window_height = settings[0].window_y;

  min_map_x = settings[0].minmap_x;
  min_map_y = settings[0].minmap_y;
  mini_map = settings[0].minmap_active;

  tool_bar_x = settings[0].toolbar_x;
  tool_bar_y = settings[0].toolbar_y;
  tool_bar = settings[0].toolbar_active;

  status_bar_x = settings[0].statusbar_x;
  status_bar_y = settings[0].statusbar_y;
  status_bar = settings[0].statusbar_active;

  grid = settings[0].grid_size;
  color_1 = settings[0].last_height_used;
  tolerance_value = settings[0].replace_tolerance;
  tolerance_mode = settings[0].tolerance_mode;
  overwrite_terrain = settings[0].overwrite_terrain;
}

void save_settings() {
  FILE *f = NULL;

  settings[0].window_x = window_width;
  settings[0].window_y = window_height;

  settings[0].minmap_x = min_map_x;
  settings[0].minmap_y = min_map_y;
  settings[0].minmap_active = mini_map;

  settings[0].toolbar_x = tool_bar_x;
  settings[0].toolbar_y = tool_bar_y;
  settings[0].toolbar_active = tool_bar;

  settings[0].statusbar_x = status_bar_x;
  settings[0].statusbar_y = status_bar_y;
  settings[0].statusbar_active = status_bar;

  settings[0].grid_size = grid;
  settings[0].last_height_used = color_1;
  settings[0].replace_tolerance = tolerance_value;
  settings[0].tolerance_mode = tolerance_mode;
  settings[0].overwrite_terrain = overwrite_terrain;

  f = fopen (conf_file_path, "wb");
  fwrite (settings, sizeof (settings), 1, f);
  fclose (f);
}
