#include <math.h>
#include "tools.h"

void draw_brush (int cur_x, int cur_y);

/*
This function gets the x and y of the height that is pointed by the mouse.
It returns 0, in case the mouse points to no pixel, otherwise return 1
*/
int get_cur_x_y () {
  if(!terrain_height)return 0;//we don't have a terrain
  cur_x = (x_mouse_pos - x_screen_offset) / terrain_ratio + xoffset;
  cur_y = (y_mouse_pos - y_screen_offset) / terrain_ratio + yoffset;

  if (cur_x >= 0 && cur_x < WIDTH && cur_y >= 0 && cur_y < HEIGHT)
    return 1;

  last_drawn_x = -1;
  last_drawn_y = -1;
  return 0;
}

void zoom_in () {
  int some_x_lenght, some_y_lenght;

  if (terrain_ratio > 15)
    return;

  if (!get_cur_x_y ())
    return;

  some_x_lenght = (window_width / (terrain_ratio + 1)) / 2;
  some_y_lenght = (window_height / (terrain_ratio + 1)) / 2;
  xoffset = (cur_x - some_x_lenght);
  yoffset = (cur_y - some_y_lenght);
  terrain_ratio++;
}

//the 'eye drop' tool, get the current pixel, under the mouse.
void pick_height (bool button_l, bool button_r) {
  if (!get_cur_x_y ())
    return;
  color_1 = *(terrain_height + cur_y * WIDTH + cur_x);	//get the deepth
}


void select_area() {
	if (!get_cur_x_y ())return;
	if(long_pressed_button_l==1 && selection_x_1!=-1)//we already have a selection, kill it
	{
		selection_x_1=-1;
		selection_y_1=-1;
		selection_x_2=-1;
		selection_y_2=-1;
		return;
	}

	if(long_pressed_button_l==1 && selection_x_1==-1 && selection_y_1==-1) {
		selection_x_1=cur_x;
		selection_y_1=cur_y;
		return;
	}

	if(long_pressed_button_l!=0 && selection_x_1!=-1) {
		selection_x_2=cur_x;
		selection_y_2=cur_y;
	}
}

void put_pattern(Uint8 * terrain, int x, int y) {
	int x_pattern,y_pattern,pattern_height;

	x_pattern = x % current_pattern.object_x_len;
	y_pattern = y % current_pattern.object_y_len;
	pattern_height = *(current_pattern.object_mem+y_pattern*current_pattern.object_x_len+x_pattern);

    if(pattern_height) {
        switch(tolerance_replace_mode) {
            case tolerance_replace_equal: setHeight(terrain, x, y, pattern_height); break;
            case tolerance_replace_plus: risePoint(terrain, x, y, pattern_height); break;
            case tolerance_replace_minus: sinkPoint(terrain, x, y, pattern_height); break;
        }
    }
}

void replacePoint(Uint8 *terrain, int x, int y) {
    if(tolerance_replace_mode_2 == replace_mode_pattern)
        put_pattern(terrain, x, y);
    else {
        switch(tolerance_replace_mode) {
            case tolerance_replace_equal: setHeight(terrain, x, y, color_1); break;
            case tolerance_replace_plus: risePoint(terrain, x, y, color_1); break;
            case tolerance_replace_minus: sinkPoint(terrain, x, y, color_1); break;
        }
    }
}

int isFilled(int x, int y) {
    return *(temp_buffer + y * WIDTH + x) == already_filled ? 1 : 0;
}

void setFilled(int x, int y) {
    *(temp_buffer + y * WIDTH + x) = already_filled;
}

void setPendingFill(int x, int y) {
    *(temp_buffer + y * WIDTH + x) = pending_filled;
}

void setPendingFillIfNeeded(int x, int y, int tolerance, int deltaMax) {
    int currentHeight = getHeight(terrain_height, x, y);

    if(isHeightInsideLimits(tolerance, currentHeight, deltaMax) && !isFilled(x, y)) {
        setPendingFill(x, y);
    }
}

void replaceVerticalLine(int x, int yIni, int yFin) {
    int y;

    for(y = yIni; y <= yFin; y++) {
		curent_height = getHeight(terrain_height, x, y);

		if(isHeightInsideLimits(tolerance_mode, curent_height, color_2) && !isFilled(x, y)) {
            replacePoint(terrain_height, x, y);
            setFilled(x, y);

			//now, scan for the up and down neighbours
			if(x > 0) setPendingFillIfNeeded(x-1, y, tolerance_mode, color_2);
            if(x < WIDTH-1) setPendingFillIfNeeded(x+1, y, tolerance_mode, color_2);
        }
		else break;
	}
}

void replaceVerticalLineIfNeeded(int x, int y, int tolerance_mode, int deltaMax) {
    int curent_height = getHeight(terrain_height, x - WIDTH, y);

    if(isHeightInsideLimits(tolerance_mode, curent_height, deltaMax) && !isFilled(x - WIDTH, y)) {
        replace_ver_line(x, y);
    }
}

void replaceHorizontalLine(int xIni, int xFin, int y) {
    int x;

    for(x = xIni; x < xFin; x++) {
        curent_height = getHeight(terrain_height, x, y);

        if(isHeightInsideLimits(tolerance_mode, curent_height, color_2) && !isFilled(x y)) {
            replacePoint(terrain_height, x, y);
            setFilled(x, y);

            //now, scan for the up and down neighbours
            if(y>0) replaceVerticalLineIfNeeded(x - WIDTH, y, tolerance_mode, color_2);
            if(y < HEIGHT-1) replaceVerticalLineIfNeeded(x + WIDTH, y, tolerance_mode, color_2);
        }
        else break;
    }
}

//Replaces two lines, upwards and downwards
void replace_ver_line(int orig_x, int orig_y) {
    replaceVerticalLine(orig_x, 0, orig_y);
    replaceVerticalLine(orig_x, orig_y + 1, HEIGHT - 1);
}

//Scans left and right
void replace_line(short orig_x, short orig_y) {
    replaceLine(0, orig_x, orig_y);
    replaceLine(orig_x + 1, WIDTH - 1, orig_y);
}

int isHeightInsideLimits(int condition, int height, int deltaMax) {
    int maximum = currentHeight;
    int minimum = currentHeight;

    switch(condition) {
        case greater_or_leaser:
            maximum += deltaMax;
            minimum -= deltaMax;
            break;
        case greater: maximum += deltaMax; break;
        case leaser: minimum -= deltaMax; break;
    }

    return (currentHeight >= minimum && currentHeight <= maximum) ? 1 : 0;
}

//the fill tool
void pre_change_area()
{
  int i,x,y;
  int map_size=WIDTH*HEIGHT;
  char * some_temp_buffer;
  bool no_pending_found=0;
  if (!get_cur_x_y())return;
  //try to see if the desired filling mode is pattern fill, and if we have a current pattern.
  if(tolerance_replace_mode_2==replace_mode_pattern)
  {
	  if(!current_pattern.object_mem)
	  {
					sprintf(error_msg_1,"Pattern filling mode, but there is no pattern!");
					sprintf(error_msg_2,"Righ click on the Magic Wand tool, and select a pattern!");
					view_error_menu=1;
					return;
	  }

  }

  change_cursor(cursor_wait);

  color_2 = *(terrain_height + cur_y * WIDTH + cur_x);	//get the deepth
  some_temp_buffer=temp_buffer;
  for (i = 0; i <map_size; i++)*(some_temp_buffer++)=not_filled;//clear the temp buffer
  replace_line((short)cur_x,(short)cur_y);
	while(1)
	{
		no_pending_found=0;
		some_temp_buffer=temp_buffer;
		for(i=0;i<map_size;i++)
		if(*(some_temp_buffer++)==pending_fill)
			{
				no_pending_found=1;
				y=i/WIDTH;
				x=i-y*WIDTH;
				replace_line((short)x,(short)y);
			}
		if(!no_pending_found)break;
	}
	some_temp_buffer=temp_buffer;
	for (i = 0; i <map_size; i++)*(some_temp_buffer++)=not_filled;//clear the temp buffer
	change_cursor(last_cursor);
}

void floodVerticalLine(int x, int yIni, int yFin, int height) {
    for (y = xIni; y <= xFin; y++) {
		if(getHeight(x, y) != height) {
			setHeight(x, y, height);
            setFilled(x, y);

            //now, scan for the up and down neighbours
			if(x > 0 && getHeight(x-1, y) != height) setPendingFill(x-1, y);
			if(x < WIDTH-1 && getHeight(x+1, y) != height) setPendingFill(x+1, y);
		}
		else break;
	}
}

void floodLine(int xIni, int xFin, int y, int height) {
    int x;

    for(x = xIni; x <= xFin; x++) {

		if(getHeight(x, y) != color_1) {
            setHeight(x, y, color_1);
            setFilled(x, y);

			//now, scan for the up and down neighbours
			if(y > 0 && getHeight(x - WIDTH, y) != color_1) flood_ver_line(x, y-1);
			if(y < HEIGHT-1 && getHeight(x + WIDTH, y) != color_1) flood_ver_line(x, y+1);
		}
		 else break;
	}
}

//Fills upwards and downwards
void flood_ver_line(int orig_x, int orig_y) {
    floodVerticalLine(orig_x, 0, orig_y, color_1);
    floodVerticalLine(orig_x, orig_y + 1, HEIGHT - 1, color_1);
}

//Scans left an right
void flood_line(short orig_x,short orig_y) {
    floodLine(0, orig_x, orig_y, color_1);
    floodLine(orig_x + 1, WIDTH, orig_y, color_1);
}

//the fill tool
void pre_flood_area () {
  int i,x,y;
  int map_size=WIDTH*HEIGHT;
  char * some_temp_buffer;
  bool no_pending_found=0;
  if (!get_cur_x_y ())return;
  change_cursor(cursor_wait);

  some_temp_buffer=temp_buffer;
  for (i = 0; i <map_size; i++)*(some_temp_buffer++)=not_filled;//clear the temp buffer
  flood_line((short)cur_x,(short)cur_y);
  while(1) {
		no_pending_found=0;
		some_temp_buffer=temp_buffer;
		for(i=0;i<map_size;i++)
		if(*(some_temp_buffer++)==pending_fill) {
				no_pending_found=1;
				y=i/WIDTH;
				x=i-y*WIDTH;
				flood_line((short)x,(short)y);
		}
		if(!no_pending_found)break;
	}
	some_temp_buffer=temp_buffer;
	for (i = 0; i <map_size; i++)*(some_temp_buffer++)=not_filled;//clear the temp buffer
	change_cursor(last_cursor);
}

void draw_brush_line () {
  int start_x, start_y, x_len, y_len;
  int i = 0;
  int line_lenght;
  float xstep, ystep, x, y;

  if (!get_cur_x_y ()) {
    last_drawn_x = -1;
    last_drawn_y = -1;
    return;			//nope, not on the map
  }

  line_lenght = getLineLength(&xstep, &ystep);

  //ok, now update the last drawn x and y
  last_drawn_x = cur_x;
  last_drawn_y = cur_y;
  x = cur_x;
  y = cur_y;

  for (i = 0; i <= line_lenght; i++) {
    draw_brush (x, y);
    x += xstep;
    y += ystep;
  }
}

/*
   Ok, now, if the user moves the mouse very fast, what s/he draws will be fragmented.
   So, we need to do some sort of interpolations, and draw lines.
 */
int getLineLength(float *xstep, float *ystep) {
  int line_length;
  int delta_x, delta_y;

  delta_x = (last_drawn_x == -1) ? 0 : last_drawn_x - cur_x;
  delta_y = (last_drawn_y == -1) ? 0 : last_drawn_y - cur_y;

  line_length = (int) sqrt (pow(delta_x, 2) + pow(delta_y, 2));

  *xstep = (float) delta_x / line_length;
  *ystep = (float) delta_y / line_length;

  return line_length;
}

void draw_brush (int this_cur_x, int this_cur_y) {
  Rectangle brush;
  int x, y;

  clearTempBuffer();
  undo = partial_undo;//the undo type we have here

  calculateRectangleBrush(&brush, this_cur_x, this_cur_y, brush_size);

  for (y = brush.ymin; y <= brush.ymax; y++)
    for (x = brush.xmin; x <= brush.xmax; x++)
      if (isPointInWindow(x, y) && getHeightOld(temp_buffer, x, y) == NOT_MODIFIED) {
        applyBrushInPixel(x, y);

        //and, we should also clear the buffer, at the next mouse up event.
	      clear_temp_buffer = 1;
	    }
}

void applyBrushInPixel(int x, int y) {
  switch(current_tool) {
    case t_place:    setHeightOld(terrain_height, x, y, color_1); break;
    case t_escavate: decHeightOld(terrain_height, x, y, color_1); break;
    case t_elevate:  incHeightOld(terrain_height, x, y, color_1); break;
  }

  setHeightOld(temp_buffer, x, y, MODIFIED);
  updateMinMaxDrawnCoords(x, y);
}

/*
Rectangle with centre in the cursor and size of 'brush'
Brush size -> [1 = 1px, 2 = 3px, 3 = 5px, 4 = 7px, 5 = 9px]
The rectangle is calculated in pixels given the brush number
*/
void calculateRectangleBrush(Rectangle *brush, int xcursor, int ycursor, int size) {
  int delta = size - 1;
  brush->ymin = ycursor - delta;
  brush->xmin = xcursor - delta;
  brush->xmax = xcursor + delta;
  brush->ymax = ycursor + delta;
}

void clearTempBuffer() {
  //see if we have to clear the temp buffer
  if(clear_temp_buffer && long_pressed_button_l == 1) {
		do_clear_temp_buffer ();
		clear_temp_buffer = 0;
		min_drawn_x = 0xffff;
		min_drawn_y = 0xffff;
		max_drawn_x = 0;
		max_drawn_y = 0;
  }
}

void updateMinMaxDrawnCoords(int x, int y) {
  //now, update the min and max drawn
  if (x < min_drawn_x) min_drawn_x = x;
  if (y < min_drawn_y) min_drawn_y = y;
  if (x > max_drawn_x) max_drawn_x = x;
  if (y > max_drawn_y) max_drawn_y = y;

  //11111111 11111111 11111111 11111100 wtf??
  //00000000 00000000 00000000 00000011 wtf??
  max_drawn_x = max_drawn_x & 0xfffc;
  min_drawn_x = min_drawn_x | 3;
}

int isPointInWindow(int x, int y) {
  return (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT) ? 1 : 0;
}

int getHeightOld(Uint8 *terrain, int x, int y) {
  return *(terrain + y * WIDTH + x);
}

void setHeightOld(Uint8 *terrain, int x, int y, int colour) {
  *(terrain + y * WIDTH + x) = colour;
}

void incHeightOld(Uint8 *terrain, int x, int y, int delta) {
  int newColour = getHeightOld(terrain, x, y) + delta;
  setHeightOld(terrain, x, y, (newColour < 255 ? newColour : 255));
}

void decHeightOld(Uint8 *terrain, int x, int y, int delta) {
  int newColour = getHeightOld(terrain, x, y) - delta;
  setHeightOld(terrain, x, y, (newColour > 0 ? newColour : 0));
}

void stamp_object() {
    int object_x_start=0;
    int object_y_start=0;
    int object_x_terrain_start,object_y_terrain_start;
    int object_x_terrain_end,object_y_terrain_end;

    int x,y,j,k;
    int cur_height;

    getTerrainCoords()
    //ok, now just display the object
    j=object_y_start;

    for(y=object_y_terrain_start;y<object_y_terrain_end;y++) {
        k=object_x_start;

        for(x=object_x_terrain_start;x<object_x_terrain_end;x++) {
            cur_height=*(current_object.object_mem+j*current_object.object_x_len+k);

            if(cur_height) {
                switch(object_mode) {
                    case put_object: setHeight(x, y, cur_height); break;
                    case add_object: risePoint(x, y, cur_height); break;
                    case sub_object: sinkPoint(x, y, cur_height); break;
                }
            }
            k++;
        }
        j++;
    }
}

void getTerrainCoords() {
    object_x_terrain_start = ((x_mouse_pos-x_screen_offset)-(current_object.object_x_len/2*terrain_ratio))/ terrain_ratio + xoffset;
    object_y_terrain_start = ((y_mouse_pos-y_screen_offset)-(current_object.object_y_len/2*terrain_ratio))/ terrain_ratio + yoffset;
    object_x_terrain_end = ((x_mouse_pos-x_screen_offset)+(current_object.object_x_len/2*terrain_ratio))/ terrain_ratio + xoffset;
    object_y_terrain_end = ((y_mouse_pos-y_screen_offset)+(current_object.object_y_len/2*terrain_ratio))/ terrain_ratio + yoffset;

    if(object_x_terrain_start<0) object_x_start=object_x_terrain_start * -1;
    if(object_y_terrain_start<0) object_y_start=object_y_terrain_start * -1;

    if(object_x_terrain_start<0) object_x_terrain_start = 0;
    if(object_y_terrain_start<0) object_y_terrain_start = 0;
    if(object_x_terrain_end>WIDTH) object_x_terrain_end = WIDTH;
    if(object_y_terrain_end>HEIGHT) object_y_terrain_end = HEIGHT;
}
