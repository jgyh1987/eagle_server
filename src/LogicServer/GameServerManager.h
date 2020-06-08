#ifndef _GAMESERVER_MANAGER_H_ 
#define _GAMESERVER_MANAGER_H_

#include "Sys.h"
#include "Singleton.h"
#include "ServerCommand.h"
#include "LandmassManager.h"

class GameServerManager : public EagleLandmassManager, public CSingleton<GameServerManager>
{
public:
	bool Init();

private:


};

#endif    


