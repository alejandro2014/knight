#include <SDL/SDL.h>
#include <SDL/SDL_endian.h>	/* Used for the endian-dependent 24 bpp mode */
#include <stdlib.h>
#include <time.h>

#include "global.h"

#include "init.h"
#include "cursors.h"
#include "load_save.h"
#include "global_tools.h"
#include "tools.h"
#include "actions.h"

#include "draw_stuff.h"
#include "menus.h"
#include "font.h"
#include "generate_terrain.h"
#include "display_terrain.h"
#include "events.h"
#include "settings.h"
#include "objects.h"

#include "actions_core.h"

void freeMemory(Terrain *terrain);
void defineCustomColours();
void load_cursors();
void build_cursors();

int main (int argc, char *argv[]) {
  terrain = generateTerrain(700, 480);
  //terrain = generateTerrain(33, 33);

  Uint32 (*on_screen_pointer) (unsigned int) = on_screen;
  SDL_Init (SDL_INIT_VIDEO || SDL_INIT_TIMER);

  //TODO Load settings
  //load_settings ();

  screen = SDL_SetVideoMode (window_width, window_height, 8, SDL_HWSURFACE | SDL_RESIZABLE | SDL_HWPALETTE);
  SDL_Surface *icon = SDL_LoadBMP("/Users/alejandro/programs/height-map-editor/res/icon.bmp");

  SDL_WM_SetIcon(icon, NULL);
  SDL_WM_SetCaption ("Terrain Editor", "Terrain Editor");

  if (screen == NULL) {
    fprintf (stderr, "Could not initialize video\n");
    exit (1);
  }

  load_font();
  load_tool_bar();
  build_tool_bar();

  load_cursors();
  build_numeric_dialog_boxes();

  build_cursors();
  change_cursor(cursor_put);

  SDL_EnableKeyRepeat (200, 100);

	make_gray_pallete();

  seed = time (NULL);
  srand (seed);

  generateRandomTerrain(terrain);

  SDL_SetTimer (100, on_screen_pointer);

  events_loop ();

  //TODO Save settings
  //save_settings ();		//save the settings, at exit

  SDL_Quit ();

  freeMemory(terrain);

  return 1;
}

void freeMemory(Terrain *terrain) {
  freeTerrain(terrain);

  if (terrain_height)free (terrain_height);
  if (temp_buffer)free (temp_buffer);
  if (handle_font_mem)free(handle_font_mem);
  if (handle_tool_bar_mem)free(handle_tool_bar_mem);
  if (cursors_mem)free(cursors_mem);
}
