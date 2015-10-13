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
  //Terrain *terrains[3];
  //memset(&terrains, 0, sizeof(Terrain*) * 3);
  terrain = generateTerrain(WIDTH, HEIGHT);

  Uint32 (*on_screen_pointer) (unsigned int) = on_screen;
  SDL_Init (SDL_INIT_VIDEO || SDL_INIT_TIMER);

  //TODO Load settings
  //load_settings ();

  screen = SDL_SetVideoMode (window_width, window_height, 8, SDL_HWSURFACE | SDL_RESIZABLE | SDL_HWPALETTE);
  SDL_Surface *icon = SDL_LoadBMP("/Users/alejandro/programs/height-map-editor/res/icon.bmp");

  SDL_WM_SetIcon(icon, NULL);
  SDL_WM_SetCaption ("Terrain Editor", "Terrain Editor");

  if (screen == NULL)
  {
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

  defineCustomColours();

	make_gray_pallete();

  seed = time (NULL);
  srand (seed);

  //allocate_mem(&terrains, WIDTH, HEIGHT);
  //overdraw_terrain(WIDTH, HEIGHT);
  //overdrawTerrain(*terrains);
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
  /*free(*(terrains + TERRAIN_WORK));
  free(*(terrains + TERRAIN_UNDO));
  free(*(terrains + TERRAIN_TEMP));*/
  freeTerrain(terrain);

  if (terrain_height)free (terrain_height);
  if (temp_buffer)free (temp_buffer);
  if (handle_font_mem)free(handle_font_mem);
  if (handle_tool_bar_mem)free(handle_tool_bar_mem);
  if (cursors_mem)free(cursors_mem);
}

void defineCustomColours() {
  //now, define our custom colors
  //black
  colors[255].r = 0;
  colors[255].g = 0;
  colors[255].b = 0;

  //white
  colors[254].r = 255;
  colors[254].g = 255;
  colors[254].b = 255;

  //darkblue
  colors[253].r = 20;
  colors[253].g = 40;
  colors[253].b = 160;

  //light blue
  colors[252].r = 20;
  colors[252].g = 140;
  colors[252].b = 255;

  //green
  colors[251].r = 20;
  colors[251].g = 255;
  colors[251].b = 100;

  //red
  colors[250].r = 250;
  colors[250].g = 55;
  colors[250].b = 10;

  //gray
  colors[249].r = 150;
  colors[249].g = 150;
  colors[249].b = 150;

  //steel blue
  colors[248].r = 140;
  colors[248].g = 170;
  colors[248].b = 200;

  //light steel blue
  colors[247].r = 170;
  colors[247].g = 200;
  colors[247].b = 230;

  //very light steel blue
  colors[246].r = 190;
  colors[246].g = 220;
  colors[246].b = 250;

  //dark steel blue
  colors[245].r = 100;
  colors[245].g = 130;
  colors[245].b = 160;
}
