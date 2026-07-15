#include "pch.h"
#include "Engine.h"
#include "framework.h"
#include <iostream>

void fnEngine()
{
	std::cout << "engine connected" << std::endl;
}

namespace nu
{
	Engine engine;

	bool Engine::Initialize(float width, float height) {
		m_renderer.Initialize("Game Engine", width, height);
		m_input.Initialize();
		fnEngine();

		return true;
	}

	void Engine::Shutdown() {
		m_input.Shutdown();
		m_renderer.Shutdown();
	}

	void Engine::Update() {
		m_input.Update();
		m_time.Tick();
	}
}