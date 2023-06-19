#ifndef GOLD_CARTRIDGE_GLOBALS_CPP
#define GOLD_CARTRIDGE_GLOBALS_CPP

#include "globals.h"

// General and SDL2 base.

SDL_Window* MAIN_WINDOW = nullptr;
const int   WINDOW_WIDTH  = 1024;
const int   WINDOW_HEIGHT = 768;

SDL_Renderer* MAIN_RENDERER = nullptr;
SDL_Color     CLEAR_COLOR = {0, 128, 0, 255};

bool QUITTING = false;

Button test_button(200, 250,
                   140, 50,
                   "Test Button!",
                   []() -> void {
    static bool green = false;
    if (!green) {
        CLEAR_COLOR = {0, 255, 0, 255};
        green       = true;
    }
    else {
        CLEAR_COLOR = {255, 204, 204, 255};
        green       = false;
    }
});

// SDL2_image.

const std::string TEST_IMAGE_FILE_PATH = "resources/pixel-art-ball.png";
SDL_Texture*      TEST_IMAGE = nullptr;

// SDL2_ttf

TTF_Font*         TEST_FONT = nullptr;
const std::string TEST_FONT_FILE_PATH = "resources/playfair-display-font/PlayfairDisplayRegular-ywLOY.ttf";
const int         TEST_FONT_SIZE_PTS  = 14;
SDL_Color         TEST_FONT_COLOR     = {0, 0, 0, 255};

std::string  TEST_SENTENCE = "Cwm fjord bank glyphs vext quiz";
SDL_Texture* TEXT_RENDER_TEXTURE = nullptr;
SDL_Rect     TEXT_RENDER_LOCATION = {};

#endif //GOLD_CARTRIDGE_GLOBALS_CPP
