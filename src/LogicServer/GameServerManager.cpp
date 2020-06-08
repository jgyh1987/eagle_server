#include "GameServerManager.h"

bool GameServerManager::Init()
{
	EagleLandmassManager::Init();

	for (auto l : m_landmassgrids)
	{
		l->Init(l->Id());
	}

	return true;
}
