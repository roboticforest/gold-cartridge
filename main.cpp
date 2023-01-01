#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

int main() {

    SDL_Window * main_window = nullptr;
    SDL_Surface * drawing_area = nullptr;
    SDL_Surface * test_image = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Video failed to initialize!" << std::endl;
        std::cout << "SDL says: " << SDL_GetError() << std::endl;
    }
    else {
        main_window = SDL_CreateWindow("Game Window",
                         SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                         WINDOW_WIDTH, WINDOW_HEIGHT,
                         SDL_WINDOW_SHOWN);
    }
    if (main_window == nullptr) {
        std::cout << "Window creation failed!" << std::endl;
        std::cout << "SDL says: " << SDL_GetError() << std::endl;
    }
    else {

        if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
            std::cout << "SDL_image could not initialize." << std::endl;
            std::cout << "SDL_image says: " << IMG_GetError() << std::endl;
        }
        else {
            test_image = IMG_Load("resources/pixel-art-ball.png");
            if (!test_image) {
                std::cout << "Failed to load the image of the ball." << std::endl;
                std::cout << "SDL_image says: " << IMG_GetError() << std::endl;
            }
        }

        drawing_area = SDL_GetWindowSurface(main_window);
        SDL_FillRect(drawing_area, nullptr, 0x00aa00);

        if (test_image) {
            SDL_BlitSurface(test_image, nullptr, drawing_area, nullptr);
        }

        SDL_UpdateWindowSurface(main_window);
        SDL_Event e; bool quit = false; while(!quit){ while( SDL_PollEvent(&e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
    }

    SDL_DestroyWindow(main_window);
    SDL_Quit();
    return 0;
}
