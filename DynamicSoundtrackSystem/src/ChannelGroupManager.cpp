#include "ChannelGroupManager.hpp"

#include <fmod.hpp>
#include <fmod_errors.h>
#include "AudioManager.hpp"
#include <string>
#include <iostream>
#include "ChannelManager.hpp"

#pragma region Using
using std::cout;
using std::endl;
using std::string;
using std::vector;
#pragma endregion

namespace DSS {

	ChannelGroupManager* ChannelGroupManager::m_Instance = nullptr;

	ChannelGroupManager::ChannelGroupManager() {

	}

	ChannelGroupManager::~ChannelGroupManager() {

		//Error handle
		FMOD_RESULT result;

		//Clean up instance
		if(m_Instance != nullptr)		delete m_Instance;

		//Free all the channel group handles

		for(auto iter : m_ChannelGroups) {
			result = iter->release();
			errCheck(result);
		}

	}

	ChannelGroupManager * ChannelGroupManager::Instance() {
		if(m_Instance == nullptr)
			m_Instance = new ChannelGroupManager();
		return m_Instance;
	}

	bool ChannelGroupManager::CreateChannelGroup(const char * p_Name, unsigned int * p_ChannelNumbers, unsigned int p_Count) {

		//Error handle
		FMOD_RESULT result;

		AudioManager* am = AudioManager::Instance();
		ChannelManager* cm = ChannelManager::Instance();

		int index = findChannelGroup(p_Name);

		if(index != -1) {
			cout << "Error! " << p_Name << " is an existing channel-group." << endl;
			return false;
		}

		//Create a channel group
		FMOD::ChannelGroup* group;
		result = am->m_System->createChannelGroup(p_Name, &group);

		//If channelgroup creation fails then return false
		if(!errCheck(result)) {
			cout << "Error! Could not create Channel-Group " << p_Name << endl;
			return false;
		}

		//Link group to master group
		result = am->m_MasterGroup->addGroup(group);

		//If linking fails then return false
		if(!errCheck(result)) {
			cout << "Error! Could not link Channel-Group " << p_Name << " to master group." << endl;
			return false;
		}
		
		//Add channels to group (if any)
		for(auto iter = 0; iter < p_Count; iter++) {

			//Safety check to avoid access violations
			if(p_ChannelNumbers[iter] > cm->m_Channels.size()) {
				cout << "Error! Channel index " << p_ChannelNumbers[iter] << " does not exist." << endl;
				return false;
			}

			result = cm->m_Channels[p_ChannelNumbers[iter]]->setChannelGroup(group);

			if(!errCheck(result)) {
				cout << "Error! Could not add Channel number";
				return false;
			}

			cm->PlayChannel(iter);

		}

		group->setPaused(true);

		m_ChannelGroups.push_back(group);
		
		return true;
	}

	bool ChannelGroupManager::CreateChannelGroup(const char * p_Name, std::vector<unsigned int> p_ChannelNumbers) {
		//Error handle
		FMOD_RESULT result;

		AudioManager* am = AudioManager::Instance();
		ChannelManager* cm = ChannelManager::Instance();

		int index = findChannelGroup(p_Name);

		if(index != -1) {
			cout << "Error! " << p_Name << " is an existing channel-group." << endl;
			return false;
		}

		//Create a channel group
		FMOD::ChannelGroup* group;
		result = am->m_System->createChannelGroup(p_Name, &group);

		//If channelgroup creation fails then return false
		if(!errCheck(result)) {
			cout << "Error! Could not create Channel-Group " << p_Name << endl;
			return false;
		}

		//Link group to master group
		result = am->m_MasterGroup->addGroup(group);

		//If linking fails then return false
		if(!errCheck(result)) {
			cout << "Error! Could not link Channel-Group " << p_Name << " to master group." << endl;
			return false;
		}

		//Add channels to group (if any)
		for(auto iter : p_ChannelNumbers) {

			//Safety check to avoid access violations
			if(iter > cm->m_Channels.size()) {
				cout << "Error! Channel index " << iter << " does not exist." << endl;
				return false;
			}

			result = cm->m_Channels[iter]->setChannelGroup(group);

			if(!errCheck(result)) {
				cout << "Error! Could not add Channel number";
				return false;
			}

			cm->PlayChannel(iter);

		}

		group->setPaused(true);

		m_ChannelGroups.push_back(group);

		return true;

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

		result = m_ChannelGroups[index]->setPaused(false);
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

	bool ChannelGroupManager::AddChannels(const char * p_Name, std::vector<unsigned int> p_ChannelNumbers) {
		
		//Error handle
		FMOD_RESULT result;

		ChannelManager* cm = ChannelManager::Instance();

		//Find channel group
		int index = findChannelGroup(p_Name);

		if(index == -1) {
			cout << "Error! Invalid channel group name " << p_Name << endl;
			return false;
		}

		for(auto iter : p_ChannelNumbers) {
			//Safety check to avoid access violations
			if(iter > cm->m_Channels.size()) {
				cout << "Error! Channel index " << iter << " does not exist." << endl;
				return false;
			}

			result = cm->m_Channels[iter]->setChannelGroup(m_ChannelGroups[index]);

			if(!errCheck(result)) {
				cout << "Error! Could not add Channel number";
				return false;
			}
		}
		
		return true;
	}

	int ChannelGroupManager::findChannelGroup(const char * p_ChannelGroupName) {
		
		//Error handle
		FMOD_RESULT result;

		string channelGroupName = p_ChannelGroupName;
		char* name = new char[channelGroupName.capacity()];

		int index = 0;

		for(auto iter : m_ChannelGroups) {
			result = iter->getName(name, channelGroupName.capacity());
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