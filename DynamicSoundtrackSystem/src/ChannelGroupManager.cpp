#include "ChannelGroupManager.hpp"

#include <fmod.hpp>
#include <fmod_errors.h>

namespace DSS {

	ChannelGroupManager* ChannelGroupManager::m_Instance = nullptr;

	ChannelGroupManager::ChannelGroupManager() {
	}

	ChannelGroupManager::~ChannelGroupManager() {

		//Clean up instance
		if(m_Instance != nullptr)		delete m_Instance;

	}

	ChannelGroupManager * ChannelGroupManager::Instance() {
		if(m_Instance == nullptr)
			m_Instance = new ChannelGroupManager();
		return m_Instance;
	}

}