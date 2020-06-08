#include "CentralTaskManager.h"
#include "CentralTask.h"
#include "TransMap.h"
#include "CentralService.h"
#include "Defs.h"

CConnectTask* CCentralTaskManager::NewTcpTask(CListenTCPServer *listenServer)
{
    return new CCentralTask(listenServer);
}

bool CCentralTaskManager::Init()
{

    return true;
}

void CCentralTaskManager::UniqueAddExtImp(CServerTask *task)
{
    ((CCentralTask *)task)->UpdateHreatTime();
}

void CCentralTaskManager::UniqueRemoveExtImp(CServerTask *task)
{
    LOGI("CCentralTaskManager::UniqueRemoveExtImp ServerName = " << task->GetServerName() << "  !!!");
    ServerImp()->RemoveCentralTask(task);
    
}

