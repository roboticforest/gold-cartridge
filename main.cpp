/**
 * @author David Vitez (AKA: Robotic Forest)
 * @copyright All rights reserved © 2023 David Vitez
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 *          License, v. 2.0. If a copy of the MPL was not distributed with this
 *          file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <SDL.h> // Core SDL2 features.

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
                    QUITTING = true;
                    break;
                }
            }
        }
    }

    void update_data() {
        // UPDATE YOUR DATA AND OBJECTS HERE.
    }

    void draw_scene() {
        SDL_SetRenderDrawColor(MAIN_RENDERER, CLEAR_COLOR.r, CLEAR_COLOR.g, CLEAR_COLOR.b, CLEAR_COLOR.a);
        SDL_RenderClear(MAIN_RENDERER);

        // PUT YOUR DRAWING CODE HERE.

        SDL_RenderPresent(MAIN_RENDERER);
    }
}

int main(int num_args, char** args) {
    (void) num_args; // Ignored.
    (void) args;     // Ignored.
    initialize_boilerplate();

    // DELETE, OR COMMENT OUT, THIS CALL TO app.run() TO RUN YOUR CODE INSTEAD.
    TestApplication app;
    app.run();

    // PUT YOUR CODE INTO THESE FUNCTIONS.
    while (!QUITTING) {
        USER::handle_input();
        USER::update_data();
        USER::draw_scene();
    }

    shutdown();
    return 0;
}