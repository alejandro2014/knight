#ifndef INIT_H
#define INIT_H

#include "global.h"

typedef tool_bar_struct Button;

void build_tool_bar();
void build_numeric_dialog_boxes();
void buildToolBarButton(int iconId, int windowMessage, int iconActive, int iconPush, int iconNotPush, int righClickMessage, char *tooltip, int mouseOverTimer);
TextBox *buildNumericTextbox(int max, int min, int current, int offset, int length, int hasFocus, int isPressed);
void build_cursors();
void assignCursor(int cursor, int hotX, int hotY);

#endif
