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

struct SDL_Window;
struct SDL_Renderer;

namespace Rendering {

    using Callback = std::function<void()>;

    class Window {
    public:
        Window();
        Window(int windowWidth, int windowHeight, std::string windowTitle);
        ~Window();

        void set_update_callback(Callback update_fn);
        void set_draw_callback(Callback draw_fn);
        void run();
        void close();

    private:

        void update();
        void render();

        SDL_Renderer* _renderer;
        SDL_Window  * _window;
        int         _windowWidth;
        int         _windowHeight;
        std::string _windowTitle;

        Callback _do_user_update;
        Callback _do_user_rendering;
        bool     _windowOpen;
    };

} // Rendering namespace

#endif //GOLD_CARTRIDGE_WINDOWING_H
