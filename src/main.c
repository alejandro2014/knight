/*#include <SDL2/SDL.h>
#include <SDL2/SDL_endian.h>
#include <stdlib.h>
#include <time.h>

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

#include <SDL_ttf.h>

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
#include "widgets.h"
#include "main.h"
#include "helper.h"
#include "api.h"
#include "hme_lowlevel.h"
#include "console.h"

#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char *string = "gterr -w 20 -h 30";
    char *stringCommand = (char *) malloc(sizeof(char) * 100);
    memset(stringCommand, 0, 100);
    memcpy(stringCommand, string, strlen(string));

    //char stringCommand[100] = "gterr -w 20 -h 30\0";
    Command *command = parseCommand(stringCommand);
    return 0;

    HeightMapEditor heightMapEditor;
    heightMapEditor.horSize = 3;
    heightMapEditor.verSize = 2;
    //SDL_Init(SDL_INIT_VIDEO);

    Terrain *terrain;

    if(loadResources(&heightMapEditor) != -1) {
        //programLoop();
        terrain = heightMapEditor.terrain;
        setHeight(terrain, 0, 0, 10);
        setHeight(terrain, 1, 0, 11);
        setHeight(terrain, 2, 0, 12);
        setHeight(terrain, 0, 1, 13);
        setHeight(terrain, 1, 1, 14);
        setHeight(terrain, 2, 1, 15);
        /*setHeight(terrain, 0, 2, 6);
        setHeight(terrain, 1, 2, 7);
        setHeight(terrain, 2, 2, 8);*/
        showTerrainCmd(terrain);

        api_sinkTerrain(terrain, 4);
        showTerrainCmd(heightMapEditor.terrain);

        freeResources(&heightMapEditor);
    }

    //SDL_Quit();
    return 0;
}

void programLoop() {
    /*bool finish = false;
    SDL_Event event;

    while(!finish) {
        readEvents(&finish);
        //drawScreen();
        //SDL_Delay(1000);
    }*/
}

int loadResources(HeightMapEditor *heightMapEditor) {
    int width = 100;
    int height = 100;

    heightMapEditor->dialogs = loadDialogs();
    //printDialogs(heightMapEditor->dialogs);

    heightMapEditor->terrain = api_generateTerrain(heightMapEditor->horSize, heightMapEditor->verSize);

    /**window = SDL_CreateWindow("HME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);

    if (*window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return -1;
    }*/

    /**renderer = SDL_CreateRenderer(*window, -1, 0);

    if(*renderer == NULL) {
        printf("Could not create renderer: %s\n", SDL_GetError());
        return -1;
    }*/

    /*TTF_Init();
    *font = TTF_OpenFont(FONT_PATH_LINUX, 12);

    if(*font == NULL) {
        printf("Could not load the font\n");
        return -1;
    }*/

    return 0;
}

void freeResources(HeightMapEditor *heightMapEditor) {
    /*SDL_DestroyRenderer(heightMapEditor->renderer);
    SDL_DestroyWindow(heightMapEditor->window);
    TTF_CloseFont(heightMapEditor->font);*/
    freeDialogs(heightMapEditor->dialogs);
    api_freeTerrain(heightMapEditor->terrain);

    /*if (terrain_height)free (terrain_height);
    if (temp_buffer)free (temp_buffer);
    if (handle_font_mem)free(handle_font_mem);
    if (handle_tool_bar_mem)free(handle_tool_bar_mem);
    if (cursors_mem)free(cursors_mem);*/
}

/*int main2(int argc, char *argv[]) {
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

  seed = time (NULL);
  srand (seed);

  //generateRandomTerrain(terrain);

  events_loop ();

  //TODO Save settings
  //save_settings ();		//save the settings, at exit

  SDL_Quit ();

  return 1;
}*/
