#include <SDL2/SDL.h>
#include <SDL2/SDL_endian.h>	/* Used for the endian-dependent 24 bpp mode */
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
#include "load_widgets.h"

#include <SDL_ttf.h>

void freeMemory(Terrain *terrain);
void defineCustomColours();
void load_cursors();
void build_cursors();

extern TTF_Font *font;
SDL_Window *window;
SDL_Renderer *renderer;

char *FONT_PATH_MAC = "/Library/Fonts/Arial.ttf";
char *FONT_PATH_LINUX = "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf";

int main(int argc, char* argv[]) {

    SDL_Window *window;                    // Declare a pointer

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

renderer = SDL_CreateRenderer(window, -1, 0);
    // The window is open: could enter program loop here (see SDL_PollEvent())
    cls();

    SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}

int main2(int argc, char *argv[]) {
  WIDTH = 700;
  HEIGHT = 480;
  //WIDTH = 513;
  //HEIGHT = 513;
  window_width = WIDTH;
  window_height = HEIGHT;
  //terrain = generateTerrain(700, 480);
  //terrain = generateTerrain(WIDTH, HEIGHT);

  Uint32 (*on_screen_pointer) (Uint32, void *) = on_screen;
  SDL_Init (SDL_INIT_VIDEO | SDL_INIT_TIMER);
  //TTF_Init();
  //font = TTF_OpenFont(FONT_PATH_LINUX, 12);

  //TODO Load settings
  //load_settings ();

  //screen = SDL_SetVideoMode (window_width, window_height, 8, SDL_HWSURFACE | SDL_RESIZABLE | SDL_HWPALETTE);
  //screen = SDL_SetVideoMode (window_width, window_height, 8, SDL_HWSURFACE | SDL_HWPALETTE);
  
  window = SDL_CreateWindow("HME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_RESIZABLE);
  renderer = SDL_CreateRenderer(window, -1, 0); 
  //screen = screen = SDL_GetWindowSurface(window);
  
  //screen = SDL_SetVideoMode (window_width, window_height, 32, SDL_HWSURFACE);
  //printf("Allocated screen (%d x %d) pitch %d\n", window_width, window_height, screen->pitch);
  /*SDL_Surface *icon = SDL_LoadBMP("/Users/alejandro/programs/height-map-editor/res/icon.bmp");

  SDL_WM_SetIcon(icon, NULL);
  SDL_WM_SetCaption ("Terrain Editor", "Terrain Editor");

  if (screen == NULL) {
    fprintf (stderr, "Could not initialize video\n");
    exit (1);
  }*/

  //load_font();
  //load_tool_bar();
  /*build_tool_bar();

  load_cursors();
  build_numeric_dialog_boxes();

  build_cursors();
  change_cursor(cursor_put);

  SDL_EnableKeyRepeat (200, 100);

	//make_gray_pallete();

  seed = time (NULL);
  srand (seed);*/

  //generateRandomTerrain(terrain);

  SDL_AddTimer(100, on_screen_pointer, NULL);

  events_loop ();

  //TODO Save settings
  //save_settings ();		//save the settings, at exit

  SDL_Quit ();

  freeMemory(terrain);

  return 1;
}

void freeMemory(Terrain *terrain) {
  TTF_CloseFont(font);
  freeTerrain(terrain);

  if (terrain_height)free (terrain_height);
  if (temp_buffer)free (temp_buffer);
  if (handle_font_mem)free(handle_font_mem);
  if (handle_tool_bar_mem)free(handle_tool_bar_mem);
  if (cursors_mem)free(cursors_mem);
}
