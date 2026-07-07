#include "Engine.h"
#include <iostream>
#include <vector>

using namespace nu;
using namespace std;

int main()
{
    fnEngine();

    nu::Renderer renderer;

    nu::Input input;
    input.Initialize();

    const int WIN_WIDTH = 1024;
    const int WIN_HEIGHT = 1080;

    const int starcount = 10000;

    renderer.Initialize("Project1", WIN_WIDTH, WIN_HEIGHT);

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
            if (e.type == SDL_EVENT_KEY_DOWN && e.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }


        input.Update();

        if (input.GetKeyDown(SDL_SCANCODE_Q)) std::cout << "Q down" << std::endl;
        if (input.GetKeyPressed(SDL_SCANCODE_W)) std::cout << "W pressed" << std::endl;
        if (input.GetKeyReleased(SDL_SCANCODE_E)) std::cout << "E released" << std::endl;

        Vector2 mousePosition;
        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

        if (colour.r == 255) rIncrease = false;
        if (colour.r == 0) rIncrease = true;
        if (colour.g == 255) gIncrease = false;
        if (colour.g == 0) gIncrease = true;
        if (colour.b == 255) bIncrease = false;
        if (colour.b == 0) bIncrease = true;

        colour.r = (rIncrease ? colour.r + 1 : colour.r - 1);
        colour.g = (gIncrease ? colour.g + 1 : colour.g - 1);
        colour.b = (bIncrease ? colour.b + 1 : colour.b - 1);


        renderer.SetColour(0, 0, 0);
        renderer.Clear(); // Clear the renderer

        renderer.SetColour(colour);
        renderer.DrawFillRect(&colouredSquare);

        for (int i = 0; i < vs.size(); i++) {
            renderer.SetColourRandom();
            renderer.DrawPoint(vs.at(i).x, vs.at(i).y);
        }

        renderer.SetColour(150, 220, 20);
        renderer.DrawFillRect(input.GetMousePosition().x - 20, input.GetMousePosition().y - 20, 40, 40);

        renderer.SetColour(255, 255, 255);
        renderer.DrawDebugText(30, 30, "press ESC to quit");

        renderer.Present(); // Render the screen
    }

    renderer.Shutdown();

    return 0;

}
