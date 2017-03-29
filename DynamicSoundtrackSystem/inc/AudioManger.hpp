#pragma once


namespace DSS {

	class AudioManager {
	public:
		AudioManager();
		virtual ~AudioManager();

		static AudioManager* Instance();

	protected:

		static AudioManager* m_Instance;

	};

}
