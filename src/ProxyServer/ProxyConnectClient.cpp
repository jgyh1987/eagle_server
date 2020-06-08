#include "ProxyConnectClient.h"
#include "Defs.h" 
#include "ProxyService.h"
#include "HoldServerManager.h"

bool CProxyConnectClient::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
{
    Cmd::t_NullCmd *pNullCmd = (Cmd::t_NullCmd*)ptNull;
    switch (pNullCmd->cmd) 
    {
        case Cmd::CMD_SERVER_INIT:
            return ServerInitMessageParase(pNullCmd, nCmdLen);
        case Cmd::CMD_MESSAGE_TRANS:
            return TransMessageParase(pNullCmd, nCmdLen);
        default:break;
    }

    return false;
}

void CProxyConnectClient::CallBackConnectSuccessImp()
{
    Cmd::t_Server_Regist_Req send;
    send.info.serverId = g_serverId;
    send.info.port = g_serverPort;
    strncpy(send.info.serverName, eagle::global["ServerName"].c_str(), sizeof(send.info.serverName));
    strncpy(send.info.serverIP, eagle::global["ProxyServerTcpIp"].c_str(), sizeof(send.info.serverIP));
    send.info.serverType = SERVER_TYPE_PROXY_SERVER;
    SendCmd(&send, sizeof(send));
}

void CProxyConnectClient::CallBackConnectErrorImp()
{

}

bool CProxyConnectClient::ServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch (pNullCmd->para) 
    {
        case Cmd::PARA_SERVER_REGIST_RES:
            {
                Cmd::t_Server_Regist_Res *recv = (Cmd::t_Server_Regist_Res*)pNullCmd;
                if (SUCCESS == recv->res)
                {
                    LOGI("CProxyConnectClient Regist SUCCESS ServerName = " << recv->info.serverName << " !!!");

                    if (SingleProxyConnectServerType(GetServerType()))
                    {
                        HoldServerManager::instance()->HoldServerNotify(this);
                    }
                    else if (SERVER_TYPE_WMATCH_SERVER == GetServerType())
                    {
                        Cmd::t_Server_Notify_Notify_RegistMatch send;
                        auto map = ServerImp()->GetServerTaskByType(SERVER_TYPE_WGAME_SERVER);
                        if (map)
                        {
                            for (auto &v : *map)
                            {
                                v.second->SendCmd(&send, sizeof(send));
                            }
                        }

                        map = ServerImp()->GetServerTaskByType(SERVER_TYPE_WGATE_SERVER);
                        if (map)
                        {
                            for (auto &v : *map)
                            {
                                v.second->SendCmd(&send, sizeof(send));
                            }
                        }
                    }
                }    
                else
                {
                    LOGI("CProxyConnectClient Regist ERROR ServerName = " << recv->info.serverName << " !!!");
                }
                    
            }
            return true;
        case Cmd::PARA_SERVER_INFO_NOTIFY:
            {
                Cmd::t_Server_Info_Notify *recv = (Cmd::t_Server_Info_Notify*)pNullCmd;
                Cmd::ServerInfoEx *infos = (Cmd::ServerInfoEx *)recv->data;
                for (uint32_t i = 0; i < recv->count; ++i)
                {
                    if (SERVER_TYPE_WMATCH_SERVER == infos[i].serverType || (SERVER_TYPE_PROXY_SERVER == infos[i].serverType && infos[i].serverId != g_serverId) || SERVER_TYPE_LOGIC_DATA == infos[i].serverType || SERVER_TYPE_LOG_DATA == infos[i].serverType)
                    {
                        CServerConnectClient *old = ServerImp()->GetConnectClient(infos[i].serverType, infos[i].serverId);
                        if (old)
                            ServerImp()->RemoveConnectClient(old);

                        ServerImp()->DynamicAddConnectClient(new CProxyConnectClient(infos[i].serverName, infos[i].serverType, infos[i].serverId, infos[i].serverIP, infos[i].port), true);
                    }
                }

            }
            return true;
        default:
            break;
    }

    return false;
}

bool CProxyConnectClient::TransMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    return HoldServerManager::instance()->TransMessageParase(pNullCmd, nCmdLen);
}
