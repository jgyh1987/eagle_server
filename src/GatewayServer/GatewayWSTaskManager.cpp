#include "GatewayWSTaskManager.h"
#include "GatewayWSTask.h"

CConnectTask* GatewayWSTaskManager::NewTcpTask(CListenTCPServer *listenServer)
{
    return new CGatewayWSTask(listenServer);
}


bool GatewayWSTaskManager::Init()
{

    return true;
}

void GatewayWSTaskManager::UniqueRemoveExtImp(CClientTask *task)
{


    return ;
}

