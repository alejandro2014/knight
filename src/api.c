#include "api.h"

void api_rotate(int angle) {
    switch(angle) {
        case 90: rotate_90_CW(); break;
        case 180: rotate_180(); break;
        case 270: rotate_90_CCW(); break;
    }
}
