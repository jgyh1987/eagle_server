#include "ChatServerTaskManager.h"
#include "ChatServerTask.h"

CConnectTask* CChatServerTaskManager::NewTcpTask(CListenTCPServer *listenServer)
{
	return new CChatServerTask(listenServer);
}


bool CChatServerTaskManager::Init()
{

	return true;
}

void CChatServerTaskManager::UniqueAddExtImp(CServerTask *task)
{
	
	return;
}

void CChatServerTaskManager::UniqueRemoveExtImp(CServerTask *task)
{

	return;
}

