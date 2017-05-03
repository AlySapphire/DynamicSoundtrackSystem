#pragma once

#include <string>

namespace FMOD {
	class Sound;
	class System;
	class Channel;
}

namespace DSS {

	class AudioFile {
	public:
		AudioFile();
		virtual ~AudioFile();

		bool Load(const char* p_Path, FMOD::System* p_System, bool p_LargeFile, unsigned int p_ChannelNum, FMOD::Channel** p_Channel);
		void Unload();

		unsigned int GetChannelNumber();

		const std::string & GetPath();
		const std::string & GetName();

		FMOD::Sound* GetHandle();

	protected:
		friend class AudioManager;

		std::string m_Path;
		std::string m_Name;

		FMOD::Sound* m_FMODHandle;

		unsigned int m_AssignedChannel;

	};


}