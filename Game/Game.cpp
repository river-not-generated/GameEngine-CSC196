#include "Engine.h"
#include <iostream>
#include <vector>

using namespace nu;
using namespace std;

int main()
{
    fnEngine();

    nu::Renderer r;

    const int WIN_WIDTH = 1024;
    const int WIN_HEIGHT = 1080;

    const int starcount = 10000;

    r.Initialize("Project1", WIN_WIDTH, WIN_HEIGHT);

    float xs[30];
    float ys[30];

    Vector2 vel{ 2.0f, 0.0f };

    vector<Vector2> vs;


    for (int i = 0; i < 30; i++) {
        xs[i] = RandomFloat(WIN_WIDTH);
        ys[i] = RandomFloat(WIN_HEIGHT);
    }

    for (int i = 0; i < starcount; i++) {
        Vector2 vec(RandomFloat(WIN_WIDTH), RandomFloat(WIN_HEIGHT));
        vs.push_back(vec);
    }

    SDL_FRect colouredSquare{ (WIN_WIDTH / 2) - 25, (WIN_HEIGHT / 2) - 25, 50, 50 };
    SDL_Color colour{ 60, 255, 150, 255 };

    bool rIncrease = true;
    bool gIncrease = false;
    bool bIncrease = false;

    int incrementer = 0;

    // main loop
    SDL_Event e;
    bool quit = false;
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

        for (int i = 0; i < vs.size(); i++) {
            r.SetColourRandom();
            r.DrawPoint(vs.at(i).x, vs.at(i).y);
            vs.at(i) = vs.at(i) + vel;
        }


        for (int i = 0; i < 30; i += 2) {
            r.SetColourRandom();
            r.DrawLine(xs[i], ys[i], xs[i + 1], ys[i + 1]);
        }

        for (int i = 0; i < 3; i++) {
            r.SetColourRandom();
            int width = rand() % 200;
            int height = rand() % 200;
            r.DrawFillRect(RandomFloat(WIN_WIDTH - width), RandomFloat(WIN_HEIGHT - height), (float) width, (float) height);
        }

        r.SetColour(255, 255, 255);
        r.DrawDebugText(30, 30, "debug text");

        r.Present(); // Render the screen

        r.Delay(250);
    }

    r.Shutdown();

    return 0;

}
