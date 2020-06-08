#include "WMatchTaskManager.h"
#include "WMatchTask.h"
#include "World.h"
#include "WMatchService.h"
#include "Defs.h"

CConnectTask* CWMatchTaskManager::NewTcpTask(CListenTCPServer *listenServer)
{
    return new CWMatchTask(listenServer);
}


bool CWMatchTaskManager::Init()
{

    return true;
}

void CWMatchTaskManager::UniqueAddExtImp(CServerTask *task)
{
    if (!task)
        return;


    return ;
}

void CWMatchTaskManager::UniqueRemoveExtImp(CServerTask *task)
{
    if (!task)
        return;



    ServerImp()->RemoveServer((CWMatchTask *)task);

    return ;
}


