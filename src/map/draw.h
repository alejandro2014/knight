#ifndef DRAW_H
#define DRAW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../global.h"

#include "../console/console.h"

#include "font.h"

typedef struct {
    int x, y;
    int width, height;
    int interLineSpace;
    int padding;
    int pixelsFill;
    int widthCursor;
    int heightCursor;
} ConsoleVisualParams;

void drawScreen(SDL_Renderer *renderer, Font *font, Console *console, ConsoleVisualParams *consoleParams, bool showCursor);
void drawCursor(Console *console, SDL_Renderer *renderer, SDL_Color *color, ConsoleVisualParams *consoleParams);
void drawConsole(SDL_Renderer *renderer, Font *font, Console *console, ConsoleVisualParams *consoleParams);

int calculateCursorPosition(Console *console);

/*void draw_frame (SDL_Surface * this_screen, int xmenu, int ymenu, int xlen, int ylen);
void draw_down_button (SDL_Surface * this_screen, int xmenu, int ymenu, int xlen, int ylen);
void draw_up_button (SDL_Surface * this_screen, int xmenu, int ymenu, int xlen, int ylen);
void draw_empty_menu (SDL_Surface * this_screen, char color, int xmenu, int ymenu, int xlen, int ylen);

#define mode_pushed 0
#define mode_not_pushed 1
#define mode_let_alone 2
void draw_tool_bar_big_icon (SDL_Surface * this_screen, int mode, int icon_no, int icon_x_screen, int icon_y_screen);
void draw_tool_bar_small_icon (SDL_Surface * this_screen, int mode, int icon_no, int icon_x_screen, int icon_y_screen);

void draw_tool_bar (SDL_Surface * this_screen);
void draw_status_bar ();

void draw_minimap (SDL_Surface * this_screen);
void draw_tool_tip();

int isPointInWindow(int x, int y);
void setPixel(int x, int y, int colour);
int getPixel(int x, int y);*/

#endif
