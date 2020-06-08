#include "ChatClientTaskManager.h"
#include "ChatClientTask.h"
#include "ChatManager.h"

CConnectTask* CChatClientTaskManager::NewTcpTask(CListenTCPServer *listenServer)
{
	return new CChatClientTask(listenServer);
}


bool CChatClientTaskManager::Init()
{

	return true;
}

void CChatClientTaskManager::UniqueAddExtImp(CClientTask *task)
{

	return;
}

void CChatClientTaskManager::UniqueRemoveExtImp(CClientTask *task)
{
	ChatManager::instance()->DelTask((CChatClientTask *)task);

	return;
}

