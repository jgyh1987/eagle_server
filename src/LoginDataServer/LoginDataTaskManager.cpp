#include "LoginDataTaskManager.h"
#include "LoginDataTask.h"

CConnectTask* CLoginDataTaskManager::NewTcpTask(CListenTCPServer *listenServer)
{
    return new CLoginDataTask(listenServer);
}


bool CLoginDataTaskManager::Init()
{

    return true;
}

void CLoginDataTaskManager::UniqueAddExtImp(CServerTask *task)
{

}

void CLoginDataTaskManager::UniqueRemoveExtImp(CServerTask *task)
{

}

