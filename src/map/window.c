#include <SDL2/SDL.h>
#include "window.h"

/*void programLoop() {
    bool finish = false;
    //SDL_Event event;
    int i = 5;

    //while(!finish) {
    for(i = 0; i < 5; i++) {
        //readEvents(&finish);
        //drawScreen();
        printf("Iteration %d\n", i);
        SDL_Delay(1000);
    }
}*/

void testVideo() {
    SDL_Init(SDL_INIT_VIDEO);
    printf("Testing video\n");
    SDL_Quit();
}
