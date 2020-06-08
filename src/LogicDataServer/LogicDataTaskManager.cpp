#include "LogicDataTaskManager.h"
#include "LogicDataTask.h"

CConnectTask*  CLogicDataTaskManager::NewTcpTask(CListenTCPServer *listenServer)
{
    return new CLogicDataTask(listenServer);
}


bool CLogicDataTaskManager::Init()
{

    return true;
}

void CLogicDataTaskManager::UniqueAddExtImp(CServerTask *task)
{

}

void CLogicDataTaskManager::UniqueRemoveExtImp(CServerTask *task)
{

}


