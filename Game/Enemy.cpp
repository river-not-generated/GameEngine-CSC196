#include "pch.h"
#include "Enemy.h"
#include "Engine.h"

void Enemy::Update(float dt) {

    // movement control for the Enemy square (WASD or arrows)
    // nu::Vector2 force{ 0.0f, 0.0f };

    float thrust = 0.0f;
    //if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_W) || nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_UP)) {
    //    thrust = m_speed;
    //}
    //if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_S) || nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_DOWN)) {
    //    thrust = -m_speed;
    //}

    float rotate = 0.0f;
    //if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_A) || nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) {
    //    rotate = -270.0f;
    //}
    //if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_D) || nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) {
    //    rotate = 270.0f;
    //}

    SetRotation(m_transform.rotation + rotate * dt);

    nu::Vector2 forward{ 1.0f, 0.0f };
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::math::DEG_TO_RAD) * thrust;
    AddVelocity(velocity * dt);

    //SetVelocity(GetVelocity() + (force * dt));

    Actor::Update(dt);
}

void Enemy::Draw(const nu::Renderer& renderer) const {
    Actor::Draw(renderer);
}