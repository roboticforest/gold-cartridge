/**
 * @author David Vitez (AKA: Robotic Forest)
 * @copyright All rights reserved © 2023 David Vitez
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 *          License, v. 2.0. If a copy of the MPL was not distributed with this
 *          file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef GOLD_CARTRIDGE_GLOBALS_H
#define GOLD_CARTRIDGE_GLOBALS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

namespace Global {
    // General Application & SDL2 Variables
    // ====================================

    namespace App {

    }

    // SDL Image Test Variables
    // =========================

    extern const std::string TEST_IMAGE_FILE_PATH;
    extern SDL_Texture*      TEST_IMAGE;

    // SDL TTF Test Variables
    // ======================

    // Font, Size, and Color.
    extern TTF_Font*         TEST_FONT;
    extern const std::string TEST_FONT_FILE_PATH;
    extern const int         TEST_FONT_SIZE_PTS;
    extern SDL_Color         TEST_FONT_COLOR;

    // Word/Sentence Rendering
    extern std::string  TEST_SENTENCE;
    extern SDL_Texture* TEXT_RENDER_TEXTURE;
    extern SDL_Rect     TEXT_RENDER_LOCATION;
}

#endif //GOLD_CARTRIDGE_GLOBALS_H
