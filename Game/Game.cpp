#include "Engine.h"
#include <iostream>
#include <vector>

using namespace nu;
using namespace std;


const int WIN_WIDTH = 1024;
const int WIN_HEIGHT = 1080;

struct Transform {
    Vector2 position;
    float rotation;
    float scale;
};

class Actor {
    public:
        Actor() = default;
        Actor(const Transform& transform) : m_transform{ transform } {}

        void Update(float dt) {
            m_transform.position += (m_velocity * dt);
            m_velocity *= 0.997f;

            m_transform.position.x = math::Wrap(0.0f, (float)WIN_WIDTH, m_transform.position.x);
            m_transform.position.y = math::Wrap(0.0f, (float)WIN_HEIGHT, m_transform.position.y);
        }

        void Draw(const Renderer& renderer) const {
            renderer.SetColour(150, 220, 20);
            renderer.DrawFillRect(m_transform.position.x - (m_transform.scale * 0.5f)
                , m_transform.position.y - (m_transform.scale * 0.5f)
                , m_transform.scale, m_transform.scale);
        }
        const Transform& GetTransform() const {
            return m_transform;
        }
        const Vector2& GetVelocity() const {
            return m_velocity;
        }

        void SetVelocity(const Vector2& velocity) {
            m_velocity = velocity;
        }
        void SetPosition(const Vector2& position) {
            m_transform.position = position;
        }
        void SetRotation(float rotation) {
            m_transform.rotation = rotation;
        }
        void SetScale(float scale) {
            m_transform.scale = scale;
        }

    protected:
        Transform m_transform;
        Vector2 m_velocity{ 0.0f, 0.0f };
};

class BrushStroke {
    public:
        BrushStroke(const Vector2& point, const SDL_Color& colour) : m_points{ vector<Vector2>{point} }, m_colour { colour } {}
        vector<Vector2> m_points;
        SDL_Color m_colour;
};

int main()
{
    // confirm the engine is connected
    fnEngine();

    // initialize the renderer and input handlers
    nu::Renderer renderer;
    renderer.Initialize("Project1", WIN_WIDTH, WIN_HEIGHT);
    nu::Input input;
    input.Initialize();

    // game time handline
    uint64_t ticks = SDL_GetTicksNS();
    uint64_t prevTicks = ticks;
    Time time;

    // program-specific variables
    vector<BrushStroke> brushStrokes;
    Vector2 position{ WIN_WIDTH / 2, WIN_HEIGHT / 2 };
    float speed = 400;
    Actor player{ Transform{ Vector2{ WIN_WIDTH / 2, WIN_HEIGHT / 2}, 0.0f, 10.0f } };

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

        input.Update();
        time.Tick();

        // movement control for the player square (WASD or arrows)
        Vector2 force{ 0.0f, 0.0f };
        if (input.GetKeyDown(SDL_SCANCODE_A) || input.GetKeyDown(SDL_SCANCODE_LEFT)) {
            force.x -= speed;
        }
        if (input.GetKeyDown(SDL_SCANCODE_D) || input.GetKeyDown(SDL_SCANCODE_RIGHT)) {
            force.x += speed;
        }
        if (input.GetKeyDown(SDL_SCANCODE_W) || input.GetKeyDown(SDL_SCANCODE_UP)) {
            force.y -= speed;
        }
        if (input.GetKeyDown(SDL_SCANCODE_S) || input.GetKeyDown(SDL_SCANCODE_DOWN)) {
            force.y += speed;
        }
        player.SetVelocity(player.GetVelocity() + (force * time.GetDeltaTime()));
        player.Update(time.GetDeltaTime());

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
        if (input.GetKeyPressed(SDL_SCANCODE_C)) {
            drawColour = squareColour;
        }

        // upon starting a new line (initial LMB press) add a brush stroke object containing the current mouse position and draw colour
        if (input.GetMousePressed(Input::MouseButton::Left)) {
            brushStrokes.push_back(BrushStroke{ Vector2{input.GetMousePosition()}, drawColour});
        }

        // if they continue holding down LMB then add points whenever the position changes by more than 2 pixels
        // the assignment says 10 but I like some precision in my drawing program
        if (input.GetMouseDown(Input::MouseButton::Left)) {
            Vector2 v = brushStrokes.back().m_points.back() - input.GetMousePosition();
            if (v.Length() > 2) {
                brushStrokes.back().m_points.push_back(input.GetMousePosition());
            }
        }

        // if not currently drawing a line, undo if you press Z or RMB
        if ((input.GetMousePressed(Input::MouseButton::Right) || (input.GetKeyPressed(SDL_SCANCODE_Z)) && !input.GetMouseDown(Input::MouseButton::Left))) {
            if (!brushStrokes.empty()) brushStrokes.pop_back();
        }


        // ---------------
        // --- DRAWING ---
        // ---------------

        renderer.SetColour(0, 0, 0);
        renderer.Clear(); // Clear the renderer

        renderer.SetColour(squareColour);
        renderer.DrawFillRect(&colouredSquare);

        // for each brush stroke
        for (const BrushStroke& line : brushStrokes) {
            // set the colour to the current brush stroke colour
            renderer.SetColour(line.m_colour);

            // if there is only one point then draw it
            if (line.m_points.size() == 1) {
                renderer.DrawPoint(line.m_points.front().x, line.m_points.front().y);
            }
            // otherwise connect each point in the sequence
            for (int i = 1; i < line.m_points.size(); i++) {
                renderer.DrawLine(line.m_points.at(i - 1).x, line.m_points.at(i - 1).y
                    , line.m_points.at(i).x, line.m_points.at(i).y);
            }
        }

        // draw the moveable cube
        player.Draw(renderer);

        renderer.SetColour(255, 255, 255);
        renderer.DrawDebugText(30, 30, "C to change colour");
        renderer.DrawDebugText(30, 50, "RMB or Z to undo");
        renderer.DrawDebugText(30, 70, "ESC to quit");

        renderer.Present(); // render the screen
    }

    // shut down the program cleanly upon exiting (either through the X button or escape)
    renderer.Shutdown();

    return 0;

}
