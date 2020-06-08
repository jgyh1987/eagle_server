#include "ProxyTaskManager.h"
#include "ProxyTask.h"
#include "TransMap.h"
#include "ProxyService.h"
#include "HoldServerManager.h"
#include "Defs.h"

CConnectTask* CProxyTaskManager::NewTcpTask(CListenTCPServer *listenServer)
{
    return new CProxyTask(listenServer);
}

bool CProxyTaskManager::Init()
{

    return true;
}

void CProxyTaskManager::UniqueAddExtImp(CServerTask *task)
{

}

void CProxyTaskManager::UniqueRemoveExtImp(CServerTask *task)
{
    HoldServerManager::instance()->HoldMapDelTask((CProxyTask *)task);

    LOGI("CProxyTaskManager::UniqueRemoveExtImp ServerName = " << task->GetServerName() << " !!!");

}

