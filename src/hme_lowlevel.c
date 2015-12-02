int isFilled(int x, int y) {
    return *(temp_buffer + y * WIDTH + x) == already_filled ? 1 : 0;
}

void setFilled(int x, int y) {
    *(temp_buffer + y * WIDTH + x) = already_filled;
}

void setPendingFill(int x, int y) {
    *(temp_buffer + y * WIDTH + x) = pending_filled;
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

void risePoint(Uint8 *terrain, int x, int y, int delta) {
    int currentHeight = getHeight(terrain, x, y);
    int nextHeight = currentHeight + delta;

    nextHeight = (nextHeight < 255) ? nextHeight : 255;
    setHeight(terrain, x, y, nextHeight);
}

void sinkPoint(Uint8 *terrain, int x, int y, int delta) {
    int currentHeight = getHeight(terrain, x, y);
    int nextHeight = currentHeight + delta;

    nextHeight = (nextHeight > 0) ? nextHeight : 0;
    setHeight(terrain, x, y, nextHeight);
}

void setHeight(Uint8 *terrain, int x, int y, int height) {
    *(terrain + y * WIDTH + x) = height;
}

unsigned int valueCell(Terrain *terrain, int x, int y) {
  return hmeGetHeight(terrain, x, y);;
}

Point *hmeGetPoint(Terrain *terrain, int x, int y) {
  return terrain->points + (y * terrain->width + x);
}

Uint32 hmeGetHeight(Terrain *terrain, Uint32 x, Uint32 y) {
    return (terrain->points + (y * terrain->width + x))->z;
}

void hmeSetHeight(Terrain *terrain, Uint32 x, Uint32 y, Uint32 height) {
  Point *point = hmeGetPoint(terrain, x, y);
  if(point->isHeightSetted) return;

  countPoints++;
  point->z = height;
  point->isHeightSetted = true;
}

void putPixel(SDL_Surface *currentScreen, Uint32 x, Uint32 y, Uint32 colour) {
  *((Uint32 *)currentScreen->pixels + y * currentScreen->w + x) = colour;
}
