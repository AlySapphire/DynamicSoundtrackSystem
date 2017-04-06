#pragma once

#include <vector>

namespace FMOD {

	class ChannelGroup;
	class System;
	class DSP;

}

namespace DSS {

	class Event {
	public:
		Event();
		virtual ~Event();

		bool CreateTimedEvent(unsigned int p_TimeMs, unsigned int p_EventType, FMOD::ChannelGroup** p_MasterGroup, FMOD::System** p_System);

	protected:

		bool errCheck(int p_ErrorCode);

		std::vector<FMOD::DSP*> m_DSPs;

	};

}