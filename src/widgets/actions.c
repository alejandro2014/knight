#include "actions.h"

void action_exit(Events *eventsInfo) {
    eventsInfo->finish = true;
}
