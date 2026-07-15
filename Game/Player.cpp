#include "pch.h"
#include "Player.h"
#include "Engine.h"

void Player::Update(float dt) {

    // movement control for the player square (WASD or arrows)
    nu::Vector2 force{ 0.0f, 0.0f };
    if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_A) || nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) {
        force.x -= m_speed;
    }
    if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_D) || nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) {
        force.x += m_speed;
    }
    if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_W) || nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_UP)) {
        force.y -= m_speed;
    }
    if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_S) || nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_DOWN)) {
        force.y += m_speed;
    }

    SetVelocity(GetVelocity() + (force * dt));

    Actor::Update(dt);
}

void Player::Draw(const nu::Renderer& renderer) const {
	Actor::Draw(renderer);
}