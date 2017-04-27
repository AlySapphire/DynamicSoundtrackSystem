#pragma once

#include <vector>

namespace FMOD {

	class ChannelGroup;
	class Channel;

}

namespace DSS {

	class Submixer {
	public:
		Submixer(FMOD::ChannelGroup** p_Parent);
		virtual ~Submixer();

		//Channel modifiers
		//Mute - Singular
		void ToggleChannelMute(unsigned int p_ChannelNum);
		void MuteChannel(unsigned int p_ChannelNum);
		void UnmuteChannel(unsigned int p_ChannelNum);
		//Mute - Multiple
		void ToggleChannelMute(std::vector<unsigned int> p_ChannelNums);
		void MuteChannel(std::vector<unsigned int> p_ChannelNums);
		void UnmuteChannel(std::vector<unsigned int> p_ChannelNums);
		//Volume - Singular
		float GetVolume(unsigned int p_ChannelNum);
		void SetVolume(unsigned int p_ChannelNum, float p_Volume);
		//Volume - Multiple
		std::vector<float> GetVolume(std::vector<unsigned int> p_ChannelNums);
		void SetVolume(std::vector<unsigned int> p_ChannelNums, std::vector<float> p_Volumes);
		void SetVolume(std::vector<unsigned int> p_ChannelNums, float* p_Volumes);

	protected:

		friend class ChannelGroupManager;
		friend class Event;

		FMOD::ChannelGroup* m_Parent;
		std::vector<FMOD::Channel*> m_Channels;

		bool errCheck(int p_Error);

		void AddChannels();

	};

}