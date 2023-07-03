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

/**
 * Initialize all of SDL's core subsystems, logging any errors and terminating the program if they occur.
 */
void prep_SDL2() {
    assert_task([]() { return SDL_InitSubSystem(SDL_INIT_VIDEO) == 0; },
                "Starting SDL2's Video subsystem...",
                "Video failed to initialize!");

    assert_task([]() -> bool { return SDL_InitSubSystem(SDL_INIT_AUDIO) == 0; },
                "Starting SDL2's Audio subsystem...",
                "Audio playback failed to initialize!");

    assert_task([]() { return SDL_InitSubSystem(SDL_INIT_EVENTS) == 0; },
                "Starting SDL2's Event handling subsystem...",
                "Event handling failed to initialize!");

    assert_task([]() { return SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) == 0; },
                "Starting SDL2's Gamepad and Joystick Input subsystems...",
                "Game Controller Input handling failed to initialize!");

    assert_task([]() { return SDL_InitSubSystem(SDL_INIT_HAPTIC) == 0; },
                "Starting SDL2's Haptic Feedback subsystem...",
                "Haptic Feedback failed to initialize!");

    assert_task([]() { return SDL_InitSubSystem(SDL_INIT_TIMER) == 0; },
                "Starting SDL2's Timer subsystem...",
                "Timers failed to initialize!");
}

/**
 * Create the application's main window, terminating the application if one can not be made.
 */
void prep_window() {
    auto create_window = []() {
        MAIN_WINDOW = SDL_CreateWindow("Main Window",
                                       SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT,
                                       SDL_WINDOW_SHOWN);
        return MAIN_WINDOW != nullptr;
    };
    assert_task(create_window,
                "Creating main application window...",
                "Main window could not be created!");
}

/**
 * Create the application's primary drawing context, terminating the application if that fails.
 */
void prep_renderer() {
    auto create_renderer = []() {
        MAIN_RENDERER = SDL_CreateRenderer(MAIN_WINDOW, -1, SDL_RENDERER_ACCELERATED);
        return MAIN_RENDERER != nullptr;
    };
    assert_task(create_renderer,
                "Creating primary rendering context...",
                "A rendering context could not be created!");
}

/**
 * Initialize the SDL_image library to load desired image formats.
 */
void prep_SDL_image() {
    assert_task([]() { return ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)); },
                "Configuring SDL_image for PNG file loading...",
                "PNG file loader could not be initialized!"
    );
}

/**
 * Use SDL_image to load a test graphic.
 */
void load_test_graphic() {
    SDL_Surface *png_img = IMG_Load(TEST_IMAGE_FILE_PATH.c_str());

    if (!png_img) {
        std::string error_msg = "The test image \"" + TEST_IMAGE_FILE_PATH + "\" could not be loaded.";
        log_SDL2_error(error_msg);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Image Not Found",
                                 "Test graphic could not be loaded! See log for more details.", MAIN_WINDOW);
    } else {
        TEST_IMAGE = SDL_CreateTextureFromSurface(MAIN_RENDERER, png_img);
    }

    if (!TEST_IMAGE) {
        auto make_empty_texture = []() {
            TEST_IMAGE = SDL_CreateTexture(MAIN_RENDERER, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 64, 64);
            return TEST_IMAGE != nullptr;
        };
        assert_task(make_empty_texture, "Making a placeholder for the test image.",
                    "Unable to create generic empty textures. Aborting!");
        SDL_Rect square = {0, 0, 64, 64};
        SDL_SetRenderTarget(MAIN_RENDERER, TEST_IMAGE);
        SDL_SetRenderDrawColor(MAIN_RENDERER, 255, 0, 0, 255);
        SDL_RenderFillRect(MAIN_RENDERER, &square);
        SDL_SetRenderTarget(MAIN_RENDERER, nullptr);
    }
    SDL_FreeSurface(png_img);
}

/**
 * Initialize the SDL_ttf library.
 */
void prep_SDL_ttf() {
    assert_task([]() { return TTF_Init() == 0; },
                "Initializing SDL_ttf...",
                "SDL True Type Font loader failed to initialize!");
}

/**
 * Use SDL_ttf to load a test font. Currently, this font is the default used all throughout other tests. This needs to
 * be repurposed for more general usage.
 */
void load_test_font() {
    auto open_font = []() -> bool {
        TEST_FONT = TTF_OpenFont(TEST_FONT_FILE_PATH.c_str(), TEST_FONT_SIZE_PTS);
        return TEST_FONT != nullptr;
    };
    assert_task(open_font, "Loading test font...", "Test font failed to load! Aborting!");
}

/**
 * Renders a test sentence to a texture for later rendering to the screen.
 */
void prep_test_text_render() {

    SDL_Surface *text_render_surface = nullptr;
    auto render_text_to_surface = [&text_render_surface]() -> bool {
        text_render_surface = TTF_RenderText_Blended(TEST_FONT, TEST_SENTENCE.c_str(), TEST_FONT_COLOR);
        return text_render_surface != nullptr;
    };
    assert_task(render_text_to_surface,
                "Rendering text to an image surface...",
                "Rendering text failed. Aborting!");

    auto convert_text_surface_to_texture = [&text_render_surface]()->bool {
        TEXT_RENDER_TEXTURE = SDL_CreateTextureFromSurface(MAIN_RENDERER, text_render_surface);
        return TEXT_RENDER_TEXTURE != nullptr;
    };
    assert_task(convert_text_surface_to_texture,
                "Converting text render surface to a texture...",
                "Conversion of text render surface to a texture failed. Aborting!");

    TEXT_RENDER_LOCATION.w = text_render_surface->w;
    TEXT_RENDER_LOCATION.h = text_render_surface->h;

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

    BOILERPLATE_INITIALIZED = true;
    std::cout << "Initialization complete!" << std::endl;
}

/**
 * Deletes all dynamically allocated global resources and shuts down all libraries and SDL2 subsystems.
 */
void shutdown() {
    std::cout << "Shutting down the application..." << std::endl;

    std::cout << "Destroying the Test Image texture..." << std::endl;
    SDL_DestroyTexture(TEST_IMAGE);
    TEST_IMAGE = nullptr;

    std::cout << "Cleaning up the test font resources..." << std::endl;
    TTF_CloseFont(TEST_FONT);
    TEST_FONT = nullptr;
    std::cout << "Destroying the Text Rendering texture..." << std::endl;
    SDL_DestroyTexture(TEXT_RENDER_TEXTURE);
    TEXT_RENDER_TEXTURE = nullptr;

    std::cout << "Destroying the Main Renderer..." << std::endl;
    SDL_DestroyRenderer(MAIN_RENDERER);
    MAIN_RENDERER = nullptr;

    std::cout << "Destroying the Main Application Window..." << std::endl;
    SDL_DestroyWindow(MAIN_WINDOW);
    MAIN_WINDOW = nullptr;

    std::cout << "Shutting down SDL_image..." << std::endl;
    IMG_Quit();
    std::cout << "Shutting down SDL_ttf..." << std::endl;
    TTF_Quit();

    std::cout << "Shutting down SDL2 and all subsystems..." << std::endl;
    SDL_Quit();

    BOILERPLATE_INITIALIZED = false;
    std::cout << "Shut down complete!" << std::endl;
}