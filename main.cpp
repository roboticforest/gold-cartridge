#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

SDL_Window* main_window = nullptr;
SDL_Renderer* drawing_area = nullptr;
SDL_Texture* test_image = nullptr;

SDL_Color DEFAULT_CLEAR_COLOR;

void log_SDL_error(std::string message) {
    std::cerr << message << std::endl;
    std::cerr << "SDL says: " << SDL_GetError << std::endl;
}

void dump_render_info(SDL_Renderer * sdl_renderer, std::string label) {

    SDL_RendererInfo renderer_details;
    SDL_GetRendererInfo(sdl_renderer, &renderer_details);

    std::cout << label << std::endl;
    std::cout << "" << "Renderer Details:" << std::endl;
    std::cout << "Name: " << renderer_details.name << std::endl;
    std::cout << "Max Width: " << renderer_details.max_texture_width << std::endl;
    std::cout << "Max Height: " << renderer_details.max_texture_height << std::endl;
    std::cout << "Texture Fmt Cnt: " << renderer_details.num_texture_formats << std::endl;
    std::cout << "SDL_RENDERER_SOFTWARE:      " << ((renderer_details.flags & SDL_RENDERER_SOFTWARE) > 0) << std::endl;
    std::cout << "SDL_RENDERER_ACCELERATED:   " << ((renderer_details.flags & SDL_RENDERER_ACCELERATED) > 0) << std::endl;
    std::cout << "SDL_RENDERER_PRESENTVSYNC:  " << ((renderer_details.flags & SDL_RENDERER_PRESENTVSYNC) > 0) << std::endl;
    std::cout << "SDL_RENDERER_TARGETTEXTURE: " << ((renderer_details.flags & SDL_RENDERER_TARGETTEXTURE) > 0) << std::endl;
}

void startup() {
    // Initialize the SDL.
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {log_SDL_error("Audio Playback failed to initialize!"); abort();}
    if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0) {log_SDL_error("Events Polling failed to initialize!"); abort();}
    if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0) {log_SDL_error("Game Controllers failed to initialize!"); abort();}
    if (SDL_InitSubSystem(SDL_INIT_HAPTIC) < 0) {log_SDL_error("Haptic Feedback failed to initialize!"); abort();}
    if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0) {log_SDL_error("Joystick Input failed to initialize!"); abort();}
    if (SDL_InitSubSystem(SDL_INIT_TIMER) < 0) {log_SDL_error("Timers failed to initialize!"); abort();}
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {log_SDL_error("Video failed to initialize!"); abort();}

    // Create the application window.
    main_window = SDL_CreateWindow("Main Window",
                                   SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   WINDOW_WIDTH, WINDOW_HEIGHT,
                                   SDL_WINDOW_SHOWN);
    if (!main_window) { log_SDL_error("Main game window could not be created!"); abort();}

    // drawing_area = SDL_GetRenderer(main_window);
    // dump_render_info(drawing_area, "Default Window Renderer");
    drawing_area = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED);
    //dump_render_info(drawing_area, "New Window Renderer");
    DEFAULT_CLEAR_COLOR = {0, 170, 0, 255};

    // NOTE: SDL_Windows are not made with default renderers (though they are made with default surfaces).

    // Initialize SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {log_SDL_error("PNG file loader could not initialize!"); abort();}

    // Load a test graphic using the library.
    SDL_Surface * png_img = IMG_Load("resources/pixel-art-ball.png");
    if (!png_img) {log_SDL_error("Test graphic could not be loaded!"); abort();}
    test_image = SDL_CreateTextureFromSurface(drawing_area, png_img);
    SDL_FreeSurface(png_img);
    if (!test_image) { log_SDL_error("Could not convert test image to a texture!"); abort();}

    // Initialize SDL_ttf.
    
}

void shutdown() {
    SDL_DestroyTexture(test_image);
    test_image = nullptr;

    SDL_DestroyRenderer(drawing_area);
    drawing_area = nullptr;

    SDL_DestroyWindow(main_window);
    main_window = nullptr;

    IMG_Quit();
    SDL_Quit();
}

void draw() {
    SDL_SetRenderDrawColor(drawing_area, DEFAULT_CLEAR_COLOR.r, DEFAULT_CLEAR_COLOR.g, DEFAULT_CLEAR_COLOR.b, DEFAULT_CLEAR_COLOR.a);
    SDL_RenderClear(drawing_area);

    // Texture rendering test.
    // SDL_RenderCopy(drawing_area, test_image, nullptr, nullptr); // Draws texture to fill drawing area.

    // Texture rendering test.
    SDL_Rect texture_scaler = {0, 0, 55, 55}; // Draw texture at specified size and location.
    SDL_RenderCopy(drawing_area, test_image, nullptr, &texture_scaler);

    // SDL's built-in line drawing test.
    SDL_SetRenderDrawColor(drawing_area, 0, 0, 0, 255);
    SDL_RenderDrawLine(drawing_area, 60, 0, 69, 1);

    // SDL_gfx line drawing test.
    lineColor(drawing_area, 80, 0, 89, 1, 0xffff0000);
    aalineColor(drawing_area, 100, 0 ,109, 1, 0xffff0000);

    // SDL_gfx circle drawing test.
    circleColor(drawing_area, 60, 50, 0, 0x7f000000);
    circleColor(drawing_area, 70, 50, 1, 0x7f000000);
    circleColor(drawing_area, 80, 50, 2, 0x7f000000);
    circleColor(drawing_area, 90, 50, 3, 0x7f000000);
    circleColor(drawing_area, 100, 50, 4, 0x7f000000);

    // SDL_ttf text and font drawing test.



    SDL_RenderPresent(drawing_area);
}

int main() {
    startup();

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        draw();
    }

    shutdown();
    return 0;
}
