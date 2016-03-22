#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_events.h>

#include "../map/font.h"
#include "menus.h"

void drawWindowTitle(Dialog *dialog) {
	/*SDL_Rect rectangleMenu;
	rectangleMenu.w = dialog->width;
	rectangleMenu.h = 19;
	rectangleMenu.x = dialog->x;
	rectangleMenu.y = dialog->y;

    SDL_SetRenderDrawColor(renderer, 0, 0, 100, 255);
    SDL_RenderFillRect(renderer, &rectangleMenu);
    SDL_RenderPresent(renderer);

	printString(dialog->title, dialog->x + 1, dialog->y + 1);*/
}

void drawTextBox(TextBox *textbox) {
	/*DialogBox *dialogBox = textbox->dialogBox;
	int barHeight = 19;
	int textWidth;

	SDL_Texture *printTexture = printString(textbox->title, textbox->x, textbox->y + barHeight);
    SDL_QueryTexture(printTexture, NULL, NULL, &textWidth, NULL);

	SDL_Rect rectangleTextBox;
	rectangleTextBox.w = textbox->width;
	rectangleTextBox.h = textbox->height;
	rectangleTextBox.x = textbox->x + textWidth + 1;
	rectangleTextBox.y = textbox->y + barHeight;

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderFillRect(renderer, &rectangleTextBox);
    SDL_RenderPresent(renderer);

	printString("1000", rectangleTextBox.x + 2, rectangleTextBox.y);*/
}

void drawTextBoxes(TextBoxContainer *textBoxContainer) {
	int i;

	for(i = 0; i < textBoxContainer->textBoxesNo; i++) {
		drawTextBox(textBoxContainer->textBoxes + i);
	}
}

void drawButton(Button *button) {
	/*Menu *menu = button->menu;
	int barWidth = 19;

	SDL_Rect buttonBox;
	buttonBox.w = button->width + (button->padding * 2);
	buttonBox.h = button->height + (button->padding * 2);
	buttonBox.x = menu->x + button->x + 2;
	buttonBox.y = menu->y + button->y + barWidth;

	SDL_FillRect(currentScreen, &buttonBox, YELLOW);
	printString(currentScreen, button->title, menu->x + button->x, menu->y + button->y + barWidth);*/
}

void drawButtons(ButtonContainer *buttonContainer) {
	int i;

	for(i = 0; i < buttonContainer->buttonsNo; i++) {
		//drawButton(buttonContainer->buttons + i, currentScreen);
	}
}

void drawDialogWindow(Dialog *dialog) {
	/*SDL_Rect rectangleMenu;
	rectangleMenu.x = dialog->x;
	rectangleMenu.y = dialog->y;
	rectangleMenu.w = dialog->width;
	rectangleMenu.h = dialog->height;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rectangleMenu);
    SDL_RenderPresent(renderer);

	drawWindowTitle(dialog);*/
}
