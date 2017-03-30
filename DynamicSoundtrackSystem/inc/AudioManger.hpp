#pragma once

#include <vector>

namespace FMOD {

	class System;
	class Channel;

}

namespace DSS {

	class AudioFile;

	class AudioManager {
	public:
		AudioManager();
		virtual ~AudioManager();

		bool Init(int p_MaxChannels = 32);
		void Shutdown();

		void Update(float deltaTime);

		static AudioManager* Instance();

	protected:

		static AudioManager* m_Instance;
		FMOD::System* m_System;

		std::vector<AudioFile*> m_AudioSources;
		std::vector<FMOD::Channel*> m_Channels;

		float m_Time = 0.0f;
		unsigned int m_ChannelTracker = 0;

	};

}
