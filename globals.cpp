/**
 * @author David Vitez (AKA: Robotic Forest)
 * @copyright All rights reserved © 2023 David Vitez
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 *          License, v. 2.0. If a copy of the MPL was not distributed with this
 *          file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "globals.h"

#include "colors.h"

namespace Global {

    // General Application & SDL2 Variables
    // ====================================

    namespace App {
        SDL_Window* MAIN_WINDOW = nullptr;
        const int WINDOW_WIDTH  = 1024;
        const int WINDOW_HEIGHT = 768;

        SDL_Renderer* MAIN_RENDERER = nullptr;
        SDL_Color CLEAR_COLOR = Color::black;

        bool BOILERPLATE_INITIALIZED = false;
        bool QUITTING                = false;
    }

    // SDL Image Test Variables
    // =========================

    const std::string TEST_IMAGE_FILE_PATH = "resources/pixel-art-ball.png";
    SDL_Texture* TEST_IMAGE = nullptr;

    // SDL TTF Test Variables
    // ======================

    TTF_Font* TEST_FONT = nullptr;
    const std::string TEST_FONT_FILE_PATH = "resources/playfair-display-font/PlayfairDisplayRegular-ywLOY.ttf";
    const int         TEST_FONT_SIZE_PTS  = 14;
    SDL_Color         TEST_FONT_COLOR     = {0, 0, 0, 255};

    std::string TEST_SENTENCE = "Cwm fjord bank glyphs vext quiz";
    SDL_Texture* TEXT_RENDER_TEXTURE = nullptr;
    SDL_Rect TEXT_RENDER_LOCATION = {};
}
