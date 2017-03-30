#pragma once

namespace FMOD {

	class System;

}

namespace DSS {

	class AudioManager {
	public:
		AudioManager();
		virtual ~AudioManager();

		static AudioManager* Instance();

	protected:

		static AudioManager* m_Instance;
		FMOD::System* m_System;

	};

}
