/**
 * @author David Vitez (AKA: Robotic Forest)
 * @copyright All rights reserved © 2023 David Vitez
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 *          License, v. 2.0. If a copy of the MPL was not distributed with this
 *          file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "core/SDL_System.h"
#include "rendering/Windowing.h"

int main(int num_args, char** args) {
    (void)num_args; // Ignored.
    (void)args;     // Ignored.
    Core::SDL_System::instance().startup();

    Rendering::Window mainWindow;
    mainWindow.set_user_update_callback([]() {
        // Your update code here...
    });

    mainWindow.set_user_draw_callback([]() {
        // Your graphics rendering code here...
    });

    mainWindow.run();

    Core::SDL_System::instance().shutdown();
    return 0;
}