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
#include "Scene.h"
#include "Audio.h"

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
			Time& GetTime() { return m_time; }
			AudioSystem& GetAudio() { return m_audio; }

		private:
			Input m_input;
			Renderer m_renderer;
			Time m_time;
			AudioSystem m_audio;
	};

	extern Engine engine;
}



void fnEngine();