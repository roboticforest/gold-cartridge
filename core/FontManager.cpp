/**
 * @author David Vitez (AKA: Robotic Forest)
 * @copyright All rights reserved © 2024 David Vitez
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 *          License, v. 2.0. If a copy of the MPL was not distributed with this
 *          file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "FontManager.h"

#include <iostream>

namespace Core {

//    static const std::string DEFAULT_FONT_FILE    = "resources/fonts/playfair-display-font/PlayfairDisplayRegular-ywLOY.ttf";
//    static const int         DEFAULT_FONT_PT_SIZE = 12;
//    static const SDL_Color   DEFAULT_FONT_COLOR{0, 0, 0, 255};
//    static std::unique_ptr<TTF_Font, decltype(TTF_CloseFont)> DEFAULT_FONT();

////////////////////////////////////////////////////////////////////////////////
/// Public API FontManager Functions
////////////////////////////////////////////////////////////////////////////////

    bool FontManager::m_manager_initialized = false;
    bool FontManager::is_initialized() {
        return m_manager_initialized;
    }

    bool FontManager::start_up() {

        static FontManager instance;

        if (!is_initialized()) {
            return m_manager_initialized = true;
        }
    }

    void FontManager::shut_down() {
        if (is_initialized()) {
            m_manager_initialized = false;
        }
    }

////////////////////////////////////////////////////////////////////////////////
/// Private API
////////////////////////////////////////////////////////////////////////////////

    FontManager::FontManager() = default;
    FontManager::~FontManager() { shut_down(); }

} // Core