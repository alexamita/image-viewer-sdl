#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

int main() {
    const int width = 900;
    const int height = 600;

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
        width,
        height,
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

        // Get the window surface
        SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

        // Fill the surface with red color
        Uint32 color = SDL_MapRGB(psurface->format, 255, 0, 0);
        SDL_Rect pixel = (SDL_Rect){0, 0, 1, 1};
        SDL_FillRect(psurface, NULL, color);

        // Update the window surface to reflect changes
        SDL_UpdateWindowSurface(pwindow);
        //Pause for 16 milliseconds after each loop iteration to prevent CPU burn (~60 FPS)
        SDL_Delay(16);

    }
    //3. Clean up and quit SDL
    SDL_DestroyWindow(pwindow);
    SDL_Quit();
    return 0;
}
