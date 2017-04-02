#pragma once

#include <vector>

namespace FMOD {

	class System;
	class Channel;
	class ChannelGroup;
}

namespace DSS {

	typedef enum {
		eTIME_MS,
		eTIME_SAMPLES
	}eTIME_UNIT;

	class AudioFile;

	class AudioManager {
	public:
		AudioManager();
		virtual ~AudioManager();

		bool Init(int p_MaxChannels = 32);
		void Shutdown();

		void Update(float deltaTime);

		//Add an audio source to the sound manager
		bool AddAudio(const char* p_Path, bool p_LargeFile, unsigned int p_Mode = 0);
		
		//Toggle the pause state of a channel
		void ToggleChannelPause(unsigned int p_Channel);

		//Set the loop points of a channel
		void SetChannelLoopPoints(unsigned int p_ChannelIndex, unsigned int p_Start, unsigned int p_End, eTIME_UNIT p_Unit);

		static AudioManager* Instance();

	protected:

		static AudioManager* m_Instance;
		FMOD::System* m_System;

		std::vector<AudioFile*> m_AudioSources;
		std::vector<FMOD::Channel*> m_Channels;
		std::vector<FMOD::ChannelGroup*> m_ChannelGroups;

		//Master channel group
		FMOD::ChannelGroup* m_MasterGroup;

		float m_Time = 0.0f;
		unsigned int m_ChannelTracker = 0;
		unsigned int m_ChannelGroupTracker = 1;

		bool errorCheck(int p_Err);

	};

}
