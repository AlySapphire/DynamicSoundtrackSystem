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

	typedef enum {
		eEVENT_HIGHPASS,
		eEVENT_LOWPASS,
		eEVENT_ECHO,
		eEVENT_FLANGE
	}eEVENT_TYPE;

	class AudioFile;
	class ChannelManager;

	class AudioManager {
	public:
		AudioManager();
		virtual ~AudioManager();

		bool Init(int p_MaxChannels = 32);
		void Shutdown();

		void Update(float deltaTime);

		//Add an audio source to the sound manager
		bool AddAudio(const char* p_Path, bool p_LargeFile, unsigned int p_Mode = 0);
		
		//Create a timed event
		bool CreateTimedEvent(unsigned int p_TimeMs, eEVENT_TYPE p_EventType);

		ChannelManager* channelManager;

		static AudioManager* Instance();

	protected:

		friend class ChannelGroupManager;

		static AudioManager* m_Instance;
		FMOD::System* m_System;

		std::vector<AudioFile*> m_AudioSources;

		//Master channel group
		FMOD::ChannelGroup* m_MasterGroup;

		float m_Time = 0.0f;
		unsigned int m_ChannelTracker = 0;
		unsigned int m_ChannelGroupTracker = 1;

		bool errorCheck(int p_Err);

	};

}
