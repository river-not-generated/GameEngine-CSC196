#include "Engine.h"
#include "SDL3/SDL.h"

#include <iostream>

int main()
{
    fnEngine();

    nu::Renderer r;

    r.Initialize("Project1", 1024, 1080);

    SDL_Event e;
    bool quit = false;


    SDL_FRect colouredSquare{ 200, 200, 50, 50 };
    SDL_Color colour{ 60, 255, 150, 255 };

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

        increment = (increment == 60 ? 0 : increment + 1);

        if (colour.r == 255) rIncrease = false;
        if (colour.r == 0) rIncrease = true;
        if (colour.g == 255) gIncrease = false;
        if (colour.g == 0) gIncrease = true;
        if (colour.b == 255) bIncrease = false;
        if (colour.b == 0) bIncrease = true;

        if (increment % 10 == 0) {
            colour.r = (rIncrease ? colour.r + 1 : colour.r - 1);
            colour.g = (gIncrease ? colour.g + 1 : colour.g - 1);
            colour.b = (bIncrease ? colour.b + 1 : colour.b - 1);
        }

        r.SetColour(0, 0, 0);
        r.Clear(); // Clear the renderer

        r.SetColour(colour);
        r.DrawFillRect(&colouredSquare);

        r.SetColour(255, 255, 255);
        r.DrawDebugText(30, 30, "debug text");

        r.Present(); // Render the screen
    }

    r.Shutdown();

    return 0;

}
