#ifndef ACTIONS_H
#define ACTIONS_H

#include <stdio.h>

#include "../global.h"

void actionExit(Events *eventsInfo);

void actionRotate90(Events *eventsInfo);
void actionRotate180(Events *eventsInfo);
void actionRotate270(Events *eventsInfo);
void actionFlipX(Events *eventsInfo);
void actionFlipY(Events *eventsInfo);

#endif
