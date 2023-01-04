#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

SDL_Window* main_window = nullptr;
SDL_Renderer* drawing_area = nullptr;
SDL_Texture* test_image = nullptr;
TTF_Font * main_font = nullptr;
SDL_Texture * text_texture = nullptr;

SDL_Color CLEAR_COLOR = {0, 128, 0, 255};
SDL_Color TEXT_COLOR = {0, 0, 0, 255};
SDL_Rect TEXT_AREA = {0, 0, 0, 0};

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

    // NOTE: SDL_Windows are not made with default renderers (though they are made with default surfaces).

    // NOTE: SDL_gfx does not need to be initialized. It is ready when SDL is ready.

    // Initialize SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {log_SDL_error("PNG file loader could not initialize!"); abort();}

    // Load a test graphic using the library.
    SDL_Surface * png_img = IMG_Load("resources/pixel-art-ball.png");
    if (!png_img) {log_SDL_error("Test graphic could not be loaded!"); abort();}
    test_image = SDL_CreateTextureFromSurface(drawing_area, png_img);
    SDL_FreeSurface(png_img);
    if (!test_image) { log_SDL_error("Could not convert test image to a texture!"); abort();}

    // Initialize SDL_ttf.
    TTF_Init();
    if (!TTF_WasInit()) {log_SDL_error("SDL True Type Font library failed to initialize!"); abort();}
    main_font = TTF_OpenFont("resources/playfair-display-font/PlayfairDisplayRegular-ywLOY.ttf", 14);
    if(!main_font){ log_SDL_error("The main font failed to load!"); abort();}

    SDL_Surface * text_render = TTF_RenderText_Solid(main_font, "Cwm fjord bank glyphs vext quiz", TEXT_COLOR);
    if (!text_render){ log_SDL_error("Rendering of sample text failed."); abort();}
    TEXT_AREA = {0, 100, text_render->w, text_render->h};

    text_texture = SDL_CreateTextureFromSurface(drawing_area, text_render);
    if (!text_texture) { log_SDL_error("Conversion of text surface to texture failed."); abort();}

    SDL_FreeSurface(text_render);
    text_render = nullptr;

}

void shutdown() {
    SDL_DestroyTexture(test_image);
    test_image = nullptr;

    SDL_DestroyRenderer(drawing_area);
    drawing_area = nullptr;

    SDL_DestroyWindow(main_window);
    main_window = nullptr;

    TTF_CloseFont(main_font);
    main_font = nullptr;
    SDL_DestroyTexture(text_texture);

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void draw() {
    SDL_SetRenderDrawColor(drawing_area, CLEAR_COLOR.r, CLEAR_COLOR.g, CLEAR_COLOR.b, CLEAR_COLOR.a);
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
    SDL_RenderCopy(drawing_area, text_texture, nullptr, &TEXT_AREA);

    // Show the final rendering.
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
