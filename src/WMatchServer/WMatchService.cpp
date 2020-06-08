#include "WMatchService.h"
#include "Logger.h"
#include "WMatchTask.h"
#include "WMatchManager.h"
#include "Defs.h"

#define FIGHT_HIGHLOAD_PARAM 30

CWMatchServer *ServerImp()
{
    return (CWMatchServer *)g_pServerImp;
}


CWMatchServer::CWMatchServer(const std::string &name)
    :CImpServer(SERVER_TYPE_MAX, name)
{

}
    
CWMatchServer::~CWMatchServer()
{

}

void CWMatchServer::UpdateSec()
{
    WMatchManager::instance()->Update1Sec();

    return;
}

void CWMatchServer::Update5Sec()
{

}

void CWMatchServer::RemoveServer(CWMatchTask *task)
{


    return;
}

void CWMatchServer::ProxySendCmd(void *cmd, uint32_t len, uint32_t serverType, uint32_t serverId, CWMatchTask *proxyTask)
{
    Cmd::t_Server_Send_Trans_Msg* send = NULL;
    ServerCmdBuffer(send);
    memcpy(send->data, cmd, len);
    send->dataLen = len;
    send->targetServer.serverType = serverType;
    send->targetServer.serverId = serverId;
    send->srcServer.serverId = g_serverId;
    send->srcServer.serverType = SERVER_TYPE_WMATCH_SERVER;

    if (!proxyTask)
    {
        auto v = ServerImp()->GetServerTaskByType(SERVER_TYPE_PROXY_SERVER);
        for (auto &v1 : *v)
        {
            v1.second->SendCmd(send, send->Size());
            break;
        }
        
    }
    else
        proxyTask->SendCmd(send, send->Size());

    return;
}
