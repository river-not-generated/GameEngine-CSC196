#include "Engine.h"
#include "SDL3/SDL.h"

#include <iostream>

int main()
{
    fnEngine();

    nu::Renderer r;

    const int WIN_WIDTH = 1024;
    const int WIN_HEIGHT = 1080;

    r.Initialize("Project1", WIN_WIDTH, WIN_HEIGHT);

    SDL_Event e;
    bool quit = false;


    SDL_FRect colouredSquare{ (WIN_WIDTH / 2) - 25, (WIN_HEIGHT / 2) - 25, 50, 50 };
    SDL_Color colour{ 60, 255, 150, 255 };

    bool rIncrease = true;
    bool gIncrease = false;
    bool bIncrease = false;

    int incrementer = 0;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        if (colour.r == 255) rIncrease = false;
        if (colour.r == 0) rIncrease = true;
        if (colour.g == 255) gIncrease = false;
        if (colour.g == 0) gIncrease = true;
        if (colour.b == 255) bIncrease = false;
        if (colour.b == 0) bIncrease = true;

        colour.r = (rIncrease ? colour.r + 1 : colour.r - 1);
        colour.g = (gIncrease ? colour.g + 1 : colour.g - 1);
        colour.b = (bIncrease ? colour.b + 1 : colour.b - 1);


        r.SetColour(0, 0, 0);
        r.Clear(); // Clear the renderer

        r.SetColour(colour);
        r.DrawFillRect(&colouredSquare);

        for (int i = 0; i < 10000; i++) {
            r.SetColourRandom();
            r.DrawPoint(rand() % WIN_WIDTH, rand() % WIN_HEIGHT);
        }


        for (int i = 0; i < 10; i++) {
            r.SetColourRandom();
            r.DrawLine(rand() % WIN_WIDTH, rand() % WIN_HEIGHT, rand() % WIN_WIDTH, rand() % WIN_HEIGHT);
        }

        for (int i = 0; i < 3; i++) {
            r.SetColourRandom();
            int width = rand() % 200;
            int height = rand() % 200;
            r.DrawFillRect(rand() % WIN_WIDTH - width, rand() % WIN_HEIGHT - height, width, height);
        }

        r.SetColour(255, 255, 255);
        r.DrawDebugText(30, 30, "debug text");

        r.Present(); // Render the screen

        r.Delay(250);
    }

    r.Shutdown();

    return 0;

}
