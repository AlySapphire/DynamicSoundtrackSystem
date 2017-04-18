#include "ChannelGroupManager.hpp"

#include <fmod.hpp>
#include <fmod_errors.h>
#include "AudioManager.hpp"
#include <string>
#include <iostream>

#pragma region Using
using std::cout;
using std::endl;
using std::string;
using std::vector;
#pragma endregion

namespace DSS {

	ChannelGroupManager* ChannelGroupManager::m_Instance = nullptr;

	ChannelGroupManager::ChannelGroupManager() {

		m_AudioManagerHandle = AudioManager::Instance();

	}

	ChannelGroupManager::~ChannelGroupManager() {

		//Clean up instance
		if(m_Instance != nullptr)		delete m_Instance;

	}

	ChannelGroupManager * ChannelGroupManager::Instance() {
		if(m_Instance == nullptr)
			m_Instance = new ChannelGroupManager();
		return m_Instance;
	}

	void ChannelGroupManager::ToggleChannelGroupPause(const char * p_GroupName) {

		//Error handle
		FMOD_RESULT result;

		int index = findChannelGroup(p_GroupName);

		if(index == -1) {
			cout << "Error! Invalid channel group name " << p_GroupName << endl;
			return;
		}

		bool paused;
		result = m_ChannelGroups[index]->getPaused(&paused);
		errCheck(result);
		result = m_ChannelGroups[index]->setPaused(!paused);
		errCheck(result);

	}

	void ChannelGroupManager::PlayChannelGroup(const char * p_GroupName) {

		//Error handle
		FMOD_RESULT result;

		int index = findChannelGroup(p_GroupName);

		if(index == -1) {
			cout << "Error! Invalid channel group name " << p_GroupName << endl;
			return;
		}

		result = m_ChannelGroups[index]->getPaused(false);
		errCheck(result);

	}

	void ChannelGroupManager::PauseChannelGroup(const char * p_GroupName) {

		//Error handle
		FMOD_RESULT result;

		int index = findChannelGroup(p_GroupName);

		if(index == -1) {
			cout << "Error! Invalid channel group name " << p_GroupName << endl;
			return;
		}

		result = m_ChannelGroups[index]->setPaused(true);
		errCheck(result);

	}

	int ChannelGroupManager::findChannelGroup(const char * p_ChannelGroupName) {
		
		//Error handle
		FMOD_RESULT result;

		string channelGroupName = p_ChannelGroupName;
		char* name = new char[channelGroupName.size()];

		int index = 0;

		for(auto iter : m_ChannelGroups) {
			result = iter->getName(name, channelGroupName.length());
			errCheck(result);

			int comparison = strcmp(name, p_ChannelGroupName);

			if(!comparison) {
				delete[] name;
				return index;
			}

			index++;
		}

		delete[] name;

		return -1;

	}

	bool ChannelGroupManager::errCheck(int p_Error) {
		if(p_Error) {
			cout << "Error Code " << p_Error << ": " << FMOD_ErrorString((FMOD_RESULT)p_Error) << endl;
			return false;
		}

		return true;
	}

}