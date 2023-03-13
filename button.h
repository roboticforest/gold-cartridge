//
// Created by david on 3/13/23.
//

#ifndef GOLD_CARTRIDGE_BUTTON_H
#define GOLD_CARTRIDGE_BUTTON_H

#include <string>
#include <functional>

#include <SDL.h>

class Button {
  public:
    Button(int x_pixel_pos, int y_pixel_pos, int pixel_width, int pixel_height, std::string text_label,
           std::function<void()> button_action);
    void handle_event(SDL_Event& event);
    void draw();

  private:
    [[nodiscard]] bool contains_point(int x, int y) const;

    SDL_Rect              button_area;
    std::string           text_label;
    bool                  is_highlighted;
    bool                  is_depressed;
    std::function<void()> action;
};

#endif //GOLD_CARTRIDGE_BUTTON_H
