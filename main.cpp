/**
 * @author David Vitez (AKA: Robotic Forest)
 * @copyright All rights reserved © 2023 David Vitez
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 *          License, v. 2.0. If a copy of the MPL was not distributed with this
 *          file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <SDL.h> // SDLCore SDL2 features.

#include "core/SDL_System.h"

#include "sdl2_loading.h" // Boilerplate functions.
#include "globals.h"      // Boilerplate data.

#include "test_application.h" // The SDL2 tester app.

namespace USER {

    namespace DATA {
        // PUT YOUR DATA AND OTHER OBJECTS HERE (IF YOU WANT).
    }

    void handle_input() {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            // ADD MORE CASES TO HANDLE USER INPUT AND OTHER SDL EVENTS.
            switch (e.type) {
                case SDL_QUIT: {
                    Global::App::QUITTING = true;
                    break;
                }
            }
        }
    }

    void update_data() {
        // UPDATE YOUR DATA AND OBJECTS HERE.
    }

    void draw_scene() {
        SDL_SetRenderDrawColor(Global::App::MAIN_RENDERER,
                               Global::App::CLEAR_COLOR.r,
                               Global::App::CLEAR_COLOR.g,
                               Global::App::CLEAR_COLOR.b,
                               Global::App::CLEAR_COLOR.a);
        SDL_RenderClear(Global::App::MAIN_RENDERER);

        // PUT YOUR DRAWING CODE HERE.

        SDL_RenderPresent(Global::App::MAIN_RENDERER);
    }
}

int main(int num_args, char** args) {
    (void) num_args; // Ignored.
    (void) args;     // Ignored.
    Core::SDL_System::instance().startup();
    initialize_boilerplate();

    // DELETE, OR COMMENT OUT, THIS CALL TO app.run() TO RUN YOUR CODE INSTEAD.
    TestApplication app;
    app.run();

    // PUT YOUR CODE INTO THESE FUNCTIONS.
    while (!Global::App::QUITTING) {
        USER::handle_input();
        USER::update_data();
        USER::draw_scene();
    }

    shutdown();
    return 0;
}