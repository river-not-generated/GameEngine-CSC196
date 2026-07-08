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

    renderer.Initialize("Project1", WIN_WIDTH, WIN_HEIGHT);

    vector<Vector2> points;
    Vector2 position{ WIN_WIDTH / 2, WIN_HEIGHT / 2 };
    float speed = 400;

    uint64_t ticks = SDL_GetTicksNS();
    uint64_t prevTicks = ticks;

    Time time;

    SDL_FRect colouredSquare{ (WIN_WIDTH) - 75, 25, 50, 50 };
    SDL_Color colour{ 60, 255, 150, 255 };
    SDL_Color drawColour{ colour };

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
        time.Tick();


        Vector2 velocity{ 0, 0 };
        if (input.GetKeyDown(SDL_SCANCODE_A)) {
            velocity.x -= speed;
        }
        if (input.GetKeyDown(SDL_SCANCODE_D)) {
            velocity.x += speed;
        }
        if (input.GetKeyDown(SDL_SCANCODE_W)) {
            velocity.y -= speed;
        }
        if (input.GetKeyDown(SDL_SCANCODE_S)) {
            velocity.y += speed;
        }
        position += (velocity * time.GetDeltaTime());

        Vector2 mousePosition;
        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

        incrementer = (incrementer == 3 ? 0 : incrementer + 1);

        if (incrementer == 0) {
            if (colour.r == 255) rIncrease = false;
            if (colour.r == 0) rIncrease = true;
            if (colour.g == 255) gIncrease = false;
            if (colour.g == 0) gIncrease = true;
            if (colour.b == 255) bIncrease = false;
            if (colour.b == 0) bIncrease = true;

            colour.r = (rIncrease ? colour.r + 1 : colour.r - 1);
            colour.g = (gIncrease ? colour.g + 1 : colour.g - 1);
            colour.b = (bIncrease ? colour.b + 1 : colour.b - 1);
        }


        if (input.GetMouseDown(Input::MouseButton::Left)) {
            points.push_back(input.GetMousePosition());
        }
        if (input.GetKeyPressed(SDL_SCANCODE_C)) {
            drawColour = colour;
        }

        renderer.SetColour(0, 0, 0);
        renderer.Clear(); // Clear the renderer

        renderer.SetColour(colour);
        renderer.DrawFillRect(&colouredSquare);

        renderer.SetColour(drawColour);

        for (int i = 0; i < points.size(); i++) {
            renderer.DrawFillRect(points.at(i).x - 1, points.at(i).y - 1, 2, 2);
        }

        renderer.SetColour(150, 220, 20);
        renderer.DrawFillRect(position.x - 5, position.y - 5, 10, 10);

        renderer.SetColour(255, 255, 255);
        renderer.DrawDebugText(30, 30, "press ESC to quit");

        renderer.Present(); // Render the screen
    }

    renderer.Shutdown();

    return 0;

}
