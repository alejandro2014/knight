#include "brush.h"

void draw_brush_line() {
  int start_x, start_y, x_len, y_len;
  int i = 0;
  int line_lenght;
  float xstep, ystep, x, y;

  if (!get_cur_x_y()) {
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

void draw_brush (int this_cur_x, int this_cur_y) {
  Rectangle brush;
  int x, y;

  clearTempBuffer();
  undo = partial_undo;//the undo type we have here

  calculateRectangleBrush(&brush, this_cur_x, this_cur_y, brush_size);

  for (y = brush.ymin; y <= brush.ymax; y++)
    for (x = brush.xmin; x <= brush.xmax; x++)
      if (isPointInWindow(x, y) && getHeight(temp_buffer, x, y) == NOT_MODIFIED) {
        applyBrushInPixel(x, y);

        //and, we should also clear the buffer, at the next mouse up event.
	      clear_temp_buffer = 1;
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

void applyBrushInPixel(int x, int y) {
  switch(current_tool) {
    case t_place:    setHeightOld(terrain_height, x, y, color_1); break;
    case t_escavate: decHeightOld(terrain_height, x, y, color_1); break;
    case t_elevate:  incHeightOld(terrain_height, x, y, color_1); break;
  }

  api_setHeight(temp_buffer, x, y, MODIFIED);
  updateMinMaxDrawnCoords(x, y);
}
