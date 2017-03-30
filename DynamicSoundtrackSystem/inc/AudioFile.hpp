#pragma once

#include <string>

namespace FMOD {
	class Sound;
	class System;
}

namespace DSS {

	class AudioFile {
	public:
		AudioFile();
		virtual ~AudioFile();

		bool Load(const char* p_Path, FMOD::System* p_System, bool p_LargeFile, unsigned int p_Mode = 0);
		void Unload(FMOD::System* p_System);

	protected:

		std::string m_Path;
		std::string m_Name;

		FMOD::Sound* m_FMODHandle;


	};


}