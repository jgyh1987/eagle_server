#include "WGateClientTaskManager.h"
#include "WGateClientTask.h"
#include "Defs.h"
#include "WGateService.h"

CConnectTask* CWGateClientTaskManager::NewTcpTask(CListenTCPServer *listenServer)
{
    return new CWGateClientTask(listenServer);
}


bool CWGateClientTaskManager::Init()
{

    return true;
}

void CWGateClientTaskManager::UniqueAddExtImp(CClientTask *task)
{


    return;
}

void CWGateClientTaskManager::UniqueRemoveExtImp(CClientTask *task)
{

    return;
}


