#pragma once

#include <vector>
#include <map>

namespace FMOD {

	class ChannelGroup;
	class System;
	class DSP;
	class Channel;

}

namespace DSS {

	typedef enum {
		eDSP_EVENT,
		eMULTITRACK_EVENT,
	}eINTERNAL_EVENT_TYPE;

	struct EventData;

	class Event {
	public:
		Event();
		virtual ~Event();

		//bool CreateTimedEvent(unsigned int p_TimeMs, unsigned int p_EventType, FMOD::ChannelGroup** p_MasterGroup, FMOD::System** p_System);
		bool CreateTimedEvent(std::vector<EventData>& p_EventData);

	protected:
		
		bool errCheck(int p_ErrorCode);

		//std::vector<FMOD::DSP*> m_DSPs;
		std::map<unsigned int, FMOD::DSP*> m_DSPs;

		void CreateDSPEvent(unsigned int p_Duration, FMOD::ChannelGroup** p_MasterGroup, FMOD::System** p_System);
		void CreateMultiTrackingEvent();

		void Timer(std::vector<EventData> p_EventData);

	};

}