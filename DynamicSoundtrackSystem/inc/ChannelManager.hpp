#pragma once

namespace DSS {

	class ChannelManager {
	public:
		ChannelManager();
		virtual ~ChannelManager();

		static ChannelManager* Instance();

	protected:

		static ChannelManager* m_Instance;

	};


}