#ifndef GOLD_CARTRIDGE_TEST_LOGGING_H
#define GOLD_CARTRIDGE_TEST_LOGGING_H

#include <SDL.h>

#include <string>

/**
 * Dumps information about the given renderer to the console for debugging purposes.
 * @param renderer The renderer to extract properties from.
 * @param renderer_name A short meaningful label for the render. For example: "Main Renderer" or "Texture Render".
 */
[[maybe_unused]] void dump_render_info(SDL_Renderer* renderer, const std::string& renderer_name);

/**
 * Logs a general status/info/progress message.
 * @param message A short (typically one line) note to record.
 */
[[maybe_unused]] void log_status(const std::string& message);

/**
 * Logs a program error message. Note, if the error is related in anyway to the SDL2 library, you should use
 * log_SDL2_error() which will record some additional information polled from SDL2 as well.
 * @param message A short (typically one line) description of the issue.
 */
[[maybe_unused]] void log_error(const std::string& message);

/**
 * A utility function for logging a more meaningful error message ahead of SDL's built-in error descriptions.
 * @param message A short description of program error that occurred.
 */
[[maybe_unused]] void log_SDL2_error(const std::string& message);

#endif //GOLD_CARTRIDGE_TEST_LOGGING_H
