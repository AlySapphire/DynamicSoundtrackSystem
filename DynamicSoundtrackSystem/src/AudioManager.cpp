#include "AudioManger.hpp"

#include "AudioFile.hpp"
#include <fmod.hpp>
#include <fmod_errors.h>
#include <iostream>

#pragma region Using
using std::cout;
using std::endl;
using std::vector;
using std::string;
#pragma endregion

#pragma region typedef
typedef unsigned int uint;
#pragma endregion

namespace DSS {

	AudioManager* AudioManager::m_Instance = nullptr;

	AudioManager::AudioManager() {
	}

	AudioManager::~AudioManager() {

		//Clean up memory
		if(m_Instance != nullptr)	delete m_Instance;

	}

	bool AudioManager::Init(int p_MaxChannels) {

		//Error handle
		FMOD_RESULT result;

		//Create a system object
		result = FMOD::System_Create(&m_System);

		//Check for errors
		if(result) {
			cout << "Error Code " << result << ": " << FMOD_ErrorString(result) << endl;
			return false;
		}

		//Check we have correct version installed
		uint version;
		result = m_System->getVersion(&version);

		if(version < FMOD_VERSION) {
			cout << "ERROR! Current FMOD version not supported!" << endl;
			return false;
		}

		//Initialize our system
		result = m_System->init(p_MaxChannels, FMOD_INIT_NORMAL, 0);

		//Check for errors
		if(result) {
			cout << "Error Code " << result << ": " << FMOD_ErrorString(result) << endl;
			return false;
		}

		//Reserve space in our channels vector for the max amount of channels specified
		if(p_MaxChannels > 0)
			m_Channels.reserve(p_MaxChannels);

		return true;
	}

	void AudioManager::Shutdown() {

		FMOD_RESULT result;

		//Unload audio sources and free memory
		for(auto iter : m_AudioSources) {
			iter->Unload();
			delete iter;
		}

		//Unload system
		result = m_System->close();
		//Check for errors
		if(result) {
			cout << "Error Code " << result << ": " << FMOD_ErrorString(result) << endl;
		}

		//Release system
		result = m_System->release();
		//Check for errors
		if(result) {
			cout << "Error Code " << result << ": " << FMOD_ErrorString(result) << endl;
		}

	}

	void AudioManager::Update(float deltaTime) {

		//Update time
		m_Time += deltaTime;

		//Error handle
		FMOD_RESULT result;

		//Update the system last
		result = m_System->update();
	}

	AudioManager * AudioManager::Instance() {
		//Check for valid instance
		if(m_Instance == nullptr)
			m_Instance = new AudioManager();

		return m_Instance;

	}

}