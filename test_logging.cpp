#include "test_logging.h"

#include <iostream>

[[maybe_unused]] void dump_render_info(SDL_Renderer* renderer, const std::string& renderer_name) {

    SDL_RendererInfo renderer_details;
    SDL_GetRendererInfo(renderer, &renderer_details);

    std::cout << renderer_name << std::endl;
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

[[maybe_unused]] void log_status(const std::string& message) {
    std::cout << message << std::endl;
}

[[maybe_unused]] void log_error(const std::string& message) {
    std::cerr << message << std::endl;
}

[[maybe_unused]] void log_SDL2_error(const std::string& message) {
    std::cerr << message << std::endl;
    std::cerr << "SDL2 last reported: " << SDL_GetError() << std::endl;
}