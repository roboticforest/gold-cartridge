#ifndef GOLD_CARTRIDGE_GLOBALS_H
#define GOLD_CARTRIDGE_GLOBALS_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "button.h"

// General variables and items dependant only on SDL2.

extern SDL_Window* MAIN_WINDOW;
extern const int   WINDOW_WIDTH;
extern const int   WINDOW_HEIGHT;

extern SDL_Renderer* MAIN_RENDERER;
extern SDL_Color     CLEAR_COLOR;

extern bool QUITTING;

extern Button test_button;

// Variables used to test SDL2_image.
// Note, these data types aren't necessarily provided by SDL_image, just used to test it.

extern const std::string TEST_IMAGE_FILE_PATH;
extern SDL_Texture* TEST_IMAGE;

// Variables used to test SDL2_ttf.
// Note, not all the following data types were provided by SDL_ttf, just used to test the library.

extern TTF_Font*         TEST_FONT;
extern const std::string TEST_FONT_FILE_PATH;
extern const int         TEST_FONT_SIZE_PTS;
extern SDL_Color         TEST_FONT_COLOR;

extern std::string  TEST_SENTENCE;
extern SDL_Texture* TEXT_RENDER_TEXTURE;
extern SDL_Rect     TEXT_RENDER_LOCATION;

#endif //GOLD_CARTRIDGE_GLOBALS_H
