#pragma once

#include "Actor.h"

class Enemy : public nu::Actor {
public:
	Enemy() = default;
	Enemy(float speed, const nu::Transform& transform) : Actor{ transform } {
		m_speed = speed;
	}
	Enemy(float speed, const nu::Transform& transform, const nu::Model& model)
		: Actor{ transform, model } {
		m_speed = speed;
	}

	void Update(float dt) override;
	void Draw(const class nu::Renderer& renderer) const override;

	float GetSpeed() { return m_speed; }

private:
	int m_ammo = 0;
	float m_speed = 400.0f;
};