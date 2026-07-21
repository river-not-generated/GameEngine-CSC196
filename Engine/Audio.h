#pragma once

#include "fmod.hpp"
#include <vector>
#include <string>

namespace nu
{
	class AudioSystem {
	public:
		void Initialize();
		void Update();
		int CreateSound(const char* fileName);
		void PlaySound(int index) const;

		void Pause();
		void Unpause();

	private:
		std::vector<FMOD::Sound*> m_sounds;
		FMOD::System* m_audio;
		bool m_paused = false;
	};
}