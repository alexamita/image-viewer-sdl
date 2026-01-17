🎨 SDL2 PPM Image Viewer in C
A lightweight, minimalist C program that parses raw P6 PPM (Portable Pixmap) images from standard input and renders them directly to a window using SDL2.
This project demonstrates low-level graphics programming concepts, including manual file parsing, direct memory access (DMA) to pixel buffers, and bitwise color mapping.

🌟 Key Features
Standard Input Stream: Reads image data via stdin piping.
Custom Parser: Manually parses PPM headers, handles comments, and extracts metadata without external image libraries.
Direct Surface Access: Manipulates the SDL Surface pixel buffer directly rather than using high-level texture APIs.
Robust Memory Handling: properly calculates memory pitch (stride) to ensure correct pixel alignment across different display resolutions and architectures.
CPU Efficient: Implements a frame-capped event loop (~60 FPS) to prevent 100% CPU usage while the window is open.

🛠️ Technical Implementation Details
1. The P6 Format
The program reads the P6 binary format, which consists of a text header followed by raw byte data:

    P6             <-- Magic Number
    #Comment(s)    <-- Comment skipping logic implemented
    800 600        <-- Width / Height
    255            <-- Max color value
    [BINARY DATA...]

2. Pixel Mapping & Memory Pitch
A common pitfall in graphics programming is assuming a row of pixels equals Width * BytesPerPixel. Modern GPUs often add padding to rows for memory alignment.
This code handles alignment by using the SDL pitch:

    //Pitch is the actual length of a row in bytes
   
    int pitch = psurface->pitch / 4; // Divided by 4 for 32-bit pixels

    //We calculate the exact memory address for every pixel
   
    pixels[y * pitch + x] = SDL_MapRGB(psurface->format, r, g, b);

Note: SDL_MapRGB is used to automatically handle Endianness (byte order) and the specific pixel format of the host machine (e.g., ARGB8888 vs RGBA8888).

🚀 Getting Started
Prerequisites
    C Compiler: GCC or Clang
    SDL2 Library:
        Debian/Ubuntu: sudo apt install libsdl2-dev
        macOS: brew install sdl2
        Windows: MinGW or SDL2 Development Libraries

Compilation
    Compile the program using gcc and link against SDL2:

    gcc iv.c -o iv `sdl2-config --cflags --libs`
    (If sdl2-config is unavailable, use -lSDL2)

📖 Usage
Because the program reads from stdin, you must redirect a file into it. This allows you to generate images on the fly or read from existing files.
Option 1: Read a file
    ./ppm_viewer < image.ppm
Option 2: Pipe from another program (e.g., ImageMagick)
    # Convert a JPG to PPM and pipe it immediately to the viewer
    convert image.jpg ppm:- | ./ppm_viewer


📝 Example Output
Upon running the command, a native OS window opens sized exactly to the image dimensions, rendering the binary data pixel-by-pixel.

🔮 Future Improvements
Add support for P3 (ASCII) PPM format.
Implement window resizing (currently fixed to image size).
Add keyboard shortcuts (e.g., ESC to quit).
Switch to SDL_Texture and SDL_Renderer for hardware acceleration.

📄 License
This project is open source and available for educational purposes.
