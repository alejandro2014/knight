#include "actions.h"

void actionExit(Events *eventsInfo) {
    eventsInfo->finish = true;
}

void actionRotate90(Events *eventsInfo) {
    eventsInfo->angleRotation = 90;
}

void actionRotate180(Events *eventsInfo) {
    eventsInfo->angleRotation = 180;
}

void actionRotate270(Events *eventsInfo) {
    eventsInfo->angleRotation = 270;
}

void actionFlipX(Events *eventsInfo) {

}

void actionFlipY(Events *eventsInfo) {

}
