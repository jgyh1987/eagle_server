#include "ProxyService.h"
#include "Defs.h"
#include "TransMap.h"
#include "ServerCommand.h"
#include "ProxyTask.h"

CProxyServer *ServerImp()
{
    return (CProxyServer *)g_pServerImp;
}

CProxyServer::CProxyServer(const std::string &name)
    :CImpServer(SERVER_TYPE_MAX, name)
{

}
    
CProxyServer::~CProxyServer()
{

}

void CProxyServer::Update5Sec()
{
    Cmd::t_Server_Load_Notify notify;
    std::map<uint32_t, CServerTask *> *map = GetServerTaskByType(SERVER_TYPE_WGAME_SERVER);
    if (map)
        notify.loadInfo = (uint32_t)map->size();
    else
        notify.loadInfo = 0;

    map = GetServerTaskByType(SERVER_TYPE_WGATE_SERVER);
    if (map)
        notify.loadInfo += (uint32_t)map->size();

    map = GetServerTaskByType(SERVER_TYPE_LOGIC_SERVER);
    if (map)
        notify.loadInfo += (uint32_t)map->size();

    map = GetServerTaskByType(SERVER_TYPE_CHAT_SERVER);
    if (map)
        notify.loadInfo += (uint32_t)map->size();

    SendCmdToConnect(&notify, sizeof(notify), SERVER_TYPE_CENTRAL_SERVER);
}

void CProxyServer::UpdateMin()
{


    return;
}

