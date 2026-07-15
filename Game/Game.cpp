#include "Engine.h"
#include "Player.h"

#include <iostream>
#include <vector>

using namespace nu;
using namespace std;

const int WIN_WIDTH = 1024;
const int WIN_HEIGHT = 1080;

class BrushStroke {
    public:
        BrushStroke(const Vector2& point, const SDL_Color& colour) : m_points{ vector<Vector2>{point} }, m_colour { colour } {}
        vector<Vector2> m_points;
        SDL_Color m_colour;
};

int main()
{
    // initialize the engine
    if (engine.Initialize(WIN_WIDTH, WIN_HEIGHT) == false) return 0;

    Mesh mesh({ Vector2{3, 1}, Vector2{0, 2}, Vector2{1, 1}, Vector2{0, 0}, Vector2{3, 1} }, Colour{ 255, 255, 255 });
    Player player{ 800.0f, Transform{ Vector2{ WIN_WIDTH / 2, WIN_HEIGHT / 2}, 0.0f, 10.0f }, vector<Mesh>{mesh} };

    // program-specific variables
    vector<BrushStroke> brushStrokes;

    // the square up in the top corner of the window
    SDL_FRect colouredSquare{ (WIN_WIDTH) - 75, 25, 50, 50 };
    SDL_Color squareColour{ 60, 255, 150, 255 };
    SDL_Color drawColour{ squareColour };

    // booleans that handle the direction of the gradient colour
    bool rIncrease = true;
    bool gIncrease = false;
    bool bIncrease = false;

    int incrementer = 0;

    // -----------------
    // --- MAIN LOOP ---
    // -----------------

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

        engine.Update();

        player.SetRotation(player.GetTransform().rotation + engine.GetTime().GetDeltaTime() * 360.0f);
        player.Update(engine.GetTime().GetDeltaTime());

        // get the current position & state of the mouse
        Vector2 mousePosition;
        SDL_GetMouseState(&mousePosition.x, &mousePosition.y);

        // gradually change the colour of The Square
        incrementer = (incrementer == 3 ? 0 : incrementer + 1);

        if (incrementer == 0) {
            if (squareColour.r == 255) rIncrease = false;
            if (squareColour.r == 0) rIncrease = true;
            if (squareColour.g == 255) gIncrease = false;
            if (squareColour.g == 0) gIncrease = true;
            if (squareColour.b == 255) bIncrease = false;
            if (squareColour.b == 0) bIncrease = true;

            squareColour.r = (rIncrease ? squareColour.r + 1 : squareColour.r - 1);
            squareColour.g = (gIncrease ? squareColour.g + 1 : squareColour.g - 1);
            squareColour.b = (bIncrease ? squareColour.b + 1 : squareColour.b - 1);
        }

        // if C is pressed change the draw colour to the current value of colour
        // which is visualized up in the top corner (the gradient square)
        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_C)) {
            drawColour = squareColour;
        }

        // upon starting a new line (initial LMB press) add a brush stroke object containing the current mouse position and draw colour
        if (engine.GetInput().GetMousePressed(Input::MouseButton::Left)) {
            brushStrokes.push_back(BrushStroke{ Vector2{engine.GetInput().GetMousePosition()}, drawColour});
        }

        // if they continue holding down LMB then add points whenever the position changes by more than 2 pixels
        // the assignment says 10 but I like some precision in my drawing program
        if (engine.GetInput().GetMouseDown(Input::MouseButton::Left)) {
            Vector2 v = brushStrokes.back().m_points.back() - engine.GetInput().GetMousePosition();
            if (v.Length() > 2) {
                brushStrokes.back().m_points.push_back(engine.GetInput().GetMousePosition());
            }
        }

        // if not currently drawing a line, undo if you press Z or RMB
        if ((engine.GetInput().GetMousePressed(Input::MouseButton::Right) || (engine.GetInput().GetKeyPressed(SDL_SCANCODE_Z))
                && !engine.GetInput().GetMouseDown(Input::MouseButton::Left)))
        {
            if (!brushStrokes.empty()) brushStrokes.pop_back();
        }

        // ---------------
        // --- DRAWING ---
        // ---------------

        engine.GetRenderer().SetColour(0, 0, 0);
        engine.GetRenderer().Clear(); // Clear the renderer

        engine.GetRenderer().SetColour(squareColour);
        engine.GetRenderer().DrawFillRect(&colouredSquare);

        // for each brush stroke
        for (const BrushStroke& line : brushStrokes) {
            // set the colour to the current brush stroke colour
            engine.GetRenderer().SetColour(line.m_colour);

            // if there is only one point then draw it
            if (line.m_points.size() == 1) {
                engine.GetRenderer().DrawPoint(line.m_points.front().x, line.m_points.front().y);
            }
            // otherwise connect each point in the sequence
            for (int i = 1; i < line.m_points.size(); i++) {
                engine.GetRenderer().DrawLine(line.m_points.at(i - 1).x, line.m_points.at(i - 1).y
                    , line.m_points.at(i).x, line.m_points.at(i).y);
            }
        }

        // draw the moveable cube
        player.Draw(engine.GetRenderer());

        engine.GetRenderer().SetColour(255, 255, 255);
        engine.GetRenderer().DrawDebugText(30, 30, "C to change colour");
        engine.GetRenderer().DrawDebugText(30, 50, "RMB or Z to undo");
        engine.GetRenderer().DrawDebugText(30, 70, "ESC to quit");

        engine.GetRenderer().Present(); // render the screen
    }

    // shut down the program cleanly upon exiting (either through the X button or escape)
    

    return 0;

}
