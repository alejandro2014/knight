#include <stdio.h>
#include "menus.h"
#include "helper.h"
#include "widgets.h"
#include "terrain.h"
#include "hme_lowlevel.h"

void printDialogs(Dialog **dialogs) {
    Dialog *dialog = NULL;
    Button *button = NULL;
    CheckBox *checkBox = NULL;
    TextBox *textBox = NULL;
    Text *text = NULL;

    int i, j;

    for(i = 0; i < NUM_DIALOGS; i++) {
        dialog = *(dialogs + i);
        printf("[INFO] ===== Dialog %s =====\n", dialog->name);

        for(j = 0; j < dialog->numButtons; j++) {
            button = *(dialog->buttons + j);
            printf("[INFO]    * button (%s, %d, %d, %d, %d)\n", button->title, button->x, button->y, button->width, button->height);
        }

        for(j = 0; j < dialog->numCheckBoxes; j++) {
            checkBox = *(dialog->checkBoxes + j);
            printf("[INFO]    * checkBox (%s, %d, %d, %d, %d)\n", checkBox->text, checkBox->x, checkBox->y, checkBox->width, checkBox->height);
        }

        for(j = 0; j < dialog->numTextBoxes; j++) {
            textBox = *(dialog->textBoxes + j);
            printf("[INFO]    * textBox (%s, %d, %d, %d, %d)\n", textBox->title, textBox->x, textBox->y, textBox->width, textBox->height);
        }

        for(j = 0; j < dialog->numTexts; j++) {
            text = *(dialog->texts + j);
            printf("[INFO]    * text (%s, %d, %d)\n", text->string, text->x, text->y);
        }
    }
}

void showTerrainCmd(Terrain *terrain) {
  int i, j;
  int columns = terrain->width;
  int rows = terrain->height;
  int value;

  printf("Printing terrain %p\n", terrain);
  for(i = 0; i < rows; i++) {
    printLine(columns);
    for(j = 0; j < columns; j++) {
      printf("| ");
      value = getHeight(terrain, j, i);
      if(value < 100) printf(" ");
      if(value < 10) printf(" ");
      printf("%d ", value);
    }
    printf("|\n");
  }
  printLine(columns);

  /*Point *point;
  int pointsNo = terrain->pointsNo;

  for(i = 0; i < pointsNo; i++) {
    point = terrain->points + i;
    //printf("points(%u) = (%d, %d, %d)\n", i, point->x, point->y, point->z);
}*/
}

void printLine(int width) {
  int i;

  for(i = 0; i < width; i++) printf("+-----");
  printf("+\n");
}
