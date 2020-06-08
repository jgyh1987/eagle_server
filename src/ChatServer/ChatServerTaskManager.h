#ifndef _CHATSERVERMANAGER_H_
#define _CHATSERVERMANAGER_H_

#include "ServerTaskManager.h"

class CChatServerTaskManager : public CServerTaskManager
{
public:
	bool Init();

protected:
	void UniqueAddExtImp(CServerTask *task);
	void UniqueRemoveExtImp(CServerTask *task);

private:
	 CConnectTask* NewTcpTask(CListenTCPServer *);
};

#endif

