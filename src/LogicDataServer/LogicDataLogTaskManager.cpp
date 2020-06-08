#include "LogicDataLogTaskManager.h"
#include "LogicDataLogTask.h"

CConnectTask*  CLogicDataLogTaskManager::NewTcpTask(CListenTCPServer *listenServer)
{
    return new CLogicDataLogTask(listenServer);
}


bool CLogicDataLogTaskManager::Init()
{

    return true;
}

void CLogicDataLogTaskManager::UniqueAddExt(CConnectTask *task)
{
    return ;
}

void CLogicDataLogTaskManager::UniqueRemoveExt(CConnectTask *task)
{
    return ;
}

