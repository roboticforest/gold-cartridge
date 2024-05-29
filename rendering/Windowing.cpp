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

    // Reasonable defaults.

    static const int         defaultWindowWidth  = 1024;
    static const int         defaultWindowHeight = 768;
    static const std::string defaultWindowTitle  = "Gold Cartridge";
    static const SDL_Color   defaultClearColor   = Color::black;

    // Constructors and Destructor.

    Window::Window(int windowWidth, int windowHeight, std::string windowTitle)
            : _windowWidth(windowWidth), _windowHeight(windowHeight), _windowTitle(std::move(windowTitle)) {
        assert(Core::SDL_System::is_initialized());
        _window = SDL_CreateWindow(_windowTitle.c_str(),
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   _windowWidth,
                                   _windowHeight,
                                   SDL_WINDOW_SHOWN);
        assert(_window != nullptr);
        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
        assert(_renderer != nullptr);
        _windowOpen = true;
    }

    Window::Window() : Window(defaultWindowWidth, defaultWindowHeight, defaultWindowTitle) {}

    Window::~Window() {
        if (_renderer) { SDL_DestroyRenderer(_renderer); }
        if (_window) { SDL_DestroyWindow(_window); }
    }

    void Window::set_update_callback(Callback update_fn) {
        _do_user_update = std::move(update_fn);
    }

    void Window::set_draw_callback(Callback draw_fn) {
        _do_user_rendering = std::move(draw_fn);
    }

    void Window::update() {
        // Give users the first shot at consuming events.
        if (_do_user_update)
            _do_user_update();

        // Process all remaining events. This *must* be done somewhere (filters or not) or the window freezes.
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

        if (_do_user_rendering)
            _do_user_rendering();

        SDL_RenderPresent(_renderer);
    }

    void Window::run() {
        auto quitEventFilter = [](void* thisWindow, SDL_Event* event) -> int {
            // Only simple event handling for single window applications. Multiple windows are not currently supported.
            if (event->type == SDL_QUIT) { ((Rendering::Window*)thisWindow)->close(); }
            return 0; // Value will be ignored by SDL.
        };
        SDL_AddEventWatch(quitEventFilter, this);

        while (_windowOpen) {
            update();
            render();
        }
    }

    void Window::close() { _windowOpen = false; }


} // Rendering namespace