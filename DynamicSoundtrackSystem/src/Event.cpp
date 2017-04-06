#include "Event.hpp"

#include <fmod.hpp>
#include <fmod_errors.h>
#include <chrono>
#include <thread>
#include <iostream>

#pragma region Using
using std::cout;
using std::endl;
using std::thread;
using std::chrono::milliseconds;
#pragma endregion

namespace DSS {

	Event::Event() {
	}

	Event::~Event() {
	}

	bool Event::CreateTimedEvent(unsigned int p_TimeMs, eEVENT_TYPE p_EventType, FMOD::ChannelGroup ** p_MasterGroup, FMOD::System** p_System) {
		
		//Error handle
		FMOD_RESULT result;

		FMOD::DSP* dsp;

		switch(p_EventType) {
			case eEVENT_HIGHPASS:
				result = (*p_System)->createDSPByType(FMOD_DSP_TYPE_HIGHPASS, &dsp);
				break;
			case eEVENT_LOWPASS:
				result = (*p_System)->createDSPByType(FMOD_DSP_TYPE_LOWPASS, &dsp);
				break;
			case eEVENT_ECHO:
				result = (*p_System)->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
				break;
		}
		
		//Check for errors
		if(!errCheck(result))	return false;

		result = (*p_MasterGroup)->addDSP(0, dsp);

		//Check for errors
		if(!errCheck(result))	return false;

		//Create a thread that sleeps for specified duration then removes the event
		thread timer([p_TimeMs, p_MasterGroup, dsp] {
			std::this_thread::sleep_for(milliseconds(p_TimeMs));
			
			//Error handle
			FMOD_RESULT resultThread;

			//Remove the DSP from the master channel group
			resultThread = (*p_MasterGroup)->removeDSP(dsp);

			//Check for errors
			if(resultThread)
				cout << "Error Code " << resultThread << ": " << FMOD_ErrorString(resultThread) << endl;

			//Free the memory of the DSP
			resultThread = dsp->release();

			//Check for errors
			if(resultThread)
				cout << "Error Code " << resultThread << ": " << FMOD_ErrorString(resultThread) << endl;

		});

		//Detatch the thread so it runs independently
		timer.detach();

		return true;
	}

	bool Event::errCheck(int p_ErrorCode) {
		if(p_ErrorCode) {
			cout << "Error Code " << p_ErrorCode << ": " << FMOD_ErrorString((FMOD_RESULT)p_ErrorCode) << endl;
			return false;
		}
		
		return true;
	}

}