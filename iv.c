#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

int main() {
    //1. Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
    //2. Create a window
    SDL_Window *pwindow = SDL_CreateWindow(
        "ImageViewer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        900,
        600,
        SDL_WINDOW_SHOWN);
    if (!pwindow) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        //3. Pause for 16 milliseconds
    SDL_Delay(16); // prevent CPU burn (~60 FPS)
    }



    //4. Clean up and quit SDL
    SDL_DestroyWindow(pwindow);
    SDL_Quit();
    return 0;
}
