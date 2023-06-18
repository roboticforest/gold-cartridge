#ifndef GOLD_CARTRIDGE_TEST_LOGGING_H
#define GOLD_CARTRIDGE_TEST_LOGGING_H

#include <string>
#include <SDL.h>

[[maybe_unused]] void log_error(const std::string& message);

[[maybe_unused]] void dump_render_info(SDL_Renderer* sdl_renderer, const std::string& label);

#endif //GOLD_CARTRIDGE_TEST_LOGGING_H
