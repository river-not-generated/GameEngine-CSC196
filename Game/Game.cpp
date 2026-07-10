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
    fnEngine();

    nu::Renderer renderer;

    nu::Input input;
    input.Initialize();



    renderer.Initialize("Project1", WIN_WIDTH, WIN_HEIGHT);

    vector<BrushStroke> art;
    vector<Vector2> points;
    Vector2 position{ WIN_WIDTH / 2, WIN_HEIGHT / 2 };

    float speed = 400;

    uint64_t ticks = SDL_GetTicksNS();
    uint64_t prevTicks = ticks;

    Time time;

    Actor player{ Transform{ Vector2{ WIN_WIDTH / 2, WIN_HEIGHT / 2}, 0.0f, 10.0f } };

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

        Vector2 force{ 0.0f, 0.0f };
        if (input.GetKeyDown(SDL_SCANCODE_A)) {
            force.x -= speed;
        }
        if (input.GetKeyDown(SDL_SCANCODE_D)) {
            force.x += speed;
        }
        if (input.GetKeyDown(SDL_SCANCODE_W)) {
            force.y -= speed;
        }
        if (input.GetKeyDown(SDL_SCANCODE_S)) {
            force.y += speed;
        }
        player.SetVelocity(player.GetVelocity() + (force * time.GetDeltaTime()));
        player.Update(time.GetDeltaTime());


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

        if (input.GetKeyPressed(SDL_SCANCODE_C)) {
            drawColour = colour;
        }

        if (input.GetMousePressed(Input::MouseButton::Left)) {
            // upon starting a new line add a brush stroke containing the current mouse position and colour
            art.push_back(BrushStroke{ Vector2{input.GetMousePosition()}, drawColour});
        }

        if (input.GetMouseDown(Input::MouseButton::Left)) {
            Vector2 v = art.back().m_points.back() - input.GetMousePosition();
            if (v.Length() > 1) {
                art.back().m_points.push_back(input.GetMousePosition());
            }
        }
        if (input.GetMousePressed(Input::MouseButton::Right) && !input.GetMouseDown(Input::MouseButton::Left)) {
            if (!art.empty()) art.pop_back();
        }

        renderer.SetColour(0, 0, 0);
        renderer.Clear(); // Clear the renderer

        renderer.SetColour(colour);
        renderer.DrawFillRect(&colouredSquare);

        // for each brush stroke
        for (const BrushStroke& line : art) {
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

        // character
        player.Draw(renderer);

        renderer.SetColour(255, 255, 255);
        renderer.DrawDebugText(30, 30, "press ESC to quit");

        renderer.Present(); // Render the screen
    }

    renderer.Shutdown();

    return 0;

}
