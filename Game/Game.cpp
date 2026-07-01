#include "../Engine/Engine.h"
#include "SDL3/SDL.h"

#include <iostream>

int main()
{
    fnEngine();
    // run this before adding anything else to make sure library works
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SDL3 Project", 1280, 1024, 0);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == nullptr) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event e;
    bool quit = false;

    // Define a rectangle
    SDL_FRect greenSquare{ 270, 190, 150, 150 };
    SDL_FRect colouredSquare{ 600, 600, 30, 30 };
    SDL_Color colour{ 30, 255, 150, 255 };

    bool increasing = false;
    bool rIncrease = true;
    bool gIncrease = false;
    bool bIncrease = false;
    int increment = 0;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        if (greenSquare.w >= 200) {
            increasing = false;
        }
        if (greenSquare.w <= 5) {
            increasing = true;
        }
        increment = (increment == 5 ? 0 : increment + 1);

        if (colour.r == 255) rIncrease = false;
        if (colour.r == 0) rIncrease = true;
        if (colour.g == 255) gIncrease = false;
        if (colour.g == 0) gIncrease = true;
        if (colour.b == 255) bIncrease = false;
        if (colour.b == 0) bIncrease = true;

        if (increment == 0) {
            greenSquare.w = (increasing ? greenSquare.w + 1 : greenSquare.w - 1);
            greenSquare.h = (increasing ? greenSquare.h + 1 : greenSquare.h - 1);
            colour.r = (rIncrease ? colour.r + 1 : colour.r - 1);
            colour.g = (gIncrease ? colour.g + 1 : colour.g - 1);
            colour.b = (bIncrease ? colour.b + 1 : colour.b - 1);
        }


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set render draw color to black
        SDL_RenderClear(renderer); // Clear the renderer

        SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
        SDL_RenderFillRect(renderer, &colouredSquare);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Set render draw color to green
        SDL_RenderFillRect(renderer, &greenSquare); // Render the rectangle

        // new stuff
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDebugText(renderer, 30, 30, "bonjour");

        SDL_RenderPresent(renderer); // Render the screen
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

}
