#include "AudioFile.hpp"
#include <fmod.hpp>
#include <fmod_errors.h>
#include <iostream>

#pragma region Using
using std::string;
using std::cout;
using std::endl;
#pragma endregion

namespace DSS {

	AudioFile::AudioFile() : m_FMODHandle(nullptr) {

	}

	AudioFile::~AudioFile() {
	}

	bool AudioFile::Load(const char * p_Path, FMOD::System * p_System, bool p_LargeFile, unsigned int p_ChannelNum, FMOD::Channel** p_Channel) {
		
		FMOD_RESULT result;

		//Store the path
		m_Path = p_Path;

		//Load the sound
		switch(p_LargeFile) {
			case true:
				result = p_System->createStream(p_Path, FMOD_LOOP_NORMAL, 0, &m_FMODHandle);
				break;
			case false:
				result = p_System->createSound(p_Path, FMOD_LOOP_NORMAL, 0, &m_FMODHandle);
				break;
		}
		
		//Check for errors
		if(result) {
			cout << "Error Code " << result << ": " << FMOD_ErrorString(result) << endl;
			return false;
		}
		
		//Start the sound paused so we can alter the attributes without it being audible
		result = p_System->playSound(m_FMODHandle, 0, true, p_Channel);

		//Check for errors
		if(result) {
			cout << "Error Code " << result << ": " << FMOD_ErrorString(result) << endl;
			return false;
		}

		//Get the file name
		unsigned int start = m_Path.find_last_of("/\\");
		if(start != string::npos) {
			m_Name = m_Path.substr(start + 1);
		} else {
			m_Name = m_Path;
		}

		m_AssignedChannel = p_ChannelNum;

		return true;
	}

	void AudioFile::Unload() {

		FMOD_RESULT result;

		//Free the memory
		result = m_FMODHandle->release();

		//Check for errors
		if(result)
			cout << "Error Code " << result << ": " << FMOD_ErrorString(result) << endl;

	}

	unsigned int AudioFile::GetChannelNumber() {
		return m_AssignedChannel;
	}

	const std::string & AudioFile::GetPath() {
		return m_Path;
	}

	const std::string & AudioFile::GetName() {
		return m_Name;
	}

	FMOD::Sound * AudioFile::GetHandle() {
		return m_FMODHandle;
	}

}

