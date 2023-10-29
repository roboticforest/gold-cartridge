/**
 * @author David Vitez (AKA: Robotic Forest)
 * @copyright All rights reserved © 2023 David Vitez
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 *          License, v. 2.0. If a copy of the MPL was not distributed with this
 *          file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "test_application.h"

#include <SDL.h>

#include "sdl2_loading.h"
#include "globals.h"
#include "colors.h"

/**
 * @brief A shorter, easier to use wrapper of SDL's official SetRenderDrawColor. Sets the color used for drawing
 * operations (Rect, Line and Clear).
 * @param renderer The renderer for which drawing color should be set.
 * @param draw_color The color used to draw on the rendering target.
 * @return 0 on success, or -1 on error.
 */
int SDL_SetRenderDrawColor(SDL_Renderer* renderer, const SDL_Color& draw_color) {
    return SDL_SetRenderDrawColor(renderer, draw_color.r, draw_color.g, draw_color.b, draw_color.a);
}

TestApplication::TestApplication() {
    Global::App::CLEAR_COLOR = Color::green;

    button_action = []() -> void {
        static bool color_changed = false;
        static SDL_Color original_color = Global::App::CLEAR_COLOR;
        if (color_changed) {
            Global::App::CLEAR_COLOR = original_color;
        } else {
            Global::App::CLEAR_COLOR = Color::lightBlue;
        }

    };

    this->test_button   = std::make_unique<Button>(
            Button(200, 250, 140, 50, "Test Button!", button_action, {128, 144, 136, 255}, Color::white));
    this->test_button_2 = std::make_unique<Button>(
            Button(350, 250, 140, 50, "Button 2!", button_action, Color::lightGray, Color::white));
}

void TestApplication::input() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT: {
                Global::App::QUITTING = true;
                break;
            }
            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP: {
                test_button->handle_event(e);
                test_button_2->handle_event(e);
                break;
            }
        }
    }
}

void TestApplication::update() {

}

/**
 * Draws all tests to the screen.
 */
void TestApplication::draw() {
    SDL_SetRenderDrawColor(Global::App::MAIN_RENDERER, Global::App::CLEAR_COLOR);
    SDL_RenderClear(Global::App::MAIN_RENDERER);

    // Texture rendering test.
    // SDL_RenderCopy(MAIN_RENDERER, TEST_IMAGE, nullptr, nullptr); // Draws texture to fill drawing area.
    SDL_Rect texture_scaler = {0, 0, 55, 55}; // Draw texture at specified size and location.
    SDL_RenderCopy(Global::App::MAIN_RENDERER, Global::TEST_IMAGE, nullptr, &texture_scaler);

    // SDL's built-in line drawing test.
    SDL_SetRenderDrawColor(Global::App::MAIN_RENDERER, 0, 0, 0, 255);
    SDL_RenderDrawLine(Global::App::MAIN_RENDERER, 60, 0, 69, 1);

    // SDL_ttf text and font drawing test.
    SDL_RenderCopy(Global::App::MAIN_RENDERER, Global::TEXT_RENDER_TEXTURE, nullptr, &Global::TEXT_RENDER_LOCATION);

    test_button->draw();
    test_button_2->draw();

    // Show the final rendering.
    SDL_RenderPresent(Global::App::MAIN_RENDERER);
}

int TestApplication::run() {

    if (!Global::App::BOILERPLATE_INITIALIZED) { initialize_boilerplate(); }

    while (!Global::App::QUITTING) {
        input();
        update();
        draw();
    }

    shutdown();
    return 0;
}

