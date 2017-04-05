#pragma once

#include <vector>

namespace FMOD {

	class Channel;

}

namespace DSS {

	class ChannelManager {
	public:
		ChannelManager();
		virtual ~ChannelManager();

		static ChannelManager* Instance();

		//bool AddChannel();

	protected:

		static ChannelManager* m_Instance;

		std::vector<FMOD::Channel*> m_Channels;

	};


}