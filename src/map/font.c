#include "font.h"

Font *initFont(char *path) {
    TTF_Init();

    alloc(font, Font, 1);

    font->type = TTF_OpenFont(path, 16);

    if(font->type == NULL) {
        printf("Could not load the font\n");
        return NULL;
    }

    SDL_Color fgColor = {180, 180, 180};
    SDL_Color bgColor = {50, 50, 50};

    font->fgColor = fgColor;
    font->bgColor = bgColor;

    return font;
}

SDL_Texture *printString(Font *font, SDL_Renderer *renderer, char *string, int x, int y) {
    SDL_Texture *texture = getStringTexture(font->type, renderer, string, font->fgColor, font->bgColor);

    SDL_Rect textLocation;
    textLocation.x = x;
    textLocation.y = y;

    SDL_QueryTexture(texture, NULL, NULL, &textLocation.w, &textLocation.h);
    SDL_RenderCopy(renderer, texture, NULL, &textLocation);

    return texture;
}

SDL_Texture *getStringTexture(TTF_Font *font, SDL_Renderer *renderer, char *string, SDL_Color fgColor, SDL_Color bgColor) {
    SDL_Surface *textSurface = TTF_RenderText_Shaded(font, string, fgColor, bgColor);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    return texture;
}

/*void draw_char (SDL_Surface * this_screen, Uint8 my_char, char font_color, char background_color, int char_xscreen, int char_yscreen) {
  int x, y, my_pitch;
  char cur_pixel;
  Uint8 *screen_buffer;
  screen_buffer = (Uint8 *) this_screen->pixels;
  my_pitch = this_screen->pitch;
  screen_buffer += char_yscreen * my_pitch + char_xscreen;
  my_char -= 32;

  for (y = y_font_bmp - 1; y != -1; y--)
  {
    for (x = my_char * char_lenght; x < my_char * char_lenght + char_lenght;
	 x++)
    {
      cur_pixel = *(font_mem + x_font_bmp * y + x + 2);
      if (cur_pixel)
	*(++screen_buffer) = font_color;
      else
	*(++screen_buffer) = background_color;
    }
    screen_buffer += my_pitch - char_lenght;
  }

}

void print_string (char *str, char char_color, char background_color, int char_xscreen, int char_yscreen) {
  while (*(str) != 0) {
    draw_char (screen, *str, char_color, background_color, char_xscreen, char_yscreen);
    str++;
    char_xscreen += char_lenght;
  }
}*/
