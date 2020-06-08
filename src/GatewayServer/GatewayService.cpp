#include "GatewayService.h"
#include "GatewayTaskManager.h"
#include "GatewayUdpServer.h"
#include "Defs.h"
#include "PlayerManager.h"
#include "Action.h"
#include "GatewayConnectClient.h"

extern CGatewayUdpServer *g_pUdpServer;

CGatewayServer *ServerImp()
{
    return (CGatewayServer *)g_pServerImp;
}

CGatewayServer::CGatewayServer(const std::string &name)
    :CImpServer(SERVER_TYPE_MAX, name)
{
    SetUpdateTime(3);
}
    
CGatewayServer::~CGatewayServer()
{

}
    
bool CGatewayServer::CallBack()
{
    //return true;
    //    return CImpServer::CallBack();

    std::map<uint32_t, CServerConnectClient *> *connectVec = GetServerConnectByType(SERVER_TYPE_LOGIC_SERVER);
    if (connectVec)
    {
        for (std::map<uint32_t, CServerConnectClient *>::iterator itr = connectVec->begin(); itr != connectVec->end(); ++itr)
        {
            if (itr->second->IsInit() && itr->second->IsFinal())
                return false;
        }
    }

     return true;
}

class PlayerUpdate : public CEntryCallback<GatewayPlayer>
{
public:
    bool exec(GatewayPlayer* player)
    {
        player->Update();
        return true;
    }
};

class Player5SecUpdate : public CEntryCallback<GatewayPlayer>
{
public:
    bool exec(GatewayPlayer* player)
    {
        player->Update5Sec();
        return true;
    }
};


void CGatewayServer::Update()
{
    g_pUdpServer->doCmd();

    PlayerUpdate doCmd;
    PlayerManager::instance()->ExecEveryPlayer(doCmd);

    return;
}



void CGatewayServer::UpdateSec()
{


    return;
}

void CGatewayServer::Update5Sec()
{
    //g_playerTaskManager->SyncTimeToClinet();

    Player5SecUpdate doCmd;
    PlayerManager::instance()->ExecEveryPlayer(doCmd);


    std::map<uint32_t, CServerConnectClient *> *connectVec = GetServerConnectByType(SERVER_TYPE_LOGIN_SERVER);
    if (connectVec)
    {
        for (std::map<uint32_t, CServerConnectClient *>::iterator itr = connectVec->begin(); itr != connectVec->end(); ++itr)
        {
            ((CGatewayConnectClient *)itr->second)->SendPlayerCountToLoginServer();
        }
    }

    return;
}

void CGatewayServer::NotifyPlayerLeave(uint64_t playerId)
{
    Cmd::t_Player_Leave_Notify notify;
    notify.playerId = playerId;
    SendToLogicServer(&notify, sizeof(notify));

    return;
}
