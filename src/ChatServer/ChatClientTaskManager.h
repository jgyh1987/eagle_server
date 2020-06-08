#ifndef _CHATCLIENTTASKMANAGER_H_
#define _CHATCLIENTTASKMANAGER_H_

#include "ClientTaskManager.h"

class CChatClientTaskManager : public CClientTaskManager
{
public:
	bool Init();

protected:
	void UniqueAddExtImp(CClientTask *task);
	void UniqueRemoveExtImp(CClientTask *task);

private:
	 CConnectTask* NewTcpTask(CListenTCPServer *);
};

#endif

