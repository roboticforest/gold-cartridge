/**
 * @author David Vitez (AKA: Robotic Forest)
 * @copyright All rights reserved © 2024 David Vitez
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 *          License, v. 2.0. If a copy of the MPL was not distributed with this
 *          file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "Windowing.h"
#include "../core/SDL_System.h"
#include "Colors.h"

#include <cassert>
#include <SDL_video.h>
#include <SDL_render.h>
#include <SDL_events.h>

namespace Rendering {

    // Reasonable window display defaults.

    static const int         defaultWindowWidth  = 1024;
    static const int         defaultWindowHeight = 768;
    static const std::string defaultWindowTitle  = "Gold Cartridge";
    static const SDL_Color   defaultClearColor   = Color::black();

    // Window constructors and destructors.

    Window::Window(int windowWidth, int windowHeight, std::string windowTitle)
            : _windowWidth(windowWidth), _windowHeight(windowHeight), _windowTitle(std::move(windowTitle)) {

        assert(Core::SDL_System::is_initialized());
        _window = SDL_CreateWindow(_windowTitle.c_str(),
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   _windowWidth,
                                   _windowHeight,
                                   SDL_WINDOW_SHOWN);

        assert(_window != nullptr);
        const int firstValidDriver = -1;
        _renderer = SDL_CreateRenderer(_window, firstValidDriver, SDL_RENDERER_ACCELERATED);

        assert(_renderer != nullptr);
        _windowOpen = true;
    }

    Window::Window() : Window(defaultWindowWidth, defaultWindowHeight, defaultWindowTitle) {}

    Window::~Window() {
        if (_renderer) { SDL_DestroyRenderer(_renderer); }
        if (_window) { SDL_DestroyWindow(_window); }
    }

    // Public API functions and helpers.

    void Window::set_update_callback(Callback update_fn) { _process_user_updates = std::move(update_fn); }

    void Window::set_draw_callback(Callback draw_fn) { _process_user_rendering = std::move(draw_fn); }

    static void start_watch_for_window_close(Rendering::Window* window) {
        // NOTE: Multiple open windows are not supported by this code. SDL2
        // generates SDL_QUIT events when "the last" (or only) window is closed
        // vs when multiple windows are open, and that's not accounted for here
        // yet.

        // NOTE: An event filter allows us to handle quit events both before
        // framework users and without interfering with their event handling
        // code.
        auto quitEventFilter = [](void* window, SDL_Event* event) -> int {
            if (event->type == SDL_QUIT) { static_cast<Rendering::Window*>(window)->close(); }
            return 0; // Value will be ignored by SDL2.
        };
        SDL_AddEventWatch(quitEventFilter, window);
    }

    void Window::run() {

        start_watch_for_window_close(this);
        while (_windowOpen) {
            this->update();
            this->render();
        }
    }

    void Window::close() { _windowOpen = false; }

    // Private API functions and helpers.

    void Window::update() {
        // Give users the first shot at consuming events.
        if (_process_user_updates) { _process_user_updates(); }

        // Processing SDL2's event queue *MUST* be done somewhere or the
        // window freezes, even if the events are just thrown away. SDL event
        // filters don't count, and users might not create their own event
        // processing loop.
        SDL_Event currentEvent;
        while (SDL_PollEvent(&currentEvent)) {}
    }

    void Window::render() {
        SDL_SetRenderDrawColor(_renderer,
                               defaultClearColor.r,
                               defaultClearColor.g,
                               defaultClearColor.b,
                               defaultClearColor.a);
        SDL_RenderClear(_renderer);

        if (_process_user_rendering) { _process_user_rendering(); }

        SDL_RenderPresent(_renderer);
    }

} // Rendering namespace