#include "Event.hpp"

#include <fmod.hpp>
#include <fmod_errors.h>
#include <chrono>
#include <thread>
#include <iostream>
#include "AudioManager.hpp"
#include "Submixer.hpp"
#include "ChannelGroupManager.hpp"
#include "ChannelManager.hpp"
#include <algorithm>

#pragma region Using
using std::cout;
using std::endl;
using std::thread;
using std::chrono::milliseconds;
#pragma endregion

namespace DSS {

	bool compareDurations(EventData a, EventData b) {
		return (a.duration < b.duration);
	}

	Event::Event() {
	}

	Event::~Event() {

		FMOD_RESULT result;

		for(auto iter : m_DSPs) {
			result = iter.second->release();
			errCheck(result);
		}

	}

	bool Event::CreateTimedEvent(std::vector<EventData>& p_EventData) {

		AudioManager* am = AudioManager::Instance();
		ChannelGroupManager* cgm = ChannelGroupManager::Instance();
		FMOD_RESULT result;
		
		//Loop through our event data array and grab values
		for(auto iter : p_EventData) {
			
			//DSP creation
			FMOD::DSP* dsp = nullptr;
			//Make DSP if specified
			if(iter.DSPType != eDSP_END) {

				//Check for existing DSP's of the same type
				auto it = m_DSPs.find(iter.DSPType);
				//If no DSP of the type specified exists then create one
				if(it == m_DSPs.end()) {
					switch(iter.DSPType) {
						case eDSP_ECHO:
							result = am->m_System->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
							errCheck(result);
							break;
						case eDSP_FLANGE:
							result = am->m_System->createDSPByType(FMOD_DSP_TYPE_FLANGE, &dsp);
							errCheck(result);
							break;
						case eDSP_HIGHPASS:
							result = am->m_System->createDSPByType(FMOD_DSP_TYPE_HIGHPASS, &dsp);
							errCheck(result);
							break;
						case eDSP_LOWPASS:
							result = am->m_System->createDSPByType(FMOD_DSP_TYPE_LOWPASS, &dsp);
							errCheck(result);
							break;
					}

					m_DSPs.emplace(iter.DSPType, dsp);

				} else {
					dsp = it->second;
				}

			}

			//Check whether we're affecting a channelgroup
			if(iter.channelGroup) {

				int index = cgm->findChannelGroup(iter.channelGroupName.c_str());

				if(index == -1) {
					cout << "Error! Invalid ChannelGroupName " << iter.channelGroupName << endl;
					return false;
				}

				//Check if this affects the whole group
				if(iter.channelGroupOverall) {

					//Apply DSP (if any)
					if(dsp != nullptr) {
						result = cgm->m_ChannelGroups[index]->addDSP(0, dsp);
						errCheck(result);
					}

					//Add fade points (if any)
					if(iter.fade) {
						unsigned long long parentClock;
						result = cgm->m_ChannelGroups[index]->getDSPClock(nullptr, &parentClock);
						errCheck(result);
						result = cgm->m_ChannelGroups[index]->addFadePoint(parentClock, iter.fadeLevelStart);
						errCheck(result);
						result = cgm->m_ChannelGroups[index]->addFadePoint(parentClock + iter.duration, iter.fadeLevelEnd);
						errCheck(result);
					}

					//Change volume
					if(iter.volume) {
						result = cgm->m_ChannelGroups[index]->getVolume(&iter.origVolume);
						errCheck(result);
						result = cgm->m_ChannelGroups[index]->setVolume(iter.volumeLevel);
						errCheck(result);
					}

					//Mute
					if(iter.mute) {
						result = cgm->m_ChannelGroups[index]->setMute(true);
						errCheck(result);
					}

					//Pause
					if(iter.pause) {
						result = cgm->m_ChannelGroups[index]->setPaused(true);
						errCheck(result);
					}

				} else {

					Submixer* sm = cgm->GetSubmixer(iter.channelGroupName.c_str());

					//Apply DSP (if any)
					if(dsp != nullptr) {
						result = sm->m_Channels[iter.channelNumber]->addDSP(0, dsp);
						errCheck(result);
					}

					//Add fade points (if any)
					if(iter.fade) {
						unsigned long long parentClock;
						result = sm->m_Channels[iter.channelNumber]->getDSPClock(nullptr, &parentClock);
						errCheck(result);
						result = sm->m_Channels[iter.channelNumber]->addFadePoint(parentClock, iter.fadeLevelStart);
						errCheck(result);
						result = sm->m_Channels[iter.channelNumber]->addFadePoint(parentClock + iter.duration, iter.fadeLevelEnd);
						errCheck(result);
					}

					//Change volume
					if(iter.volume) {
						result = sm->m_Channels[iter.channelNumber]->getVolume(&iter.origVolume);
						errCheck(result);
						result = sm->m_Channels[iter.channelNumber]->setVolume(iter.volumeLevel);
						errCheck(result);
					}

					//Mute
					if(iter.mute) {
						result = sm->m_Channels[iter.channelNumber]->setMute(true);
						errCheck(result);
					}

					//Pause
					if(iter.pause) {
						result = sm->m_Channels[iter.channelNumber]->setPaused(true);
						errCheck(result);
					}
				}

			} else {
				ChannelManager* cm = ChannelManager::Instance();
				//Apply DSP (if any)
				if(dsp != nullptr) {
					result = cm->m_Channels[iter.channelNumber]->addDSP(0, dsp);
					errCheck(result);
				}

				//Add fade points (if any)
				if(iter.fade) {
					unsigned long long parentClock;
					result = cm->m_Channels[iter.channelNumber]->getDSPClock(nullptr, &parentClock);
					errCheck(result);
					result = cm->m_Channels[iter.channelNumber]->addFadePoint(parentClock, iter.fadeLevelStart);
					errCheck(result);
					result = cm->m_Channels[iter.channelNumber]->addFadePoint(parentClock + iter.duration, iter.fadeLevelEnd);
					errCheck(result);
				}

				//Change volume
				if(iter.volume) {
					result = cm->m_Channels[iter.channelNumber]->getVolume(&iter.origVolume);
					errCheck(result);
					result = cm->m_Channels[iter.channelNumber]->setVolume(iter.volumeLevel);
					errCheck(result);
				}

				//Mute
				if(iter.mute) {
					result = cm->m_Channels[iter.channelNumber]->setMute(true);
					errCheck(result);
				}

				//Pause
				if(iter.pause) {
					result = cm->m_Channels[iter.channelNumber]->setPaused(true);
					errCheck(result);
				}

			}

		}
		
		thread timer(&DSS::Event::Timer, this, p_EventData);
		timer.detach();

		return true;

	}

	//bool Event::CreateTimedEvent(unsigned int p_TimeMs, unsigned int p_EventType, FMOD::ChannelGroup ** p_MasterGroup, FMOD::System** p_System) {
	//	
	//	//Error handle
	//	FMOD_RESULT result;
	//
	//	FMOD::DSP* dsp;
	//
	//	switch(p_EventType) {
	//		case 0:
	//			result = (*p_System)->createDSPByType(FMOD_DSP_TYPE_HIGHPASS, &dsp);
	//			break;
	//		case 1:
	//			result = (*p_System)->createDSPByType(FMOD_DSP_TYPE_LOWPASS, &dsp);
	//			break;
	//		case 2:
	//			result = (*p_System)->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
	//			break;
	//		case 3:
	//			result = (*p_System)->createDSPByType(FMOD_DSP_TYPE_FLANGE, &dsp);
	//	}
	//	
	//	//Check for errors
	//	if(!errCheck(result))	return false;
	//
	//	result = (*p_MasterGroup)->addDSP(0, dsp);
	//
	//	//Check for errors
	//	if(!errCheck(result))	return false;
	//
	//	m_DSPs.push_back(dsp);
	//
	//	//Create a thread that sleeps for specified duration then removes the event
	//	thread timer([p_TimeMs, p_MasterGroup, dsp] {
	//		std::this_thread::sleep_for(milliseconds(p_TimeMs));
	//		
	//		//Error handle
	//		FMOD_RESULT resultThread;
	//
	//		//Remove the DSP from the master channel group
	//		resultThread = (*p_MasterGroup)->removeDSP(dsp);
	//
	//		//Check for errors
	//		if(resultThread)
	//			cout << "Error Code " << resultThread << ": " << FMOD_ErrorString(resultThread) << endl;
	//
	//		//Free the memory of the DSP
	//		resultThread = dsp->release();
	//
	//		//Check for errors
	//		if(resultThread)
	//			cout << "Error Code " << resultThread << ": " << FMOD_ErrorString(resultThread) << endl;
	//
	//	});
	//
	//	//Detatch the thread so it runs independently
	//	timer.detach();
	//
	//	return true;
	//}

	bool Event::errCheck(int p_ErrorCode) {
		if(p_ErrorCode) {
			cout << "Error Code " << p_ErrorCode << ": " << FMOD_ErrorString((FMOD_RESULT)p_ErrorCode) << endl;
			return false;
		}
		
		return true;
	}

	void DSS::Event::CreateDSPEvent(unsigned int p_Duration, FMOD::ChannelGroup ** p_MasterGroup, FMOD::System ** p_System) {

		

	}

	void Event::Timer(std::vector<EventData> p_EventData) {

		FMOD_RESULT result;

		AudioManager* am = AudioManager::Instance();
		ChannelGroupManager* cgm = ChannelGroupManager::Instance();
		ChannelManager* cm = ChannelManager::Instance();

		//Find the earliest event to toggle
		std::stable_sort(p_EventData.begin(), p_EventData.end(), compareDurations);

		int duration = (int)p_EventData.front().duration;

		for(auto iter = p_EventData.begin(); iter != p_EventData.end(); iter++) {
			if(duration > 0)
				std::this_thread::sleep_for(milliseconds(duration));
			
			//Calculate next longest duration to sleep for
			if(iter + 1 != p_EventData.end())
				duration = (int)(iter + 1)->duration - iter->duration;
			
			//Remove DSP (if any)
			if(iter->DSPType != eDSP_END) {
				auto it = m_DSPs.find(iter->DSPType);
				
				//Channel Group
				if(iter->channelGroup) {
					//Entire Channel Group
					if(iter->channelGroupOverall) {
						int index = cgm->findChannelGroup(iter->channelGroupName.c_str());
						result = cgm->m_ChannelGroups[index]->removeDSP(it->second);
						errCheck(result);
					} else {	//Individual Channel of Channel Group
						int index = cgm->findChannelGroup(iter->channelGroupName.c_str());
						Submixer* sm = cgm->GetSubmixer(iter->channelGroupName.c_str());
						result = sm->m_Channels[iter->channelNumber]->removeDSP(it->second);
						errCheck(result);
					}
				} else {	//Individual channel
					result = cm->m_Channels[iter->channelNumber]->removeDSP(it->second);
					errCheck(result);
				}

			}

			//Reset vlaues
			if(iter->resetValues) {

				//Channel Group
				if(iter->channelGroup) {
					int index = cgm->findChannelGroup(iter->channelGroupName.c_str());

					//Entire Channel Group
					if(iter->channelGroupOverall) {
						
						//Fade
						if(iter->fade) {
							unsigned long long parentClock = 0;
							result = cgm->m_ChannelGroups[index]->getDSPClock(nullptr, &parentClock);
							errCheck(result);
							result = cgm->m_ChannelGroups[index]->addFadePoint(parentClock, iter->fadeLevelEnd);
							errCheck(result);
							result = cgm->m_ChannelGroups[index]->addFadePoint(parentClock + duration, iter->fadeLevelStart);
							errCheck(result);
						}

						//Mute
						if(iter->mute) {
							result = cgm->m_ChannelGroups[index]->setMute(false);
							errCheck(result);
						}

						//Volume
						if(iter->volume) {
							result = cgm->m_ChannelGroups[index]->setVolume(iter->origVolume);
							errCheck(result);
						}

						//Pause
						if(iter->pause) {
							result = cgm->m_ChannelGroups[index]->setPaused(false);
							errCheck(result);
						}

					} else {	//Individual channel of a Channel Group

						Submixer* sm = cgm->GetSubmixer(iter->channelGroupName.c_str());

						//Fade
						if(iter->fade) {
							unsigned long long parentClock = 0;
							result = sm->m_Channels[iter->channelNumber]->getDSPClock(nullptr, &parentClock);
							errCheck(result);
							result = sm->m_Channels[iter->channelNumber]->addFadePoint(parentClock, iter->fadeLevelEnd);
							errCheck(result);
							result = sm->m_Channels[iter->channelNumber]->addFadePoint(parentClock + duration, iter->fadeLevelStart);
							errCheck(result);
						}

						//Mute
						if(iter->mute) {
							result = sm->m_Channels[iter->channelNumber]->setMute(false);
							errCheck(result);
						}

						//Volume
						if(iter->volume) {
							result = sm->m_Channels[iter->channelNumber]->setVolume(iter->origVolume);
							errCheck(result);
						}

						//Pause
						if(iter->pause) {
							result = sm->m_Channels[iter->channelNumber]->setPaused(false);
							errCheck(result);
						}

					}
				} else {	//Individual Channel

					FMOD::Channel* channel = cm->m_Channels[iter->channelNumber];

					//Fade
					if(iter->fade) {
						unsigned long long parentClock = 0;
						result = channel->getDSPClock(nullptr, &parentClock);
						errCheck(result);
						result = channel->addFadePoint(parentClock, iter->fadeLevelEnd);
						errCheck(result);
						result = channel->addFadePoint(parentClock + duration, iter->fadeLevelStart);
						errCheck(result);
					}

					//Mute
					if(iter->mute) {
						result = channel->setMute(false);
						errCheck(result);
					}

					//Volume
					if(iter->volume) {
						result = channel->setVolume(iter->origVolume);
						errCheck(result);
					}

					//Pause
					if(iter->pause) {
						result = channel->setPaused(false);
						errCheck(result);
					}

				}

			}

		}

	}

}