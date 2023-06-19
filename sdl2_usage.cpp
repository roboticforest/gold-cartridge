#include "sdl2_usage.h"

#include <SDL.h>

#include "test_asserts.h"
#include "globals.h"

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