#include "pch.h"
#include "Audio.h"

namespace nu
{
	void AudioSystem::Initialize() {
		FMOD::System_Create(&m_audio);
		void* extradriverdata = nullptr;
		m_audio->init(32, FMOD_INIT_NORMAL, extradriverdata);
	}

	void AudioSystem::Update() {
		m_audio->update();
	}

	int AudioSystem::CreateSound(const char* fileName) {
		FMOD::Sound* sound = nullptr;
		m_audio->createSound(fileName, FMOD_DEFAULT, 0, &sound);
		m_sounds.push_back(sound);

		// returns the index of the sound for later retrieval
		return m_sounds.size() - 1;
	}

	void AudioSystem::PlaySound(int index) const {
		m_audio->playSound(m_sounds.at(index), 0, m_paused, nullptr);
	}

	void AudioSystem::Pause() {
		m_paused = true;
	}

	void AudioSystem::Unpause() {
		m_paused = false;
	}

}