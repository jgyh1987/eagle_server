#include "GatewayTaskManager.h"
#include "GatewayTask.h"
#include "Session.h"
#include "PlayerManager.h"
#include "GatewayConnectClient.h"
#include "LogicLoginCommand.h"
#include "GatewayService.h"

CConnectTask* GatewayTaskManager::NewTcpTask(CListenTCPServer *listenServer)
{
    return new CGatewayTask(listenServer);
}


bool GatewayTaskManager::Init()
{

    return true;
}

void GatewayTaskManager::UniqueRemoveExtImp(CClientTask *task)
{
    LOGD("GatewayTaskManager::UniqueRemoveExtImp!!!!");
    if (((CGatewayTask*)task)->m_player)
    {
        PlayerManager::instance()->RemovePlayer(((CGatewayTask*)task)->m_player);
    }

    return ;
}

