/*******************************************************
 * Parts of this code are stolen and modified from sdlplasma,
 * by Stefan Hellkvist, stefan@hellkvist.org
 * Copyright: see GPL
 *******************************************************/
#include "generate_terrain.h"

#include "cursors.h"

__inline int getPixel (int x, int y) {
  return *(terrain_height + (y * WIDTH + x));
}

__inline void putPixel (int x, int y, Uint8 color) {
  *(terrain_height + (y * WIDTH + x)) = color;
}

__inline int mrandom (int max) {
  return (int) ((float) max * rand () / (RAND_MAX + 120.0));
}

__inline int getNewColor (int c1, int c2, int dist) {
  unsigned int this_height;
  unsigned int random_displacement;
  random_displacement = (mrandom (dist) - dist / 2);

  this_height = (c1 + c2 + random_displacement);
  if (this_height < 512)
    this_height = this_height / 2;
  else
    this_height = this_height / 3;
  return this_height;
}

__inline int getNewColor4 (int c1, int c2, int c3, int c4, int dist) {
  unsigned int this_height;
  unsigned int random_displacement;
  random_displacement = (mrandom (dist) - dist / 2);

  this_height = (c1 + c2 + c3 + c4 + random_displacement);
  if (this_height < 1024)
    this_height = this_height / 4;
  else
    this_height = this_height / 5;
  return this_height;
}

// NON INLINE

void drawSeed (int width, int height) {
  putPixel (0, 0, mrandom (255));
  putPixel (width, 0, mrandom (255));
  putPixel (width, height, mrandom (255));
  putPixel (0, height, mrandom (255));
}

void drawSeed_no_overwrite (int width, int height) {
  if(!getPixel(0,0))putPixel(0,0,mrandom(255));
  if(!getPixel(width,0))putPixel(width,0,mrandom(255));
  if(!getPixel(width,height))putPixel(width,height,mrandom(255));
  if(!getPixel(0,height))putPixel(0,height,mrandom(255));
}

void drawMap (int x1, int y1, int x2, int y2) {
  int midx = (x1 + x2) / 2;
  int midy = (y1 + y2) / 2;

  if (!getPixel (midx, y1))
    putPixel (midx, y1,getNewColor(getPixel (x1, y1), getPixel (x2, y1), x2 - x1));

  if (!getPixel (x2, midy))
    putPixel (x2, midy,getNewColor(getPixel (x2, y1), getPixel (x2, y2), y2 - y1));

  if (!getPixel (midx, y2))
    putPixel (midx, y2,getNewColor(getPixel (x1, y2), getPixel (x2, y2), x2 - x1));

  if (!getPixel (x1, midy))
    putPixel (x1, midy,getNewColor(getPixel (x1, y1), getPixel (x1, y2), y2 - y1));

  if (!getPixel (midx, midy))
    putPixel (midx, midy,
	      getNewColor4 (getPixel (x1, midy), getPixel (x2, midy),
			    getPixel (midx, y1), getPixel (midx, y2),
			    y2 - y1));

  if (x2 > x1 + 1 || y2 > y1 + 1)
  {
    drawMap (x1, y1, midx, midy);
    drawMap (midx, y1, x2, midy);
    drawMap (midx, midy, x2, y2);
    drawMap (x1, midy, midx, y2);
  }
}

int overdraw_terrain(int width, int height) {
  int map_size = width * height;
  int i;
  if(!terrain_height)return 0;//we don't have a terrain
  change_cursor(cursor_wait);
  memset(terrain_height, 0, map_size);

  drawSeed (width - 1, height - 1);
  drawMap (0, 0, width - 1, height - 1);
  change_cursor(last_cursor);
  return 1;
}

int make_terrain (int width, int height) {

  int map_size = width * height;

  if(!terrain_height)return 0;//we don't have a terrain
  change_cursor(cursor_wait);
  drawSeed_no_overwrite(width - 1, height - 1);
  drawMap (0, 0, width - 1, height - 1);
  change_cursor(last_cursor);
  return 1;
}

/*---------------
Memory allocation
---------------*/
void allocate_mem(int width, int height) {
  int map_size = width * height;

  freeMemTerrain(terrain_height);
  freeMemTerrain(temp_buffer);
  freeMemTerrain(undo_buffer);

  undo = no_undo;
  clear_temp_buffer = 0;//needed, otherwise it might crash next time you draw something

  if(allocateMemTerrain2(&terrain_height, map_size) == -1) {
    view_error_menu = 1;
    return;
  }

  if(allocateMemTerrain2(&temp_buffer, map_size) == -1) {
    view_error_menu = 1;
    return;
  }

  if(allocateMemTerrain2(&undo_buffer, map_size) == -1) {
    view_error_menu = 1;
    return;
  }
}

int allocateMemTerrain2(Uint8 **buffer, int map_size) {
  if(allocateMemTerrain(buffer, map_size) == -1) {
    sprintf(error_msg_1,"Not enough memory for the height map!");
    sprintf(error_msg_2,"Please use a smaller map size!");
    freeMemTerrain(*buffer);
    return -1;
  }

  return 0;
}

void clear_mem() {
  freeMemTerrain(terrain_height);
  freeMemTerrain(temp_buffer);
  freeMemTerrain(undo_buffer);
}

int allocateMemTerrain(Uint8 **buffer, int map_size) {
  *buffer = calloc ( map_size, sizeof(Uint8));

  if(*buffer) {
    memset(*buffer, 0, map_size);
    return 0;
  }

  return -1;
}

void freeMemTerrain(Uint8 *buffer) {
  if (buffer)
    free(buffer);
  buffer = NULL;
}
