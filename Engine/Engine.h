#pragma once

#include "Random.h"
#include "Vector2.h"
#include "MathUtils.h"
#include "Transform.h"

#include "Renderer.h"
#include "Input.h"
#include "GameTime.h"
#include "Actor.h"
#include "Mesh.h"

namespace nu
{
	class Engine {
		public:
			Engine() = default;

			bool Initialize(float width, float height);
			void Shutdown();

			void Update();

			Input& GetInput() { return m_input; }
			Renderer& GetRenderer() { return m_renderer; }
			Time GetTime() { return m_time; }

		private:
			Input m_input;
			Renderer m_renderer;
			Time m_time;
	};

	extern Engine engine;
}



void fnEngine();