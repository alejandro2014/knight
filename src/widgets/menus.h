#ifndef MENUS_H
#define MENUS_H

#include <SDL2/SDL.h>

#include "../global.h"
#include "../font.h"

typedef struct {
	SDL_Rect *coords;
	char *title;
	int padding;
} Button;

typedef struct {
	SDL_Rect *coords;
	char *title;
} TextBox;

typedef struct {
	SDL_Rect *coords;
	char *string;
} Text;

typedef struct {
    SDL_Rect *coords;
    char *text;
    bool enabled;
} CheckBox;

typedef struct {
    char *name;
	SDL_Rect *coords;
	char *title;

    TextBox **textBoxes;
    Button **buttons;
    CheckBox **checkBoxes;
    Text **texts;

    int numTextBoxes;
    int numButtons;
    int numCheckBoxes;
    int numTexts;

    bool show;
    Font *font;
} Dialog;

typedef struct {
    int textBoxesNo;
    TextBox *textBoxes;
} TextBoxContainer;

typedef struct {
    int buttonsNo;
    Button *buttons;
} ButtonContainer;

Dialog *loadDialog(char *dialogId);
void drawWindowTitle(SDL_Renderer *renderer, Dialog *dialog);
void drawTextBox(TextBox *textbox);
void drawTextBoxes(TextBoxContainer *textBoxContainer);
void drawButton(Button *button);
void drawButtons(ButtonContainer *buttonContainer);
void drawDialogWindow(SDL_Renderer *renderer, Dialog *dialog);

#endif
