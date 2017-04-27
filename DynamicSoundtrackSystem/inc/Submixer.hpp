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

	protected:

		friend class ChannelGroupManager;

		FMOD::ChannelGroup* m_Parent;
		std::vector<FMOD::Channel*> m_Channels;

		bool errCheck(int p_Error);

		void AddChannels();

	};

}