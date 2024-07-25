/**
 * @author David Vitez (AKA: Robotic Forest)
 * @copyright All rights reserved © 2024 David Vitez
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 *          License, v. 2.0. If a copy of the MPL was not distributed with this
 *          file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef GOLD_CARTRIDGE_WINDOWING_H
#define GOLD_CARTRIDGE_WINDOWING_H

#include <functional>
#include <string>
#include <chrono>

struct SDL_Window;
struct SDL_Renderer;

namespace Rendering {

    using UpdateCallback = std::function<void()>;
    using DrawCallback = std::function<void(SDL_Renderer* renderer)>;
    using Milliseconds = std::chrono::duration<double, std::milli>;

    class Window {
    public:
        Window();
        Window(int windowWidth, int windowHeight, std::string windowTitle);
        ~Window();

        void set_user_update_callback(UpdateCallback update_fn);
        void set_user_draw_callback(DrawCallback draw_fn);

        int max_updates_per_frame() const;
        void max_updates_per_frame(int new_update_limit);
        double update_interval_ms() const;
        void update_interval_ms(double new_ms_interval);

        void run();
        void close();

    private:
        void update();
        void render();

    private:
        SDL_Renderer* _renderer;
        SDL_Window  * _window;
        int         _windowWidth;
        int         _windowHeight;
        std::string _windowTitle;
        bool        _windowOpen;

        int            _max_updates_per_frame;
        Milliseconds   _update_interval_ms;
        UpdateCallback _process_user_updates;
        DrawCallback   _process_user_rendering;
    };

} // Rendering namespace

#endif //GOLD_CARTRIDGE_WINDOWING_H
