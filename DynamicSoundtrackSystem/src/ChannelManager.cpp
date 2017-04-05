#include "ChannelManager.hpp"

namespace DSS {

	ChannelManager* ChannelManager::m_Instance = nullptr;

	ChannelManager::ChannelManager() {
	}

	ChannelManager::~ChannelManager() {

		if(m_Instance != nullptr)	delete m_Instance;

	}

	ChannelManager * ChannelManager::Instance() {
		if(m_Instance == nullptr)
			m_Instance = new ChannelManager();
		return m_Instance;
	}

}