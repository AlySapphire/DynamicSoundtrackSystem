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

		unsigned int pos = 0;

		result = m_Channels[p_ChannelNum]->getPosition(&pos, FMOD_TIMEUNIT_MS);

		//Check for errors
		errCheck(result);

		return pos;
	}

	void ChannelManager::SetChannelLoopPoints(unsigned int p_ChannelNum, unsigned int p_Start, unsigned int p_End) {

		//Error handle
		FMOD_RESULT result;

		result = m_Channels[p_ChannelNum]->setLoopPoints(p_Start, FMOD_TIMEUNIT_MS, p_End, FMOD_TIMEUNIT_MS);

		//Check for errors
		errCheck(result);

	}

	void ChannelManager::ToggleChannelPause(unsigned int p_ChannelNum) {

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

		//Error handle
		FMOD_RESULT result;

		result = m_Channels[p_ChannelNum]->setPaused(false);
		errCheck(result);

	}

	void ChannelManager::PauseChannel(unsigned int p_ChannelNum) {

		//Error handle
		FMOD_RESULT result;

		result = m_Channels[p_ChannelNum]->setPaused(true);
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

}