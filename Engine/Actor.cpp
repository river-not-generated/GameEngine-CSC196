#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "MathUtils.h"

namespace nu
{
    void Actor::Update(float dt) {
        m_transform.position += (m_velocity * dt);
        m_velocity *= 0.997f;

        m_transform.position.x = nu::math::Wrap(0.0f, 1024.0f, m_transform.position.x);
        m_transform.position.y = nu::math::Wrap(0.0f, 1080.0f, m_transform.position.y);
    }

    void Actor::Draw(const Renderer& renderer) const {
        renderer.DrawModel(m_model, m_transform);
        //renderer.SetColour(m_model.GetColour().r, m_model.GetColour().g, m_model.GetColour().b);

        //renderer.DrawFillRect(m_transform.position.x - (m_transform.scale * 0.5f)
        //    , m_transform.position.y - (m_transform.scale * 0.5f)
        //    , m_transform.scale, m_transform.scale);
    }
}