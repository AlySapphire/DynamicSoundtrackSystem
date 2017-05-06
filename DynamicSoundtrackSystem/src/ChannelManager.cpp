#include "ChannelManager.hpp"

#include <fmod.hpp>
#include <fmod_errors.h>
#include <iostream>

#pragma region Using
using std::cout;
using std::endl;
#pragma endregion

namespace DSS {

	ChannelManager* ChannelManager::m_Instance = nullptr;

	ChannelManager::ChannelManager() {
	}

	ChannelManager::~ChannelManager() {

		if(m_Instance != nullptr)	delete m_Instance;

	}

	ChannelManager * ChannelManager::Instance() {
		if(m_Instance == nullptr)
			m_Instance = new ChannelManager();
		return m_Instance;
	}

	unsigned int ChannelManager::GetChannelPlaybackPosition(unsigned int p_ChannelNum) {

		//Error handle
		FMOD_RESULT result;
		unsigned int pos = -1;

		if(!CheckBounds(p_ChannelNum))	return pos;

		result = m_Channels[p_ChannelNum]->getPosition(&pos, FMOD_TIMEUNIT_MS);

		//Check for errors
		errCheck(result);

		return pos;
	}

	void ChannelManager::SetChannelLoopPoints(unsigned int p_ChannelNum, unsigned int p_Start, unsigned int p_End) {

		if(!CheckBounds(p_ChannelNum))	return;

		//Error handle
		FMOD_RESULT result;

		result = m_Channels[p_ChannelNum]->setLoopPoints(p_Start, FMOD_TIMEUNIT_MS, p_End, FMOD_TIMEUNIT_MS);

		//Check for errors
		errCheck(result);

	}

	void ChannelManager::ToggleChannelPause(unsigned int p_ChannelNum) {

		if(!CheckBounds(p_ChannelNum))	return;

		//Error handle
		FMOD_RESULT result;
		bool paused;

		//Get the current pause state and invert it
		result = m_Channels[p_ChannelNum]->getPaused(&paused);
		errCheck(result);
		result = m_Channels[p_ChannelNum]->setPaused(!paused);
		errCheck(result);

	}

	void ChannelManager::PlayChannel(unsigned int p_ChannelNum) {

		if(!CheckBounds(p_ChannelNum))	return;

		//Error handle
		FMOD_RESULT result;

		result = m_Channels[p_ChannelNum]->setPaused(false);
		errCheck(result);

	}

	void ChannelManager::PauseChannel(unsigned int p_ChannelNum) {

		if(!CheckBounds(p_ChannelNum))	return;

		//Error handle
		FMOD_RESULT result;

		result = m_Channels[p_ChannelNum]->setPaused(true);
		errCheck(result);

	}

	bool ChannelManager::isPaused(unsigned int p_ChannelNum) {
		
		if(!CheckBounds(p_ChannelNum))	return false;

		FMOD_RESULT result;
		bool paused = false;
		
		result = m_Channels[p_ChannelNum]->getPaused(&paused);
		errCheck(result);

		return paused;

	}

	float ChannelManager::GetVolume(unsigned int p_ChannelNum) {

		if(!CheckBounds(p_ChannelNum))	return -1.0f;

		FMOD_RESULT result;
		float volume = -1.0f;

		result = m_Channels[p_ChannelNum]->getVolume(&volume);
		errCheck(result);

		return volume;
	}

	void ChannelManager::SetVolume(unsigned int p_ChannelNum, float p_Volume) {

		if(!CheckBounds(p_ChannelNum))	return;

		FMOD_RESULT result;

		result = m_Channels[p_ChannelNum]->setVolume(p_Volume);
		errCheck(result);

	}

	void ChannelManager::ToggleMute(unsigned int p_ChannelNum) {

		if(!CheckBounds(p_ChannelNum))	return;

		FMOD_RESULT result;
		bool muted = false;

		result = m_Channels[p_ChannelNum]->getMute(&muted);
		errCheck(result);
		result = m_Channels[p_ChannelNum]->setMute(!muted);
		errCheck(result);

	}

	bool ChannelManager::isMuted(unsigned int p_ChannelNum) {

		if(!CheckBounds(p_ChannelNum))	return false;

		FMOD_RESULT result;
		bool muted = false;

		result = m_Channels[p_ChannelNum]->getMute(&muted);
		errCheck(result);

		return muted;
	}

	void ChannelManager::Mute(unsigned int p_ChannelNum) {

		if(!CheckBounds(p_ChannelNum))	return;

		FMOD_RESULT result;

		result = m_Channels[p_ChannelNum]->setMute(true);
		errCheck(result);

	}

	void ChannelManager::Unmute(unsigned int p_ChannelNum) {

		if(!CheckBounds(p_ChannelNum))	return;

		FMOD_RESULT result;

		result = m_Channels[p_ChannelNum]->setMute(true);
		errCheck(result);

	}

	void ChannelManager::AddChannel(FMOD::Channel ** p_Channel) {

		m_Channels.push_back(*p_Channel);
		
	}

	bool ChannelManager::errCheck(int p_Error) {

		if(p_Error) {
			cout << "Error Code " << p_Error << ": " << FMOD_ErrorString((FMOD_RESULT)p_Error) << endl;
			return false;
		}

		return true;
	}

	bool ChannelManager::CheckBounds(unsigned int p_ChannelNum) {
		
		if(p_ChannelNum >= m_Channels.size() || m_Channels.empty()) {
			cout << "Error! Invalid Channel index " << p_ChannelNum << endl;
			return false;
		}

		return true;

	}

}