/**
 * @author David Vitez (AKA: Robotic Forest)
 * @copyright All rights reserved © 2024 David Vitez
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 *          License, v. 2.0. If a copy of the MPL was not distributed with this
 *          file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "SDL_System.h"

#include <functional>
#include <iostream>
#include <memory>
#include <optional>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

namespace Core {

////////////////////////////////////////////////////////////////////////////////
/// Helper logging functions.
////////////////////////////////////////////////////////////////////////////////

    static void LOG_STATUS(const std::string& message) {
        std::cout << message << std::endl;
    }

    static void LOG_ERROR(const std::string& message) {
        std::cerr << message << std::endl;
        std::cerr << "SDL2 last reported: " << SDL_GetError() << std::endl;
    }

    static void ASSERT_TASK(const std::function<bool()>& task,
                            const std::optional<std::string>& start_message,
                            const std::optional<std::string>& failure_message) {
        if (start_message) {
            LOG_STATUS(*start_message);
        }
        if (!task()) {
            if (failure_message) {
                LOG_ERROR(*failure_message);
            }
            abort();
        }
    }

////////////////////////////////////////////////////////////////////////////////
/// Public API SDL_System functions.
////////////////////////////////////////////////////////////////////////////////

    bool SDL_System::m_library_initialized = false;
    bool SDL_System::is_initialized() {
        return m_library_initialized;
    }

    bool SDL_System::start_up() {

        static SDL_System instance;

        if (!is_initialized()) {
            // Initialize all core SDL subsystems.
            ASSERT_TASK([]() { return SDL_InitSubSystem(SDL_INIT_VIDEO) == 0; },
                        "Starting SDL2's Video subsystem...",
                        "Video failed to initialize!");

            ASSERT_TASK([]() -> bool { return SDL_InitSubSystem(SDL_INIT_AUDIO) == 0; },
                        "Starting SDL2's Audio subsystem...",
                        "Audio playback failed to initialize!");

            ASSERT_TASK([]() { return SDL_InitSubSystem(SDL_INIT_EVENTS) == 0; },
                        "Starting SDL2's Event handling subsystem...",
                        "Event handling failed to initialize!");

            ASSERT_TASK([]() { return SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) == 0; },
                        "Starting SDL2's Gamepad and Joystick Input subsystems...",
                        "Game Controller Input handling failed to initialize!");

            ASSERT_TASK([]() { return SDL_InitSubSystem(SDL_INIT_HAPTIC) == 0; },
                        "Starting SDL2's Haptic Feedback subsystem...",
                        "Haptic Feedback failed to initialize!");

            ASSERT_TASK([]() { return SDL_InitSubSystem(SDL_INIT_TIMER) == 0; },
                        "Starting SDL2's Timer subsystem...",
                        "Timers failed to initialize!");

            // Initialize SDL_image optional subsystem.
            ASSERT_TASK([]() { return ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)); },
                        "Configuring SDL_image for PNG file loading...",
                        "PNG file loader could not be initialized!"
            );

            // Initialize SDL_ttf optional subsystem.
            ASSERT_TASK([]() { return TTF_Init() == 0; },
                        "Initializing SDL_ttf...",
                        "SDL True Type Font loader failed to initialize!");


        }
        return m_library_initialized = true;
    }

    void SDL_System::shut_down() {
        LOG_STATUS("Shutting down the SDL_ttf...");
        TTF_Quit();

        LOG_STATUS("Shutting down the SDL_image...");
        IMG_Quit();

        LOG_STATUS("Shutting down the SDL2 library...");
        SDL_Quit();

        m_library_initialized = false;
    }

////////////////////////////////////////////////////////////////////////////////
/// Private API
////////////////////////////////////////////////////////////////////////////////

    SDL_System::SDL_System() = default;
    SDL_System::~SDL_System() { shut_down(); }

} // Core namespace.