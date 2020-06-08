#include "WGameTaskManager.h"
#include "WGameTask.h"
#include "WGameService.h"

CConnectTask* CWGameTaskManager::NewTcpTask(CListenTCPServer *listenServer)
{
    return new CWGameTask(listenServer);
}

bool CWGameTaskManager::Init()
{

    return true;
}

void CWGameTaskManager::UniqueAddExtImp(CServerTask *task)
{

}

void CWGameTaskManager::UniqueRemoveExtImp(CServerTask *task)
{


}

