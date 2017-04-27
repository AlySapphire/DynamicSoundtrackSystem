#pragma once

#include <vector>
#include <string>

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
		eDSP_HIGHPASS,
		eDSP_LOWPASS,
		eDSP_ECHO,
		eDSP_FLANGE,
		eDSP_END
	}eDSP_TYPE;

	struct EventData {

		unsigned int duration;
		bool mute;
		bool pause;
		bool fade;
		float fadeLevelStart;
		float fadeLevelEnd;
		bool volume;
		float volumeLevel;
		bool channelGroup;
		std::string channelGroupName;
		bool channelGroupOverall;
		int channelNumber;
		bool resetValues;
		eDSP_TYPE DSPType;

		float origVolume;

		EventData() : duration(0), mute(false), pause(false), fade(false), volume(false), channelGroup(false), fadeLevelStart(0.0f), 
					  fadeLevelEnd(0.0f), volumeLevel(0.0f), channelNumber(-1), channelGroupName(""), DSPType(eDSP_END), channelGroupOverall(false), 
					  resetValues(false), origVolume(0.0f) { }


	};

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
		bool CreateTimedEvent(unsigned int p_TimeMs, eDSP_TYPE p_EventType);

		ChannelManager* channelManager;

		static AudioManager* Instance();

	protected:

		friend class ChannelGroupManager;
		friend class Event;
		friend class Submixer;

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
