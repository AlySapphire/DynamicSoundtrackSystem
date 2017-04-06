#pragma once

namespace FMOD {

	class ChannelGroup;
	class System;
	class DSP;

}

namespace DSS {

	typedef enum {
		eEVENT_HIGHPASS,
		eEVENT_LOWPASS,
		eEVENT_ECHO
	}eEVENT_TYPE;

	class Event {
	public:
		Event();
		virtual ~Event();

		bool CreateTimedEvent(unsigned int p_TimeMs, eEVENT_TYPE p_EventType, FMOD::ChannelGroup** p_MasterGroup, FMOD::System** p_System);

	protected:

		bool errCheck(int p_ErrorCode);

	};

}