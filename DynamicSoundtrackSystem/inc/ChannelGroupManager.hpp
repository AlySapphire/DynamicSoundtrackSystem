#pragma once

#include <vector>

//TODO: Add multi-tracking event support
//TODO: Add timed and modifiable events

namespace FMOD {

	class ChannelGroup;

}

namespace DSS {

	class AudioManager;

	class ChannelGroupManager {
	public:
		ChannelGroupManager();
		virtual ~ChannelGroupManager();

		static ChannelGroupManager* Instance();

		//Create a channel group
		bool CreateChannelGroup(const char* p_Name, unsigned int* p_ChannelNumbers = nullptr, unsigned int p_Count = 0);
		bool CreateChannelGroup(const char* p_Name, std::vector<unsigned int> p_ChannelNumbers);

		//Play and pause functions
		void ToggleChannelGroupPause(const char* p_GroupName);
		void PlayChannelGroup(const char* p_GroupName);
		void PauseChannelGroup(const char* p_GroupName);

		//Add channels
		bool AddChannels(const char* p_Name, std::vector<unsigned int> p_ChannelNumbers);

	protected:

		static ChannelGroupManager* m_Instance;

		std::vector<FMOD::ChannelGroup*> m_ChannelGroups;

		int findChannelGroup(const char* p_ChannelGroupName);

		bool errCheck(int p_Error);

	};


}