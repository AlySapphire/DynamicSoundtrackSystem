#pragma once

#include <vector>

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

		//Play and pause functions
		void ToggleChannelGroupPause(const char* p_GroupName);
		void PlayChannelGroup(const char* p_GroupName);
		void PauseChannelGroup(const char* p_GroupName);

	protected:

		static ChannelGroupManager* m_Instance;

		std::vector<FMOD::ChannelGroup*> m_ChannelGroups;

		int findChannelGroup(const char* p_ChannelGroupName);

		bool errCheck(int p_Error);

	};


}