Terrain *currentTerrain = NULL;
int MAX_HEIGHT = 255;
int MIN_HEIGHT = 0;

void setHeight(int x, int y, int height) {
    Terrain *terrain = currentTerrain;
    Point *point = getPoint(terrain, x, y);
    if(point->isHeightSetted) return;

    countPoints++;
    point->z = height;
    point->isHeightSetted = true;
}

void incHeight(int x, int y, int delta) {
    Terrain *terrain = currentTerrain;
    int newHeight = getHeight(terrain, x, y) + delta;
    setHeightOld(terrain, x, y, (newHeight < MAX_HEIGHT ? newHeight : MAX_HEIGHT));
}

void decHeight(int x, int y, int delta) {
    Terrain *terrain = currentTerrain;
    int newHeight = getHeight(terrain, x, y) - delta;
    setHeight(terrain, x, y, (newHeight > MIN_HEIGHT ? newHeight : MIN_HEIGHT));
}

int isFilled(int x, int y) {
    Terrain *terrain = currentTerrain;
    Point *point = getPoint(terrain, x, y);
    return point->fillStatus == already_filled ? 1 : 0;
}

void setFilled(int x, int y) {
    setFillStatus(x, y, already_filled);
}

void setPendingFill(int x, int y) {
    setFillStatus(x, y, pending_filled);
}

void setFillStatus(int x, int y, int fillStatus) {
    Terrain *terrain = currentTerrain;
    Point *point = getPoint(terrain, x, y);
    point->fillStatus = fillStatus;
}

Point *getPoint(Terrain *terrain, int x, int y) {
  return terrain->points + (y * terrain->width + x);
}

//====================
int isPointInWindow(int x, int y) {
  return (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT) ? 1 : 0;
}

void putPixel(SDL_Surface *currentScreen, Uint32 x, Uint32 y, Uint32 colour) {
  *((Uint32 *)currentScreen->pixels + y * currentScreen->w + x) = colour;
}
