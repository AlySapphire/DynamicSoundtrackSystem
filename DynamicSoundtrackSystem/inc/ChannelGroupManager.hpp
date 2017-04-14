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

	protected:

		static ChannelGroupManager* m_Instance;

		AudioManager* m_AudioManagerHandle;

		std::vector<FMOD::ChannelGroup*> m_ChannelGroups;

	};


}