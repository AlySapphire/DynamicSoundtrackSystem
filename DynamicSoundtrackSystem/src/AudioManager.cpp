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

		//Reserve space in our channels vector for the max amount of channels specified
		if(p_MaxChannels > 0)
			m_Channels.reserve(p_MaxChannels);

		//Create a master channel group
		result = m_System->getMasterChannelGroup(&m_MasterGroup);
		//Check for errors
		if(!errorCheck(result))		return false;

		return true;
	}

	void AudioManager::Shutdown() {

		FMOD_RESULT result;

		//Unload audio sources and free memory
		for(auto iter : m_AudioSources) {
			iter->Unload();
			delete iter;
		}

		//Release channel groups
		for(auto iter : m_ChannelGroups) {
			result = iter->release();
			errorCheck(result);
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

	bool AudioManager::AddAudio(const char * p_Path, bool p_LargeFile, unsigned int p_Mode) {

		AudioFile* newFile = new AudioFile();

		FMOD::Channel* channel = 0;

		if(!newFile->Load(p_Path, m_System, p_LargeFile, m_ChannelTracker, &channel, p_Mode)) {
			cout << "Could not add audio file " << p_Path << endl;
			delete newFile;
			return false;
		}
		
		//Increment the tracker
		m_ChannelTracker++;

		//Add our file to our list of audio sources
		m_AudioSources.push_back(newFile);

		//Add our channel
		m_Channels.push_back(channel);

		return true;
	}

	void AudioManager::ToggleChannelPause(unsigned int p_Channel) {

		//Error handle
		FMOD_RESULT result;

		bool paused;

		result = m_Channels.at(p_Channel)->getPaused(&paused);
		errorCheck(result);
		result = m_Channels.at(p_Channel)->setPaused(!paused);
		errorCheck(result);

	}

	void AudioManager::SetChannelLoopPoints(unsigned int p_ChannelIndex, unsigned int p_Start, unsigned int p_End, eTIME_UNIT p_Unit) {

		//Error handle
		FMOD_RESULT result;

		result = m_Channels[p_ChannelIndex]->setLoopPoints(p_Start, (p_Unit == eTIME_MS) ? FMOD_TIMEUNIT_MS : FMOD_TIMEUNIT_PCM, p_End, (p_Unit == eTIME_MS) ? FMOD_TIMEUNIT_MS : FMOD_TIMEUNIT_PCM);

		errorCheck(result);

	}

	bool AudioManager::CreateTimedEvent(unsigned int p_TimeMs, eEVENT_TYPE p_EventType) {
		
		//Event handle
		Event soundEvent;

		if(!soundEvent.CreateTimedEvent(p_TimeMs, p_EventType, &m_MasterGroup, &m_System)) {
			cout << "Error: Could not create event." << endl;
			return false;
		}
		
		return true;
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