//
// Created by david on 3/13/23.
//

#include "button.h"

#include <iostream>
#include <SDL_ttf.h>

extern SDL_Window  * MAIN_WINDOW;
extern SDL_Renderer* MAIN_RENDERER;
extern TTF_Font    * TEST_FONT;
extern SDL_Color     TEXT_COLOR;

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
    SDL_SetRenderDrawColor(MAIN_RENDERER, 238, 238, 236, 255);
    SDL_RenderFillRect(MAIN_RENDERER, &this->button_area);

    SDL_Surface* label_render = TTF_RenderText_Blended(TEST_FONT, this->text_label.c_str(), TEXT_COLOR);
    if (label_render) {
        SDL_Texture* label_texture = SDL_CreateTextureFromSurface(MAIN_RENDERER, label_render);
        if (label_texture) {
            SDL_Rect label_area = {
                    std::max(this->button_area.x,
                             this->button_area.x + (this->button_area.w / 2) - (label_render->w / 2)),
                    std::max(this->button_area.y,
                             this->button_area.y + (this->button_area.h / 2) - (label_render->h / 2)),
                    std::min(label_render->w, this->button_area.w),
                    std::min(label_render->h, this->button_area.h)
            };

            int      horizontal_pixel_clip = std::max(label_render->w - button_area.w, 0);
            int      vertical_pixel_clip   = std::max(label_render->h - button_area.h, 0);
            SDL_Rect text_clip_area        = {
                    horizontal_pixel_clip / 2,
                    vertical_pixel_clip / 2,
                    label_render->w - horizontal_pixel_clip,
                    label_render->h - vertical_pixel_clip
            };

            SDL_RenderCopy(MAIN_RENDERER, label_texture, &text_clip_area, &label_area);
            SDL_DestroyTexture(label_texture);
        }
        SDL_FreeSurface(label_render);
    }
    else {
        std::cerr << "Something broke in the button text rendering." << std::endl;
    }
}

bool Button::contains_point(int x, int y) const {
    return x >= this->button_area.x &&
            x <= this->button_area.x + this->button_area.w &&
            y >= this->button_area.y &&
            y <= this->button_area.y + this->button_area.h;
}



