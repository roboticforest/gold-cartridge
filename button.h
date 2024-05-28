/**
 * @author David Vitez (AKA: Robotic Forest)
 * @copyright All rights reserved © 2023 David Vitez
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 *          License, v. 2.0. If a copy of the MPL was not distributed with this
 *          file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef GOLD_CARTRIDGE_BUTTON_H
#define GOLD_CARTRIDGE_BUTTON_H

#include <string>
#include <functional>

#include <SDL.h>

/**
 * @brief Represents a button that can be displayed on the screen.
 */
class Button {
public:
    /**
     * Constructs and configures a Button object.
     * @param x_pixel_pos The x-coordinate of the button's top-left corner, in pixels.
     * @param y_pixel_pos The y-coordinate of the button's top-left corner, in pixels.
     * @param pixel_width The _windowWidth of the button, in pixels.
     * @param pixel_height The _windowHeight of the button, in pixels.
     * @param text_label The label displayed on the button.
     * @param action The function to be called when the button is clicked.
     */
    Button(int x_pixel_pos, int y_pixel_pos, int pixel_width, int pixel_height, std::string text_label, std::function<void()> action,
           SDL_Color button_color, SDL_Color highlight_color);

    /**
     * Handles mouse events for the button.
     * @param event The SDL event to be handled.
     */
    void handle_event(SDL_Event& event);

    /**
     * Draws the button on the screen.
     */
    void draw();

private:
    /**
     * Checks whether the pixel coordinate is within the button's area.
     * @param x The x-coordinate of the point, in pixels.
     * @param y The y-coordinate of the point, in pixels.
     * @return True if the point is within the button's area, false otherwise.
     */
    [[nodiscard]] bool button_contains_point(int x, int y) const;

    // Button Properties
    // =================

    SDL_Color             button_color;           // The color of the button.
    SDL_Color             button_highlight_color; // The color of the button when selected.
    SDL_Rect              button_area;            // The area occupied by the button.
    bool                  button_is_depressed;    // Whether the button is currently pressed.
    bool                  button_is_highlighted;  // Whether the button is highlighted.
    std::function<void()> button_action;          // The function to be called when the button is clicked.
    std::string           button_label;           // The label displayed on the button.
};

#endif //GOLD_CARTRIDGE_BUTTON_H
