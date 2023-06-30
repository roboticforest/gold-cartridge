/**
 * @author David Vitez (AKA: Robotic Forest)
 * @copyright All rights reserved © 2023 David Vitez
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 *          License, v. 2.0. If a copy of the MPL was not distributed with this
 *          file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef GOLD_CARTRIDGE_SDL2_TESTING_H
#define GOLD_CARTRIDGE_SDL2_TESTING_H

// SDL2 Core Library
// =================

/**
 * Initializes the SDL2 core library, and all of its subsystems.
 */
void prep_SDL2();

/**
 * Creates the test application's main window.
 */
void prep_window();

/**
 * Creates a drawing area/context for the main window.
 */
void prep_renderer();

// SDL Image Library
// =================

/**
 * Initialized the SDL2_image library.
 */
void prep_SDL_image();

/**
 * Uses SDL2_image to load a graphic file from a format SDL2 can't natively load.
 */
void load_test_graphic();

// SDL TrueType Font Library
// =========================

/**
 * Initialized the SDL2_ttf library.
 */
void prep_SDL_ttf();

/**
 * Uses SDL2_ttf to load a font file.
 */
void load_test_font();

/**
 * Renders a sample sentence, using a previously loaded test font, to a texture for later rendering.
 */
void prep_test_text_render();

// General Application Functions
// =============================

/**
 * Runs all test library initialization functions in their correct order.
 */
void initialize_everything();

/**
 * Shuts down all libraries, and cleans up all dynamic resources, all in the correct order.
 */
void shutdown();

#endif //GOLD_CARTRIDGE_SDL2_TESTING_H
