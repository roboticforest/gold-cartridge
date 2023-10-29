/**
 * @author David Vitez (AKA: Robotic Forest)
 * @copyright All rights reserved © 2023 David Vitez
 * @license This Source Code Form is subject to the terms of the Mozilla Public
 *          License, v. 2.0. If a copy of the MPL was not distributed with this
 *          file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "button.h"

#include <SDL_ttf.h>

#include "globals.h"
#include "test_logging.h"

Button::Button(int x_pixel_pos, int y_pixel_pos, int pixel_width, int pixel_height,
               std::string text_label,
               std::function<void()> action,
               SDL_Color base_color = {224, 224, 224, 255},
               SDL_Color highlight_color = {255, 255, 255, 255}) :
        button_is_depressed(false), button_is_highlighted(false) {
    button_area.x = x_pixel_pos;
    button_area.y = y_pixel_pos;
    button_area.w = pixel_width;
    button_area.h = pixel_height;
    button_label           = std::move(text_label);
    button_action          = std::move(action);
    button_color           = base_color;
    button_highlight_color = highlight_color;
}

void Button::handle_event(SDL_Event& event) {
    switch (event.type) {
        case SDL_MOUSEMOTION:
            if (button_contains_point(event.motion.x, event.motion.y)) {
                button_is_highlighted = true;
            }
            else {
                button_is_highlighted = false;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (button_contains_point(event.button.x, event.button.y)) {
                button_is_depressed = true;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (button_contains_point(event.button.x, event.button.y) && button_is_depressed) {
                button_action();
            }
            button_is_depressed = false;
            break;
    }
}

void Button::draw() {
    // Fill the button area with color.
    if (button_is_highlighted) {
        SDL_SetRenderDrawColor(Global::App::MAIN_RENDERER, button_highlight_color.r, button_highlight_color.g, button_highlight_color.b, button_highlight_color.a);
    }
    else {
        SDL_SetRenderDrawColor(Global::App::MAIN_RENDERER, button_color.r, button_color.g, button_color.b, button_color.a);
    }
    SDL_RenderFillRect(Global::App::MAIN_RENDERER, &button_area);

    // Convert the label text into a displayable image, saving that to a texture for rendering to the screen.
    SDL_Surface* initial_label_render = TTF_RenderText_Blended(Global::TEST_FONT, button_label.c_str(), Global::TEST_FONT_COLOR);
    if (!initial_label_render) {
        log_error("Unable to render button label to a drawing surface.");
        return;
    }

    SDL_Texture* final_label_texture = SDL_CreateTextureFromSurface(Global::App::MAIN_RENDERER, initial_label_render);
    SDL_FreeSurface(initial_label_render);

    if (!final_label_texture) {
        log_error("Unable to convert button label drawing surface to a texture.");
        return;
    }

    // Calculate a valid label drawing area within the button's visual area on screen.
    int      label_x               = std::max(button_area.x, button_area.x + (button_area.w / 2) - (initial_label_render->w / 2));
    int      label_y               = std::max(button_area.y, button_area.y + (button_area.h / 2) - (initial_label_render->h / 2));
    int      label_width           = std::min(initial_label_render->w, button_area.w);
    int      label_height          = std::min(initial_label_render->h, button_area.h);
    SDL_Rect label_dest_pixel_area = {label_x, label_y, label_width, label_height};

    // Calculate which pixels of the texture to copy into the label drawing area on screen.
    int      horizontal_pixel_clip = std::max(initial_label_render->w - button_area.w, 0);
    int      vertical_pixel_clip   = std::max(initial_label_render->h - button_area.h, 0);
    SDL_Rect label_src_pixel_area  = {
            horizontal_pixel_clip / 2,
            vertical_pixel_clip / 2,
            initial_label_render->w - horizontal_pixel_clip,
            initial_label_render->h - vertical_pixel_clip
    };

    // Render the button label to the screen.
    SDL_RenderCopy(Global::App::MAIN_RENDERER, final_label_texture, &label_src_pixel_area, &label_dest_pixel_area);
    SDL_DestroyTexture(final_label_texture);
}

bool Button::button_contains_point(int x, int y) const {
    return x >= button_area.x &&
           x <= button_area.x + button_area.w &&
           y >= button_area.y &&
           y <= button_area.y + button_area.h;
}



