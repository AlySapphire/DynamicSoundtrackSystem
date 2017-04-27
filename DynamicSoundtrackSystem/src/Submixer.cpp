#include "Submixer.hpp"

#include <fmod.hpp>
#include <fmod_errors.h>
#include <iostream>

#pragma region Using
using std::cout;
using std::endl;
using std::vector;
#pragma endregion

namespace DSS {

	Submixer::Submixer(FMOD::ChannelGroup** p_Parent) {

		FMOD_RESULT result;

		//Store variables passed in
		m_Parent = *p_Parent;

		//Get the number of channels the parent ChannelGroup contains
		int numChannels = 0;
		result = m_Parent->getNumChannels(&numChannels);
		errCheck(result);

		for(auto iter = 0; iter < numChannels; iter++) {
			FMOD::Channel* channel = nullptr;
			result = m_Parent->getChannel(iter, &channel);
			errCheck(result);
			m_Channels.push_back(channel);
		}

	}

	Submixer::~Submixer() {
	}

	void Submixer::ToggleChannelMute(unsigned int p_ChannelNum) {

		FMOD_RESULT result;
		bool muted = false;

		//Check channel exists
		if(p_ChannelNum > m_Channels.size()) {
			cout << "Error! Channel number " << p_ChannelNum << " does not exist." << endl;
			return;
		}

		result = m_Channels[p_ChannelNum]->getMute(&muted);
		errCheck(result);
		result = m_Channels[p_ChannelNum]->setMute(!muted);
		errCheck(result);

	}

	void Submixer::MuteChannel(unsigned int p_ChannelNum) {

		FMOD_RESULT result;

		//Check channel exists
		if(p_ChannelNum > m_Channels.size()) {
			cout << "Error! Channel number " << p_ChannelNum << " does not exist." << endl;
			return;
		}

		result = m_Channels[p_ChannelNum]->setMute(true);
		errCheck(result);

	}

	void Submixer::UnmuteChannel(unsigned int p_ChannelNum) {

		FMOD_RESULT result;

		//Check channel exists
		if(p_ChannelNum > m_Channels.size()) {
			cout << "Error! Channel number " << p_ChannelNum << " does not exist." << endl;
			return;
		}

		result = m_Channels[p_ChannelNum]->setMute(false);
		errCheck(result);

	}

	void Submixer::ToggleChannelMute(std::vector<unsigned int> p_ChannelNums) {

		FMOD_RESULT result;

		//Loop through the channels and invert the mute state
		for(auto iter : p_ChannelNums) {
			//Check channel exists
			if(iter > m_Channels.size()) {
				cout << "Error! Channel number " << iter << " does not exist." << endl;
				continue;
			}

			bool muted = false;
			
			result = m_Channels[iter]->getMute(&muted);
			errCheck(result);
			result = m_Channels[iter]->setMute(!muted);
			errCheck(result);

		}

	}

	void Submixer::MuteChannel(std::vector<unsigned int> p_ChannelNums) {

		FMOD_RESULT result;

		//Loop through the channels and mute them
		for(auto iter : p_ChannelNums) {
			//Check channel exists
			if(iter > m_Channels.size()) {
				cout << "Error! Channel number " << iter << " does not exist." << endl;
				continue;
			}
			result = m_Channels[iter]->setMute(true);
			errCheck(result);

		}

	}

	void Submixer::UnmuteChannel(std::vector<unsigned int> p_ChannelNums) {

		FMOD_RESULT result;

		//Loop through the channels and unmute them
		for(auto iter : p_ChannelNums) {
			//Check channel exists
			if(iter > m_Channels.size()) {
				cout << "Error! Channel number " << iter << " does not exist." << endl;
				continue;
			}
			result = m_Channels[iter]->setMute(false);
			errCheck(result);

		}

	}

	bool Submixer::errCheck(int p_Error) {
		if(p_Error) {
			cout << "Error Code " << p_Error << ": " << FMOD_ErrorString((FMOD_RESULT)p_Error) << endl;
			return false;
		}

		return true;
	}

	void Submixer::AddChannels() {

		FMOD_RESULT result;

		int numChannels = 0;
		result = m_Parent->getNumChannels(&numChannels);
		errCheck(result);

		for(auto iter = 0; iter < numChannels; iter++) {
			FMOD::Channel* channel = nullptr;
			result = m_Parent->getChannel(iter, &channel);
			errCheck(result);
			m_Channels.push_back(channel);
		}

	}

}