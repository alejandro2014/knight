#include "draw.h"

/*
> gterr width:5 height:5
[INFO] Created terrain 5x5
> sethterr height:5
> sethp x:1 y:1 height:3
> sethp x:2 y:1 height:3
> sethp x:3 y:1 height:3
> sethp x:1 y:2 height:3
> sethp x:2 y:2 height:1
[ERROR] One random error
> sethp x:3 y:2 height:3
> sethp x:1 y:3 height:3
> sethp x:2 y:3 height:3
> sethp x:3 y:3 height:3
> prterr
*/
void drawScreen(SDL_Renderer *renderer, Font *font, char *buffer, bool showCursor) {
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);

    buffer = "> gterr width:5 height:5\n[INFO] Created terrain 5x5\n> sethterr height:5\n> sethp x:1 y:1 height:3\n";
    drawConsole(renderer, font, buffer);

    if(showCursor) {
        drawCursor(renderer, 2, 2, &(font->fgColor));
    }

    SDL_RenderPresent(renderer);
}

void drawConsole(SDL_Renderer *renderer, Font *font, char *consoleBuffer) {
    int numChars = strlen(consoleBuffer);
    int i;
    char line[80];
    int currentLine = 0;
    int linePos;
    char currentChar;

    for(i = 0; i < numChars; i++) {
        currentChar = *(consoleBuffer + i);
        line[linePos] = currentChar;
        linePos++;

        if(currentChar == '\n') {
            line[linePos - 1] = '\0';
            printString(font, renderer, &line[0], 2, (currentLine++) * 20 + 30);
            linePos = 0;
        }
    }
}

void drawCursor(SDL_Renderer *renderer, int x, int y, SDL_Color *color) {
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = 10;
    r.h = 15;

    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);
    SDL_RenderFillRect(renderer, &r);
}

/*#include "font.h"
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

//TODO Use the rectangle function
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

void drawToolbarIcon(Button button, int mode) {
    int x, y;
    int my_pitch = this_screen->pitch;
    Uint8 *screen_buffer = (Uint8 *) this_screen->pixels + buttonY * my_pitch + buttonX;

    int buttonWidth = button.width; //16, 32
    int x1 = button.x;//icon_no * buttonWidth
    int y1 = button.y;//0, 16
    int x2 = x1 + buttonWidth;
    int y2 = y1 + buttonWidth;

    for(y = y1; y < y2; y++) {
        Uint8 cur_color;

        for (x = x1; x < x2; x++) {
            cur_color = *(tool_bar_mem + x_tool_bar_bmp * y + x);

            if (cur_color == 131 || cur_color == 130) {
                cur_color = (mode == mode_pushed) ? light_steel_blue : steel_blue;
            }

            *(++screen_buffer) = cur_color;
        }

        screen_buffer += my_pitch - buttonWidth;
    }
}

void drawIcons(Toolbar toolbar) {
    int numIcons = toolbar.numIcons;
    int i;

    for (i = 0; i < numIcons; i++) {
        int button = toolbar.buttons[i];
        int buttonX = toolbar.x + button.x;
        int buttonY = toolbar.y + button.y;
        int buttonSize = button.size;

        if (button.icon_active == 1 || button.icon_pressed == 1) {
            drawToolbarIcon(button, mode_pushed);
            draw_down_button(button);
        } else if (!button.icon_dont_stay_pressed || button.icon_mouse_over) {
            drawToolbarIcon(button, mode_not_pushed);
            draw_up_button(button);
        } else if (button.icon_dont_stay_pressed) {
            drawToolbarIcon(button, mode_not_pushed);
        }
    }
}

void drawHeightsBar(HeightsBar *heightsBar) {
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
}

void drawColorPointer() {
    //draw the current color pointer
    x = heightsBarX + color_1;
    y = heightsBarY + 6;

    setPixel(x, y, red);
    setPixel(x+1, y, red);
    setPixel(x, y+1, red);
    setPixel(x+1, y+1, red);
}*/

/*void draw_tool_bar(Toolbar *toolbar) {
  char str[20];
  int x, y, i;

  //check to see if we didn't drag the tool bar outside of the screen
  if (toolbar.x < 0)
    toolbar.x = 0;
  else if ((toolbar.x + toolbar.width + 1) > window_width)
    toolbar.x = window_width - toolbar.width - 1;

    if (toolbar.y < 0)
      toolbar.y = 0;
    else if ((toolbar.y + toolbar.height + 1) > window_height)
      toolbar.y = window_height - toolbar.height - 1;

  draw_empty_menu (screen, steel_blue, tool_bar_x, tool_bar_y, tool_bar_x_lenght, tool_bar_y_lenght);*/
  /*int button = main_tool_bar[i];
  int buttonX = tool_bar_x + (i * 36,20) + 2;
  int buttonY = tool_bar_y + 2,40;
  int buttonSize = 33,17; */
  /*drawIcons(main_tool_bar);
  drawIcons(small_tool_bar);
  drawHeightsBar(heightsBar);
  drawColorPointer();

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

int isPointInWindow(int x, int y) {
  //return (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT) ? 1 : 0;
  return 0;
}*/

//void setPixel(int x, int y, int colour) {
    /*currentScreen = NULL;
    *((Uint32 *)currentScreen->pixels + y * currentScreen->w + x) = colour;*/
//}

/*int getPixel(int x, int y) {
    return 0;
}

void function_object(int object_mode) {
    switch(object_mode) {
        case put_object:
            *(start_display_pointer+j)=cur_height/4;
            break;

        case add_object:
            cur_height+=*(terrain_height+k*WIDTH+l);
            if(cur_height>255)cur_height=255;
            *(start_display_pointer+j)=cur_height/4;
            break;

        case sub_object:
            cur_height=*(terrain_height+k*WIDTH+l)-cur_height;
            if(cur_height<0)*(start_display_pointer+j)=black;
            else *(start_display_pointer+j)=cur_height/4;
            break;
    }
}

void function_object_zoom(int object_mode, int *height) {
    int cur_height = *height;

    switch(object_mode) {
        case put_object:
            cur_height /= 4;
            break;

        case add_object:
            cur_height += getHeight(terrain_height, l, k);
            if(cur_height>255) cur_height = 255;
            cur_height/=4;
            break;

        case sub_object:
            cur_height = getHeight(terrain_height, l, k) - cur_height;
            if(cur_height<0) cur_height = 0;
            else cur_height/=4;
            break;
    }

    *height = cur_height;
}

void draw_object_on_screen(SDL_Surface * this_screen) {
    int my_pitch;
    int object_x_start,object_y_start;
    int object_x_end,object_y_end;
    int object_x_screen_start,object_y_screen_start;
    int object_x_screen_end,object_y_screen_end;
    int object_x_terrain_start,object_y_terrain_start;
    int object_x_terrain_end,object_y_terrain_end;

    int x,y,i,j,k,l;

    int cur_height;
    Uint8 * start_display_pointer;
    Uint8 * start_object_pointer;

    Uint8 *screen_buffer;
    screen_buffer = (Uint8 *) this_screen->pixels;
    my_pitch = this_screen->pitch;

    //first, check to see if we really have the object
    //if we don't have it, it means that the user tried to load an invalid file
    //or he pressed the cancel button.
    if(!current_object.object_mem) {
        int i;
    	current_object.object_mem=0;
    	//change the tool to the draw tool
    	current_tool=t_place;
    	for(i=0;i<no_of_main_tool_bar_icons;i++)
            main_tool_bar[i].icon_active = 0;

    	main_tool_bar[0].icon_active = 1;
    	change_cursor_show(cursor_put);
    	return;
    }

    //ok, first, get the object screen x/y, according to the zoom level (if any)
    object_x_screen_start = x_mouse_pos-(current_object.object_x_len/2*terrain_ratio);
    object_y_screen_start = y_mouse_pos-(current_object.object_y_len/2*terrain_ratio);
    object_x_screen_end = x_mouse_pos+(current_object.object_x_len/2*terrain_ratio);
    object_y_screen_end = y_mouse_pos+(current_object.object_y_len/2*terrain_ratio);

    //now, find out which part of the object we display (if it is outside of the screen)

    //start part
    object_x_start = (object_x_screen_start > 0) ? 0 : (object_x_screen_start*-1) / terrain_ratio;
    object_y_start = (object_y_screen_start > 0) ? 0 : (object_y_screen_start*-1) / terrain_ratio;

    //end part
    object_x_end = current_object.object_x_len - (object_x_screen_end < window_width ? 0 : ((object_x_screen_end-window_width) / terrain_ratio);
    object_y_end = current_object.object_y_len - (object_y_screen_end < window_height ? 0 : ((object_y_screen_end-window_height) / terrain_ratio);

    //do some final adjustments
    if(object_x_screen_start < 0) object_x_screen_start = 0;
    if(object_y_screen_start < 0) object_y_screen_start = 0;

    //now, do get the terrain coordinates.
    object_x_terrain_start=((x_mouse_pos-x_screen_offset)-(current_object.object_x_len/2*terrain_ratio))/ terrain_ratio + xoffset;
    object_y_terrain_start=((y_mouse_pos-y_screen_offset)-(current_object.object_y_len/2*terrain_ratio))/ terrain_ratio + yoffset;
    object_x_terrain_end=((x_mouse_pos-x_screen_offset)+(current_object.object_x_len/2*terrain_ratio))/ terrain_ratio + xoffset;
    object_y_terrain_end=((y_mouse_pos-y_screen_offset)+(current_object.object_y_len/2*terrain_ratio))/ terrain_ratio + yoffset;

    if(terrain_ratio==1) {
        i=0;
	    k=object_y_terrain_start+object_y_start;
	    for(y=object_y_start;y<object_y_end;y++) {
			start_object_pointer=current_object.object_mem+y*current_object.object_x_len;
			start_display_pointer=screen_buffer+(object_y_screen_start+i)*my_pitch;
			j=object_x_screen_start;
			l=object_x_terrain_start+object_x_start;

			for(x=object_x_start;x<object_x_end;x++) {
			    cur_height=*(start_object_pointer+x);
			    if(cur_height && l>=0 && l<WIDTH && k>=0 && k<HEIGHT) {
                    function_object(object_mode);
			    }

			    j++;
			    l++;
		    }

			i++;
			k++;
        }
    } else {//the terain is zoomed in, use other routines, for better optimization
        int screen_size=window_height*my_pitch;
	    int screen_offset_int_pointer;

        i=0;
        k=object_y_terrain_start+object_y_start;

        for(y=object_y_start;y<object_y_end;y++) {
            start_object_pointer=current_object.object_mem+y*current_object.object_x_len;
            start_display_pointer=screen_buffer+(object_y_screen_start+i*terrain_ratio)*my_pitch;
            screen_offset_int_pointer=(object_y_screen_start+i*terrain_ratio)*my_pitch;
            j=object_x_screen_start;
            l=object_x_terrain_start+object_x_start;

            for(x=object_x_start;x<object_x_end;x++) {
                cur_height=*(start_object_pointer+x);

                if(cur_height && l>=0 && l<WIDTH && k>=0 && k<HEIGHT) {
                    int m,n,another_displacement;

                    function_object_zoom(object_mode, &cur_height);

                    for(m=0;m<terrain_ratio;m++)
                        for(n=0;n<terrain_ratio;n++) {
                            another_displacement=m*my_pitch+n;
                            if(screen_offset_int_pointer+j+another_displacement < screen_size)
                                *(start_display_pointer+j+another_displacement) = cur_height;
                        }
                    }

                    j+=terrain_ratio;
                    l++;
              }
              i++;
              k++;
          }
    }
}*/
