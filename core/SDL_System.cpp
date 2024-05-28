/**
 * @author David Vitez (AKA: Robotic Forest)
 * @copyright All rights reserved © 2024 David Vitez
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 *          License, v. 2.0. If a copy of the MPL was not distributed with this
 *          file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "SDL_System.h"

#include <iostream>
#include <functional>
#include <optional>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

namespace Core {

    // Helper logging functions.

    static void log_status(const std::string& message) {
        std::cout << message << std::endl;
    }

    static void log_error(const std::string& message) {
        std::cerr << message << std::endl;
        std::cerr << "SDL2 last reported: " << SDL_GetError() << std::endl;
    }

    static void assert_task(const std::function<bool()>& task,
                            const std::optional<std::string>& start_message,
                            const std::optional<std::string>& failure_message) {
        if (start_message) {
            log_status(*start_message);
        }
        if (!task()) {
            if (failure_message) {
                log_error(*failure_message);
            }
            abort();
        }
    }

    // SDL_System functions.

    bool Core::SDL_System::library_initialized = false;

    Core::SDL_System& Core::SDL_System::instance() {
        static SDL_System instance;
        Core::SDL_System::library_initialized = true;
        return instance;
    }

    bool Core::SDL_System::startup() {

        // Initialize core SDL subsystems.
        assert_task([]() { return SDL_InitSubSystem(SDL_INIT_VIDEO) == 0; },
                    "Starting SDL2's Video subsystem...",
                    "Video failed to initialize!");

        assert_task([]() -> bool { return SDL_InitSubSystem(SDL_INIT_AUDIO) == 0; },
                    "Starting SDL2's Audio subsystem...",
                    "Audio playback failed to initialize!");

        assert_task([]() { return SDL_InitSubSystem(SDL_INIT_EVENTS) == 0; },
                    "Starting SDL2's Event handling subsystem...",
                    "Event handling failed to initialize!");

        assert_task([]() { return SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) == 0; },
                    "Starting SDL2's Gamepad and Joystick Input subsystems...",
                    "Game Controller Input handling failed to initialize!");

        assert_task([]() { return SDL_InitSubSystem(SDL_INIT_HAPTIC) == 0; },
                    "Starting SDL2's Haptic Feedback subsystem...",
                    "Haptic Feedback failed to initialize!");

        assert_task([]() { return SDL_InitSubSystem(SDL_INIT_TIMER) == 0; },
                    "Starting SDL2's Timer subsystem...",
                    "Timers failed to initialize!");

        // Initialize SDL_image optional subsystem.
        assert_task([]() { return ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)); },
                    "Configuring SDL_image for PNG file loading...",
                    "PNG file loader could not be initialized!"
        );

        // Initialize SDL_ttf optional subsystem.
        assert_task([]() { return TTF_Init() == 0; },
                    "Initializing SDL_ttf...",
                    "SDL True Type Font loader failed to initialize!");

        return true;

    }

    void Core::SDL_System::shutdown() {
        SDL_Quit();
    }

    Core::SDL_System::SDL_System() = default;

    Core::SDL_System::~SDL_System() {
        this->shutdown();
    }

    bool SDL_System::is_initialized() {
        return Core::SDL_System::library_initialized;
    }

} // Core namespace.