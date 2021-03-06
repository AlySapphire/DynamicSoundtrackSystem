#include "AudioManager.hpp"

#include "AudioFile.hpp"
#include <fmod.hpp>
#include <fmod_errors.h>
#include <iostream>
#include "ChannelManager.hpp"
#include "Event.hpp"

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
	Event* AudioManager::m_EventSystem = nullptr;

	AudioManager::AudioManager() {

		channelManager = ChannelManager::Instance();

	}

	AudioManager::~AudioManager() {

		//Clean up memory
		if(m_Instance != nullptr)	delete m_Instance;

		if(m_EventSystem != nullptr)	delete m_EventSystem;

	}

	bool AudioManager::Init(int p_MaxChannels) {

		//Error handle
		FMOD_RESULT result;

		//Create a system object
		result = FMOD::System_Create(&m_System);
		//Check for errors
		if(!errorCheck(result))		return false;

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
		if(!errorCheck(result))		return false;

		//Create a master channel group
		result = m_System->getMasterChannelGroup(&m_MasterGroup);
		//Check for errors
		if(!errorCheck(result))		return false;

		m_EventSystem = new Event();

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
		errorCheck(result);

		//Release system
		result = m_System->release();
		//Check for errors
		errorCheck(result);

	}

	void AudioManager::Update(float deltaTime) {

		//Update time
		m_Time += deltaTime;

		//Error handle
		FMOD_RESULT result;

		//Update the system last
		result = m_System->update();
	}

	bool AudioManager::AddAudio(const char * p_Path, bool p_LargeFile) {

		AudioFile* newFile = new AudioFile();

		FMOD::Channel* channel = 0;

		if(!newFile->Load(p_Path, m_System, p_LargeFile, m_ChannelTracker, &channel)) {
			cout << "Could not add audio file " << p_Path << endl;
			delete newFile;
			return false;
		}
		
		//Increment the tracker
		m_ChannelTracker++;

		//Add our file to our list of audio sources
		m_AudioSources.push_back(newFile);

		//Add our channel
		channelManager->AddChannel(&channel);

		return true;
	}

	void AudioManager::ActivateEvents(std::vector<EventData>& p_EventData) {

		m_EventSystem->CreateTimedEvent(p_EventData);

	}

	AudioManager * AudioManager::Instance() {
		//Check for valid instance
		if(m_Instance == nullptr)
			m_Instance = new AudioManager();

		return m_Instance;

	}

	bool AudioManager::errorCheck(int p_Err) {

		//Check for errors
		if(p_Err) {
			cout << "Error Code " << p_Err << ": " << FMOD_ErrorString((FMOD_RESULT)p_Err) << endl;
			return false;
		}

		return true;

	}

}