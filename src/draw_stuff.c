#include "draw_stuff.h"

#include "font.h"
#include "tools.h"

void draw_frame(int xmenu, int ymenu, int xlen, int ylen) {
  int x, y;

  for (x = xmenu; x < xmenu + xlen; x++) setPixel(x, y, gray);
  for (y = ymenu; y < ymenu + ylen; y++) setPixel(xmenu, y, gray);
  for (x = xmenu; x < xmenu + xlen; x++) setPixel(x, ymenu + ylen, black);
  for (y = ymenu; y < ymenu + ylen; y++) setPixel(xmenu + xlen, y, black);
}

void draw_down_button (int xmenu, int ymenu, int xlen, int ylen) {
  drawPushableButton(xmenu, ymenu, xlen, ylen, true);
}

void draw_up_button (int xmenu, int ymenu, int xlen, int ylen) {
    drawPushableButton(xmenu, ymenu, xlen, ylen, false);
}

void drawPushableButton(int xmenu, int ymenu, int xlen, int ylen, bool isPushed) {
    int x1 = xmenu;
    int x2 = xmenu + xlen;
    int y1 = ymenu;
    int y2 = ymenu + ylen;

    int color1 = isPushed ? dark_steel_blue : light_steel_blue;
    int color2 = isPushed ? light_steel_blue : dark_steel_blue;

    drawLineHor(x1,     x2,   y1, color1);
    drawLineHor(x1,     x2, y1+1, color1);
    drawLineHor(x1,     x2,   y2, color2);
    drawLineHor(x1+1, x2+1, y2+1, color2);

    drawLineVer(y1,     y2,   x1, color1);
    drawLineVer(y1+1, y2+1, x1+1, color1);
    drawLineVer(y1,     y2,   x2, color2);
    drawLineVer(y1+1, y2+1, x2+1, color2);
}

void drawLineHor(int xIni, int xFin, int y, int color) {
    int x;
    for (x = xIni; x < xFin; x++) setPixel(x, y, color);
}

void drawLineVer(int yIni, int yFin, int x, int color) {
    int y;
    for (y = yIni; y < yFin; y++) setPixel(x, y, color);
}


void draw_empty_menu (SDL_Surface * this_screen, char color, int xmenu, int ymenu, int xlen, int ylen) {
  int x, y;
  char cur_pixel;
  Uint32 *screen_buffer = (Uint32 *) this_screen->pixels;
  int my_pitch = this_screen->pitch;
  screen_buffer += ymenu * my_pitch + xmenu;

  //draw the main menu (without borders)
  for (y = ymenu; y < ymenu + ylen; y++) {
    for (x = xmenu; x < xmenu + xlen; x++) {
      *(screen_buffer++) = color;
      *(screen_buffer++) = 0xff000000;
    }

    screen_buffer += (my_pitch - xlen);
  }

  draw_frame (screen, xmenu, ymenu, xlen, ylen);
}


void draw_tool_bar_big_icon (SDL_Surface * this_screen, int mode, int icon_no, int icon_x_screen, int icon_y_screen) {
  int x, y, my_pitch;
  char cur_pixel;
  Uint32 *screen_buffer = (Uint32 *) this_screen->pixels;
  my_pitch = this_screen->pitch;
  screen_buffer += icon_y_screen * my_pitch + icon_x_screen;

  for (y = y_tool_bar_bmp - 1; y != 15; y--) {
    Uint32 cur_color;
    for (x = icon_no * 32; x < icon_no * 32 + 32; x++) {
      cur_color = *(tool_bar_mem + x_tool_bar_bmp * y + x);

      if (cur_color == 131 || cur_color == 130) {
				if (mode == mode_pushed)
	  			cur_color = light_steel_blue;
				else if (mode == mode_not_pushed)
	  			cur_color = steel_blue;
			}

      *(++screen_buffer) = cur_color;
    }
    screen_buffer += my_pitch - 32;
  }
}

void draw_tool_bar_small_icon (SDL_Surface * this_screen, int mode, int icon_no, int icon_x_screen, int icon_y_screen) {
  int x, y, my_pitch;
  char cur_pixel;
  Uint8 *screen_buffer;
  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;
  screen_buffer += icon_y_screen * my_pitch + icon_x_screen;


  for (y = 15; y != -1; y--)
  {
    Uint8 cur_color;
    for (x = icon_no * 16; x < icon_no * 16 + 16; x++)
    {
      cur_color = *(tool_bar_mem + x_tool_bar_bmp * y + x);
      if (cur_color == 131 || cur_color == 130) {
	      if (mode == mode_pushed)
	        cur_color = light_steel_blue;
	      else if (mode == mode_not_pushed)
	        cur_color = steel_blue;
			}

      *(++screen_buffer) = cur_color;
    }
    screen_buffer += my_pitch - 16;
  }
}

void draw_tool_bar (SDL_Surface * this_screen) {
  int i, my_pitch;
  char str[20];
  int x, y;
  Uint8 *screen_buffer;
  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;

  //check to see if we didn't drag the tool bar outside of the screen
  if (tool_bar_x < 0)
    tool_bar_x = 0;
  else if ((tool_bar_x + tool_bar_x_lenght + 1) > window_width)
    tool_bar_x = window_width - tool_bar_x_lenght - 1;

  if (tool_bar_y < 0)
    tool_bar_y = 0;
  else if ((tool_bar_y + tool_bar_y_lenght + 1) > window_height)
    tool_bar_y = window_height - tool_bar_y_lenght - 1;


  draw_empty_menu (screen, steel_blue, tool_bar_x, tool_bar_y, tool_bar_x_lenght, tool_bar_y_lenght);
  //now, draw the icons
    for (i = 0; i < no_of_main_tool_bar_icons; i++) {
        int buttonX = tool_bar_x + (i * 36) + 2;
        int buttonY = tool_bar_y + 2;
        int buttonWidth = 33;
        int buttonHeight = 33;

        if (main_tool_bar[i].icon_active == 1 || main_tool_bar[i].icon_pressed == 1) {
            draw_tool_bar_big_icon (screen, mode_pushed, main_tool_bar[i].icon_id, buttonX + 1, buttonY + 1);
            draw_down_button (screen, buttonX, buttonY, buttonWidth, buttonHeight);
        } else if (!main_tool_bar[i].icon_dont_stay_pressed || main_tool_bar[i].icon_mouse_over) {
            draw_tool_bar_big_icon (screen, mode_not_pushed, main_tool_bar[i].icon_id, buttonX + 1, buttonY + 1);
            draw_up_button (screen, buttonX, buttonY, buttonWidth, buttonHeight);
        } else if (main_tool_bar[i].icon_dont_stay_pressed) {
            draw_tool_bar_big_icon (screen, mode_not_pushed, main_tool_bar[i].icon_id, buttonX + 1, buttonY + 1);
        }
    }

    //now, draw the small icons
    for (i = 0; i < no_of_small_tool_bar_icons; i++) {
        int buttonX = tool_bar_x + (i * 20) + 2;
        int buttonY = tool_bar_y + 40;
        int buttonWidth = 17;
        int buttonHeight = 17;

        if (small_tool_bar[i].icon_active == 1 || small_tool_bar[i].icon_pressed == 1) {
            draw_tool_bar_small_icon(screen, mode_pushed, small_tool_bar[i].icon_id, buttonX + 1, buttonY + 1);
            draw_down_button (screen, buttonX, buttonY, buttonWidth, buttonHeight);
        } else if (!small_tool_bar[i].icon_dont_stay_pressed || small_tool_bar[i].icon_mouse_over) {
            draw_tool_bar_small_icon(screen, mode_not_pushed, small_tool_bar[i].icon_id, buttonX + 1, buttonY + 1);
            draw_up_button(screen, buttonX, buttonY, buttonWidth, buttonHeight);
        } else if (small_tool_bar[i].icon_dont_stay_pressed) {
            draw_tool_bar_small_icon (screen, mode_not_pushed, small_tool_bar[i].icon_id, buttonX + 1, buttonY + 1);
        }
    }

    // draw the heights bar
    int heightsBarX = tool_bar_x + no_of_small_tool_bar_icons * 20 + 4;
    int heightsBarY = tool_bar_y + 42;
    int heightsBarWidth = 256;
    int heightsBarHeight = 14;

    i = 0;
    for (x = heightsBarX; x < heightsBarX + heightsBarWidth; x++) {
        for (y = heightsBarY; y < heightsBarY + heightsBarHeight; y++) {
            setPixel(x, y, i / 4);
        }
        i++;
    }

    //draw the current color pointer
    x = heightsBarX + color_1;
    y = heightsBarY + 6;

    setPixel(x, y, red);
    setPixel(x+1, y, red);
    setPixel(x, y+1, red);
    setPixel(x+1, y+1, red);

    draw_frame (screen, heightsBarX, heightsBarY, heightsBarWidth, heightsBarHeight);

    //now, print the current color
    draw_empty_menu (screen, white, heightsBarX + heightsBarWidth + 4, heightsBarY, 25, heightsBarHeight);

    sprintf (str, "%d", color_1);
    print_string (str, black, white, heightsBarX + heightsBarWidth + 6, heightsBarY + 2);
}

void draw_status_bar () {
  char str[80];
  int cur_z;

  //check to see if we didn't drag the status bar outside of the screen
  if (status_bar_x < 0)
    status_bar_x = 0;
  else if ((status_bar_x + status_bar_x_lenght + 1) > window_width)
    status_bar_x = window_width - status_bar_x_lenght - 1;

  if (status_bar_y < 0)
    status_bar_y = 0;
  else if ((status_bar_y + status_bar_y_lenght + 1) > window_height)
    status_bar_y = window_height - status_bar_y_lenght - 1;

  if (!get_cur_x_y ()) return;
  cur_z = *(terrain_height + cur_y * WIDTH + cur_x);	//get the deepth
  draw_empty_menu (screen, white, status_bar_x, status_bar_y, status_bar_x_lenght, status_bar_y_lenght);
  sprintf (str, "XSize: %d, YSize: %d, Map scale: %d/1, X: %d, Y: %d Z: %d", WIDTH, HEIGHT, terrain_ratio, cur_x, cur_y, cur_z);
  print_string (str, black, white, status_bar_x + 2, status_bar_y + 3);
}

void draw_tool_tip() {
  tip_x_lenght=7*strlen(tip_text)+6;
  //check to see if we didn't drag the tip outside of the screen
  if (tip_x < 0)tip_x = 0;
  else if ((tip_x + tip_x_lenght+1) > window_width)tip_x =window_width - tip_x_lenght - 1;
  if (tip_y < 0)tip_y = 0;
  else if ((tip_y + tip_y_lenght + 1) > window_height)tip_y =window_height - tip_y_lenght - 1;
  draw_empty_menu (screen, white, tip_x, tip_y,tip_x_lenght, tip_y_lenght);
  print_string (tip_text, black, white, tip_x + 2, tip_y + 3);
}

void draw_minimap (SDL_Surface * this_screen) {
  int my_pitch;
  float x, y, x_ratio, y_ratio;
  Uint8 cur_pixel;
  Uint8 *screen_buffer;
  Uint8 *height_map = terrain_height;
  int min_map_pos_x, min_map_pos_y, min_map_x_pos_lenght,
    min_map_y_pos_lenght;

  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;
  if(!terrain_height)return;//no terrain

  //check to see if we didn't drag the minimap outside of the screen
  if (min_map_x < 0)
    min_map_x = 0;
  else if ((min_map_x + 256) > window_width)
    min_map_x = window_width - 256;

  if (min_map_y < 0)
    min_map_y = 0;
  else if ((min_map_y + 256) > window_height)
    min_map_y = window_height - 256;

  screen_buffer += min_map_y * my_pitch + min_map_x;
  x_ratio = (float) WIDTH / (float) 256;
  y_ratio = (float) HEIGHT / (float) 256;

  for (y = 0; y < 256; y++) {
    for (x = 0; x < 256; x++) {
      cur_pixel = *(height_map + (int) (WIDTH * (int) (y * y_ratio) + (x * x_ratio)));
      if (cur_pixel)
	     cur_pixel = cur_pixel / 4;
      else
	     cur_pixel = 255;	//black
      *(screen_buffer++) = cur_pixel;
    }
    screen_buffer += my_pitch - 256;
  }

  //now, let's draw the rectangle that shows us where exactly we are
  min_map_pos_x = (int) (xoffset / x_ratio + min_map_x);
  min_map_pos_y = (int) (yoffset / y_ratio + min_map_y);
  min_map_x_pos_lenght = (int) (window_width / (x_ratio * terrain_ratio) - 1);
  min_map_y_pos_lenght = (int) (window_height / (y_ratio * terrain_ratio) - 1);

  //take care not to exceede the minmap limits, for smaller maps
  if (min_map_x_pos_lenght > 255) min_map_x_pos_lenght = 255;
  if (min_map_y_pos_lenght > 255) min_map_y_pos_lenght = 255;
  draw_frame (screen, min_map_pos_x, min_map_pos_y, min_map_x_pos_lenght, min_map_y_pos_lenght);

  //now, draw the minimap frame
  draw_frame (screen, min_map_x, min_map_y, 255, 255);
}
