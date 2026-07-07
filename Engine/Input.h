#pragma once

#include "Vector2.h"

#include <vector>

namespace nu
{
	class Input {
		public:
			enum MouseButton {
				Left = 1,
				Middle = 2,
				Right = 3
			};

		public:
			bool Initialize();
			void Shutdown();

			void Update();

			bool GetKeyDown(int key) const { return m_keyStates[key]; }
			bool GetPrevKeyDown(int key) const { return m_prevKeyStates[key]; }
			// pressed: previous frame it was not pressed but now it is
			bool GetKeyPressed(int key) const { return m_keyStates[key] && !m_prevKeyStates[key]; }
			// released: previous frame it was pressed but now it's not
			bool GetKeyReleased(int key) const { return !m_keyStates[key] && m_prevKeyStates[key]; }

			bool GetMouseDown(int button) const { return false; }

			Vector2 GetMousePosition() const { return m_mousePosition; }

		private:
			// keyboard
			std::vector<bool> m_keyStates;
			std::vector<bool> m_prevKeyStates;

			// mouse
			uint32_t m_buttonStates = 0;
			uint32_t m_prevButtonStates = 0;

			Vector2 m_mousePosition{ 0, 0 };
	};
}