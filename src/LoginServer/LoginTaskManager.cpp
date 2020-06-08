#include "LoginTaskManager.h"
#include "LoginTask.h"
#include "LoginService.h"

CConnectTask* LoginTaskManager::NewTcpTask(CListenTCPServer *listenServer)
{
    return new CLoginTask(listenServer);
}


bool LoginTaskManager::Init()
{

    return true;
}

void LoginTaskManager::UniqueAddExtImp(CServerTask *task)
{
    
    return;
}

void LoginTaskManager::UniqueRemoveExtImp(CServerTask *task)
{
    GetServerImp()->RemoveLoginTask((CLoginTask *)task);

    return;
}

