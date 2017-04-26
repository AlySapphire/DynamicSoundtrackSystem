#pragma once

#include <vector>

namespace FMOD {

	class Channel;

}

namespace DSS {

	class AudioManager;

	class ChannelManager {
	public:
		ChannelManager();
		virtual ~ChannelManager();

		static ChannelManager* Instance();

		unsigned int GetChannelPlaybackPosition(unsigned int p_ChannelNum);
		void SetChannelLoopPoints(unsigned int p_ChannelNum, unsigned int p_Start, unsigned int p_End);

		//Play/Pause Functions
		void ToggleChannelPause(unsigned int p_ChannelNum);
		void PlayChannel(unsigned int p_ChannelNum);
		void PauseChannel(unsigned int p_ChannelNum);

	protected:
		friend class AudioManager;
		friend class ChannelGroupManager;

		static ChannelManager* m_Instance;

		std::vector<FMOD::Channel*> m_Channels;

		void AddChannel(FMOD::Channel** p_Channel);

		bool errCheck(int p_Error);

	};


}