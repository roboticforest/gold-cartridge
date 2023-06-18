#include "test_logging.h"

#include <iostream>

/**
 * A utility function for logging a more meaningful error message ahead of SDL's built-in error descriptions.
 * @param message A short description of program error that occurred.
 */
void log_error(const std::string &message) {
    std::cerr << message << std::endl;
    std::cerr << "SDL2 last reported: " << SDL_GetError() << std::endl;
}

/**
 * Dumps information about the given renderer to the console for debugging purposes.
 * @param sdl_renderer The renderer to extract properties from.
 * @param label A short human-readable description of the render.
 */
[[maybe_unused]] void dump_render_info(SDL_Renderer *sdl_renderer, const std::string &label) {

    SDL_RendererInfo renderer_details;
    SDL_GetRendererInfo(sdl_renderer, &renderer_details);

    std::cout << label << std::endl;
    std::cout << "Renderer Details:" << std::endl;
    std::cout << "Name: " << renderer_details.name << std::endl;
    std::cout << "Max Width: " << renderer_details.max_texture_width << std::endl;
    std::cout << "Max Height: " << renderer_details.max_texture_height << std::endl;
    std::cout << "Texture Fmt Cnt: " << renderer_details.num_texture_formats << std::endl;
    std::cout << "SDL_RENDERER_SOFTWARE:      " << ((renderer_details.flags & SDL_RENDERER_SOFTWARE) > 0) << std::endl;
    std::cout << "SDL_RENDERER_ACCELERATED:   " << ((renderer_details.flags & SDL_RENDERER_ACCELERATED) > 0) << std::endl;
    std::cout << "SDL_RENDERER_PRESENTVSYNC:  " << ((renderer_details.flags & SDL_RENDERER_PRESENTVSYNC) > 0) << std::endl;
    std::cout << "SDL_RENDERER_TARGETTEXTURE: " << ((renderer_details.flags & SDL_RENDERER_TARGETTEXTURE) > 0) << std::endl;
}