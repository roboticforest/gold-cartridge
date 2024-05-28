/**
 * @author David Vitez (AKA: Robotic Forest)
 * @copyright All rights reserved © 2023 David Vitez
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 *          License, v. 2.0. If a copy of the MPL was not distributed with this
 *          file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "sdl2_loading.h"

#include "globals.h"
#include "test_asserts.h"
#include "test_logging.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>
#include <cassert>

/**
 * Initialize all of SDL's core subsystems, logging any errors and terminating the program if they occur.
 */
void prep_SDL2() {

}

/**
 * Create the application's main _window, terminating the application if one can not be made.
 */
void prep_window() {



}

/**
 * Create the application's primary drawing context, terminating the application if that fails.
 */
void prep_renderer() {



}

/**
 * Initialize the SDL_image library to load desired image formats.
 */
void prep_SDL_image() {

}

/**
 * Use SDL_image to load a test graphic.
 */
void load_test_graphic() {
    SDL_Surface* png_img = IMG_Load(Global::TEST_IMAGE_FILE_PATH.c_str());

    if (!png_img) {
        std::cerr << "The test image \"" + Global::TEST_IMAGE_FILE_PATH + "\" could not be loaded." << std::endl;
        std::cerr << SDL_GetError() << std::endl;
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "Image Not Found",
                                 "Test graphic could not be loaded! See log for more details.",
                                 Global::App::MAIN_WINDOW);
    }
    else {
        Global::TEST_IMAGE = SDL_CreateTextureFromSurface(Global::App::MAIN_RENDERER, png_img);
    }

    if (!Global::TEST_IMAGE) {

        Global::TEST_IMAGE = SDL_CreateTexture(Global::App::MAIN_RENDERER,
                                               SDL_PIXELFORMAT_RGBA32,
                                               SDL_TEXTUREACCESS_TARGET,
                                               64,
                                               64);
        assert(Global::TEST_IMAGE != nullptr);
        SDL_Rect square = {0, 0, 64, 64};
        SDL_SetRenderTarget(Global::App::MAIN_RENDERER, Global::TEST_IMAGE);
        SDL_SetRenderDrawColor(Global::App::MAIN_RENDERER, 255, 0, 0, 255);
        SDL_RenderFillRect(Global::App::MAIN_RENDERER, &square);
        SDL_SetRenderTarget(Global::App::MAIN_RENDERER, nullptr);
    }
    SDL_FreeSurface(png_img);
}

/**
 * Initialize the SDL_ttf library.
 */
void prep_SDL_ttf() {

}

/**
 * Use SDL_ttf to load a test font. Currently, this font is the default used all throughout other tests. This needs to
 * be repurposed for more general usage.
 */
void load_test_font() {
    Global::TEST_FONT = TTF_OpenFont(Global::TEST_FONT_FILE_PATH.c_str(), Global::TEST_FONT_SIZE_PTS);
    assert(Global::TEST_FONT != nullptr);
}

/**
 * Renders a test sentence to a texture for later rendering to the screen.
 */
void prep_test_text_render() {

    SDL_Surface* text_render_surface = nullptr;

    text_render_surface = TTF_RenderText_Blended(Global::TEST_FONT,
                                                 Global::TEST_SENTENCE.c_str(),
                                                 Global::TEST_FONT_COLOR);
    assert(text_render_surface != nullptr);


    Global::TEXT_RENDER_TEXTURE = SDL_CreateTextureFromSurface(Global::App::MAIN_RENDERER, text_render_surface);
    assert(Global::TEXT_RENDER_TEXTURE != nullptr);


    Global::TEXT_RENDER_LOCATION.w = text_render_surface->w;
    Global::TEXT_RENDER_LOCATION.h = text_render_surface->h;

    SDL_FreeSurface(text_render_surface);
    text_render_surface = nullptr;
}

/**
 * Initialize the entire application along with all SDL subsystems and extension libraries.
 */
void initialize_boilerplate() {
    prep_SDL2();
    prep_SDL_image();
    prep_SDL_ttf();

    prep_window();
    prep_renderer();

    load_test_graphic();
    load_test_font();
    prep_test_text_render();

    Global::App::BOILERPLATE_INITIALIZED = true;
    std::cout << "Initialization complete!" << std::endl;
}

/**
 * Deletes all dynamically allocated global resources and shuts down all libraries and SDL2 subsystems.
 */
void shutdown() {
    std::cout << "Shutting down the application..." << std::endl;

    std::cout << "Destroying the Test Image texture..." << std::endl;
    SDL_DestroyTexture(Global::TEST_IMAGE);
    Global::TEST_IMAGE = nullptr;

    std::cout << "Cleaning up the test font resources..." << std::endl;
    TTF_CloseFont(Global::TEST_FONT);
    Global::TEST_FONT = nullptr;
    std::cout << "Destroying the Text Rendering texture..." << std::endl;
    SDL_DestroyTexture(Global::TEXT_RENDER_TEXTURE);
    Global::TEXT_RENDER_TEXTURE = nullptr;

    std::cout << "Destroying the Main Renderer..." << std::endl;
    SDL_DestroyRenderer(Global::App::MAIN_RENDERER);
    Global::App::MAIN_RENDERER = nullptr;

    std::cout << "Destroying the Main Application Window..." << std::endl;
    SDL_DestroyWindow(Global::App::MAIN_WINDOW);
    Global::App::MAIN_WINDOW = nullptr;

    std::cout << "Shutting down SDL_image..." << std::endl;
    IMG_Quit();
    std::cout << "Shutting down SDL_ttf..." << std::endl;
    TTF_Quit();

    std::cout << "Shutting down SDL2 and all subsystems..." << std::endl;
    SDL_Quit();

    Global::App::BOILERPLATE_INITIALIZED = false;
    std::cout << "Shut down complete!" << std::endl;
}