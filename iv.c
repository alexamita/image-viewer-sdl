#include <stdio.h>
#include <SDL2/SDL.h>

int main() {
    FILE *in = stdin;
    char line[1024];

    // Read magic number (P6 only) from PPM header
    fgets(line, sizeof(line), in);
    if (line[0] != 'P' || line[1] != '6') {
        fprintf(stderr, "Only P6 PPM format supported\n");
        return 1;
    }

    //Read width and height (skip comments)
    do {
        fgets(line, sizeof(line), in);
    } while (line[0] == '#');

    int width = -1;
    int height = -1;
    sscanf(line, "%d %d", &width, &height);

    // Read max color value (skip comments).
    // line is consumed but ignored since we assume it's 255.
    do {
        fgets(line, sizeof(line), in);
    } while (line[0] == '#');

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

    // Get the window surface --> retrieve CPU accessible pixel buffer for the window
        SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

    // Lock the surface if needed (some pixel formats require locking before access)
    if (SDL_MUSTLOCK(psurface)) {
        SDL_LockSurface(psurface);
    }

    // Read pixel data from stdin and populate the surface
    Uint32 *pixels = (Uint32 *)psurface->pixels;
    // Calculate pitch in terms of number of pixels
    int pitch = psurface->pitch / 4;
    // Read pixel data
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Uint8 r = getchar();
            Uint8 g = getchar();
            Uint8 b = getchar();
            // Map RGB to pixel format and set pixel
            pixels[y * pitch + x] = SDL_MapRGB(psurface->format, r, g, b);
        }
    }

    // Unlock the surface if it was locked
    if (SDL_MUSTLOCK(psurface)) {
    SDL_UnlockSurface(psurface);
    }

    // Update the window surface to reflect changes
    SDL_UpdateWindowSurface(pwindow);

    int app_running = 1;
    SDL_Event event;

    while (app_running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                app_running = 0;
            }
        }
        //Pause for 16 milliseconds after each loop iteration to prevent CPU burn (~60 FPS)
        SDL_Delay(16);
    }
    //3. Clean up and quit SDL
    SDL_DestroyWindow(pwindow);
    SDL_Quit();
    return 0;
}
