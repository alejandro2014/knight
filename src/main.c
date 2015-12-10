
/*#include <SDL2/SDL.h>
#include <SDL2/SDL_endian.h>
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

void readEvents(int *finish);

TTF_Font *font;
SDL_Window *window;
SDL_Renderer *renderer;

char *FONT_PATH_MAC = "/Library/Fonts/Arial.ttf";
char *FONT_PATH_LINUX = "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf";*/

#include "global.h"
#include "menus.h"
#include "load_widgets.h"
#include "main.h"

void printDialogs(Dialog **dialogs);

int main(int argc, char* argv[]) {
    //SDL_Init(SDL_INIT_VIDEO);
    Dialog **dialogs = loadDialogs();

    printDialogs(dialogs);
    //if(initResources(&window, &renderer, &font) != -1) {
        programLoop();
        //freeResources(window, renderer, font);
    //}

    freeDialogs(dialogs);
    //SDL_Quit();
    return 0;
}

void programLoop() {
    /*int finish = 0;
    SDL_Event event;

    while(!finish) {
        readEvents(&finish);
        drawScreen();
        SDL_Delay(1000);
    }*/
}

/*void readEvents(int *finish) {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            *finish = 1;
        }
    }
}*/

/*int initResources(SDL_Window **window, SDL_Renderer **renderer, TTF_Font **font) {
    *window = SDL_CreateWindow("HME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);

    if (*window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return -1;
    }

    *renderer = SDL_CreateRenderer(*window, -1, 0);

    if(*renderer == NULL) {
        printf("Could not create renderer: %s\n", SDL_GetError());
        return -1;
    }

    TTF_Init();
    *font = TTF_OpenFont(FONT_PATH_LINUX, 12);

    if(*font == NULL) {
        printf("Could not load the font\n");
        return -1;
    }

    return 0;
}

void freeResources(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
}*/

/*int main2(int argc, char *argv[]) {
  WIDTH = 700;
  HEIGHT = 480;
  //WIDTH = 513;
  //HEIGHT = 513;
  window_width = WIDTH;
  window_height = HEIGHT;
  //terrain = generateTerrain(700, 480);
  //terrain = generateTerrain(WIDTH, HEIGHT);

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
  SDL_Surface *icon = SDL_LoadBMP("/Users/alejandro/programs/height-map-editor/res/icon.bmp");

  SDL_WM_SetIcon(icon, NULL);
  SDL_WM_SetCaption ("Terrain Editor", "Terrain Editor");

  if (screen == NULL) {
    fprintf (stderr, "Could not initialize video\n");
    exit (1);
  }

  //load_font();
  //load_tool_bar();
  build_tool_bar();

  load_cursors();
  build_numeric_dialog_boxes();

  build_cursors();
  change_cursor(cursor_put);

  SDL_EnableKeyRepeat (200, 100);

	//make_gray_pallete();

  seed = time (NULL);
  srand (seed);

  //generateRandomTerrain(terrain);

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
}*/
