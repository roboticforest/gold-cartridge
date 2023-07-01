/**
 * @author David Vitez (AKA: Robotic Forest)
 * @copyright All rights reserved © 2023 David Vitez
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 *          License, v. 2.0. If a copy of the MPL was not distributed with this
 *          file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "globals.h"

// General Application & SDL2 Variables
// ====================================

SDL_Window* MAIN_WINDOW = nullptr;
const int   WINDOW_WIDTH  = 1024;
const int   WINDOW_HEIGHT = 768;

SDL_Renderer* MAIN_RENDERER = nullptr;
SDL_Color     CLEAR_COLOR = {0, 128, 0, 255};

bool QUITTING = false;

SDL_Color white = {255,255,255,255};
SDL_Color button_color = {128, 144, 136, 255};
auto test_button_action = []() -> void {
    static bool green = false;
    if (!green) {
        CLEAR_COLOR = {0, 255, 0, 255};
        green       = true;
    }
    else {
        CLEAR_COLOR = {255, 204, 204, 255};
        green       = false;
    }
};
Button test_button(200, 250, 140, 50,
                   "Test Button!",
                   test_button_action, button_color, white);

Button test_button_2(400, 250, 140, 50,
                     "Pink Button!",
                     test_button_action,
                     {255, 204, 204, 255}, white);

// SDL Image Test Variables
// =========================

const std::string TEST_IMAGE_FILE_PATH = "resources/pixel-art-ball.png";
SDL_Texture*      TEST_IMAGE = nullptr;

// SDL TTF Test Variables
// ======================

TTF_Font*         TEST_FONT = nullptr;
const std::string TEST_FONT_FILE_PATH = "resources/playfair-display-font/PlayfairDisplayRegular-ywLOY.ttf";
const int         TEST_FONT_SIZE_PTS  = 14;
SDL_Color         TEST_FONT_COLOR     = {0, 0, 0, 255};

std::string  TEST_SENTENCE = "Cwm fjord bank glyphs vext quiz";
SDL_Texture* TEXT_RENDER_TEXTURE = nullptr;
SDL_Rect     TEXT_RENDER_LOCATION = {};
