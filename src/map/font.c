#include "font.h"

SDL_Texture *printString(TTF_Font *font, SDL_Renderer *renderer, char *string, int x, int y) {
    SDL_Color fgColor = {255, 255, 255};
    SDL_Color bgColor = {0, 170, 0};

    SDL_Texture *texture = getStringTexture(font, renderer, string, fgColor, bgColor);

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
