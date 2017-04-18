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

		//Play and pause functions
		void ToggleChannelGroupPause(const char* p_GroupName);
		void PlayChannelGroup(const char* p_GroupName);
		void PauseChannelGroup(const char* p_GroupName);

	protected:

		static ChannelGroupManager* m_Instance;

		AudioManager* m_AudioManagerHandle;

		std::vector<FMOD::ChannelGroup*> m_ChannelGroups;

		int findChannelGroup(const char* p_ChannelGroupName);

		bool errCheck(int p_Error);

	};


}