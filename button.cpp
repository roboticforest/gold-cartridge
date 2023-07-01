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

Button::Button(int x_pixel_pos, int y_pixel_pos, int pixel_width, int pixel_height, std::string text_label,
               std::function<void()> button_action) :
        is_depressed(false), is_highlighted(false) {
    this->button_area.x = x_pixel_pos;
    this->button_area.y = y_pixel_pos;
    this->button_area.w = pixel_width;
    this->button_area.h = pixel_height;
    this->text_label    = std::move(text_label);
    this->action        = std::move(button_action);
}

void Button::handle_event(SDL_Event& event) {
    switch (event.type) {
        case SDL_MOUSEMOTION:
            if (this->contains_point(event.motion.x, event.motion.y)) {
                this->is_highlighted = true;
            }
            else {
                this->is_highlighted = false;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (this->contains_point(event.button.x, event.button.y)) {
                this->is_depressed = true;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (this->contains_point(event.button.x, event.button.y) && this->is_depressed) {
                this->action();
            }
            this->is_depressed = false;
            break;
    }
}

void Button::draw() {
    // Fill the button area with color.
    SDL_SetRenderDrawColor(MAIN_RENDERER, 238, 238, 236, 255);
    SDL_RenderFillRect(MAIN_RENDERER, &this->button_area);

    // Convert the label text into a displayable image, saving that to a texture for rendering to the screen.
    SDL_Surface* initial_label_render = TTF_RenderText_Blended(TEST_FONT, this->text_label.c_str(), TEST_FONT_COLOR);
    if (!initial_label_render) {
        log_error("Unable to render button label to a drawing surface.");
        return;
    }

    SDL_Texture* final_label_texture = SDL_CreateTextureFromSurface(MAIN_RENDERER, initial_label_render);
    SDL_FreeSurface(initial_label_render);

    if (!final_label_texture) {
        log_error("Unable to convert button label drawing surface to a texture.");
        return;
    }

    // Calculate a valid label drawing area within the button's visual area on screen.
    int      label_x               = std::max(this->button_area.x, this->button_area.x + (this->button_area.w / 2) - (initial_label_render->w / 2));
    int      label_y               = std::max(this->button_area.y, this->button_area.y + (this->button_area.h / 2) - (initial_label_render->h / 2));
    int      label_width           = std::min(initial_label_render->w, this->button_area.w);
    int      label_height          = std::min(initial_label_render->h, this->button_area.h);
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
    SDL_RenderCopy(MAIN_RENDERER, final_label_texture, &label_src_pixel_area, &label_dest_pixel_area);
    SDL_DestroyTexture(final_label_texture);
}

bool Button::contains_point(int x, int y) const {
    return x >= this->button_area.x &&
           x <= this->button_area.x + this->button_area.w &&
           y >= this->button_area.y &&
           y <= this->button_area.y + this->button_area.h;
}



