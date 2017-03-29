#include "AudioManger.hpp"

namespace DSS {

	AudioManager* AudioManager::m_Instance = nullptr;

	AudioManager::AudioManager() {
	}

	AudioManager::~AudioManager() {

		//Clean up memory
		if(m_Instance != nullptr)	delete m_Instance;

	}

	AudioManager * AudioManager::Instance() {
		//Check for valid instance
		if(m_Instance == nullptr)
			m_Instance = new AudioManager();

		return m_Instance;

	}

}