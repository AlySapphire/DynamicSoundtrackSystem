#pragma once

#include <vector>

namespace FMOD {

	class ChannelGroup;

}

namespace DSS {

	class ChannelGroupManager {
	public:
		ChannelGroupManager();
		virtual ~ChannelGroupManager();

		static ChannelGroupManager* Instance();

	protected:

		static ChannelGroupManager* m_Instance;

		std::vector<FMOD::ChannelGroup*> m_ChannelGroups;

	};


}