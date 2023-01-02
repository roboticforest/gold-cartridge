#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

SDL_Window* main_window = nullptr;
SDL_Renderer* drawing_area = nullptr;
SDL_Surface* test_image = nullptr;

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
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {log_SDL_error("Audio Playback failed to initialize!"); abort();}
    if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0) {log_SDL_error("Events Polling failed to initialize!"); abort();}
    if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0) {log_SDL_error("Game Controllers failed to initialize!"); abort();}
    if (SDL_InitSubSystem(SDL_INIT_HAPTIC) < 0) {log_SDL_error("Haptic Feedback failed to initialize!"); abort();}
    if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0) {log_SDL_error("Joystick Input failed to initialize!"); abort();}
    if (SDL_InitSubSystem(SDL_INIT_TIMER) < 0) {log_SDL_error("Timers failed to initialize!"); abort();}
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {log_SDL_error("Video failed to initialize!"); abort();}

    main_window = SDL_CreateWindow("Main Window",
                                   SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   WINDOW_WIDTH, WINDOW_HEIGHT,
                                   SDL_WINDOW_SHOWN);
    if (!main_window) { log_SDL_error("Main game window could not be created!"); abort();}

    // drawing_area = SDL_GetRenderer(main_window);
    // dump_render_info(drawing_area, "Default Window Renderer");
    drawing_area = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED);
    //dump_render_info(drawing_area, "New Window Renderer");
    SDL_SetRenderDrawColor(drawing_area, 0, 170, 0, 255);

    // SDL_Windows are not made with default renderers (though they are made with default surfaces).

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {log_SDL_error("PNG file loader could not initialize!"); abort();}
    test_image = IMG_Load("resources/pixel-art-ball.png");
    if (!test_image) {log_SDL_error("Test graphic could not be loaded!"); abort();}
}

void shutdown() {
    SDL_DestroyRenderer(drawing_area);
    drawing_area = nullptr;
    SDL_DestroyWindow(main_window);
    main_window = nullptr;

    IMG_Quit();
    SDL_Quit();
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
        SDL_RenderClear(drawing_area);
        SDL_RenderPresent(drawing_area);
    }

    shutdown();
    return 0;
}
