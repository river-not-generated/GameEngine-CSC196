#include "pch.h"
#include "Input.h"

#include "SDL3/SDL.h"

namespace nu {
	bool Input::Initialize() {
		int numKeys;
		const bool* keyState = SDL_GetKeyboardState(&numKeys);
		m_keyStates.resize(numKeys);

		// copy the data from keyState to m_keyStates
		std::copy(keyState, keyState + numKeys, m_keyStates.begin());
		m_prevKeyStates = m_keyStates;

		return true;
	}

	void Input::Update() {
		m_prevKeyStates = m_keyStates;
		const bool* keyState = SDL_GetKeyboardState(NULL);
		std::copy(keyState, keyState + m_keyStates.size(), m_keyStates.begin());

		m_prevButtonStates = m_buttonStates;
		m_buttonStates = SDL_GetMouseState(&m_mousePosition.x, &m_mousePosition.y);
	}

	void Input::Shutdown() {
		//
	}
}