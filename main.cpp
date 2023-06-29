#include <SDL.h>

#include "sdl2_testing.h"
#include "globals.h"

void input() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT: {
                QUITTING = true;
                break;
            }
            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:test_button.handle_event(e);
                break;
        }
    }
}

void update() {

}

/**
 * Draws all tests to the screen.
 */
void draw() {
    SDL_SetRenderDrawColor(MAIN_RENDERER, CLEAR_COLOR.r, CLEAR_COLOR.g, CLEAR_COLOR.b, CLEAR_COLOR.a);
    SDL_RenderClear(MAIN_RENDERER);

    // Texture rendering test.
    // SDL_RenderCopy(MAIN_RENDERER, TEST_IMAGE, nullptr, nullptr); // Draws texture to fill drawing area.
    SDL_Rect texture_scaler = {0, 0, 55, 55}; // Draw texture at specified size and location.
    SDL_RenderCopy(MAIN_RENDERER, TEST_IMAGE, nullptr, &texture_scaler);

    // SDL's built-in line drawing test.
    SDL_SetRenderDrawColor(MAIN_RENDERER, 0, 0, 0, 255);
    SDL_RenderDrawLine(MAIN_RENDERER, 60, 0, 69, 1);

    // SDL_ttf text and font drawing test.
    SDL_RenderCopy(MAIN_RENDERER, TEXT_RENDER_TEXTURE, nullptr, &TEXT_RENDER_LOCATION);

    test_button.draw();

    // Show the final rendering.
    SDL_RenderPresent(MAIN_RENDERER);
}

int main(int num_args, char** args) {
    (void) num_args; // Ignored.
    (void) args;     // Ignored.

    initialize_everything();

    while (!QUITTING) {
        input();
        update();
        draw();
    }

    shutdown();
    return 0;
}
