#include "WGameService.h"
#include "ListenServer.h"
#include "World.h"
#include "Defs.h"

#define WFIGHTSERVER_LOAD_HIGH  50    //

CWGameServer *ServerImp()
{
    return (CWGameServer *)g_pServerImp;
}

CWGameServer::CWGameServer(const std::string &name)
    :CImpServer(SERVER_TYPE_MAX, name)
{
    m_loadHigh = 0;
}
    
CWGameServer::~CWGameServer()
{

}

void CWGameServer::Update()
{
	World::instance()->Update();

    return;
}

void CWGameServer::UpdateSec()
{
	World::instance()->UpdateSec();

    return;
}

void CWGameServer::Update5Sec()
{
    World::instance()->Update5Sec();

    //Cmd::t_Server_Load_Notify notify;
    //notify.loadInfo = 0;
    //SendCmdToConnect(&notify, sizeof(notify), SERVER_TYPE_WMATCH_SERVER);

    if (!m_proxyServer.serverId)
    {
        Cmd::t_Server_Req_ProxyServer send;
        ServerImp()->SendCmdToConnect(&send, sizeof(send), SERVER_TYPE_CENTRAL_SERVER, 0);
    }

    return;
}
    
void CWGameServer::TickLongWarn(uint32_t t)
{
    if (t >= WFIGHTSERVER_LOAD_HIGH)
        ++m_loadHigh;
    else
    {
        if (m_loadHigh)
            --m_loadHigh;
    }

    return ;
}

void CWGameServer::ProxySendCmd(void *cmd, uint32_t len, uint32_t serverType, uint32_t serverId)
{
	if (!m_proxyServer.serverId)
		return;

    Cmd::t_Server_Send_Trans_Msg* send = NULL;
    ServerCmdBuffer(send);
    memcpy(send->data, cmd, len);
    send->dataLen = len;
    send->targetServer.serverType = serverType;
    send->targetServer.serverId = serverId;
    send->srcServer.serverId = g_serverId;
    send->srcServer.serverType = SERVER_TYPE_WGAME_SERVER;

    SendCmdToConnect(send, send->Size(), SERVER_TYPE_PROXY_SERVER, m_proxyServer.serverId);

    return;
}

void CWGameServer::ClearProxyServer()
{
	m_proxyServer.Clear();

	return;
}



