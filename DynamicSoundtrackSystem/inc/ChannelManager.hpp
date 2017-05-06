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
		bool isPaused(unsigned int p_ChannelNum);

		//Volume controls
		float GetVolume(unsigned int p_ChannelNum);
		void SetVolume(unsigned int p_ChannelNum);

		//Mute controls
		void ToggleMute(unsigned int p_ChannelNum);
		bool isMuted(unsigned int p_ChannelNum);
		void Mute(unsigned int p_ChannelNum);
		void Unmute(unsigned int p_ChannelNum);

	protected:
		friend class AudioManager;
		friend class ChannelGroupManager;
		friend class Event;

		static ChannelManager* m_Instance;

		std::vector<FMOD::Channel*> m_Channels;

		void AddChannel(FMOD::Channel** p_Channel);

		bool errCheck(int p_Error);
		bool CheckBounds(unsigned int p_ChannelNum);

	};


}