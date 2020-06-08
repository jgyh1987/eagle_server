#include "WGateConnectClient.h"
#include "Defs.h" 
#include "WGateService.h"

bool CWGateConnectClient::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
{
    Cmd::t_NullCmd *pNullCmd = (Cmd::t_NullCmd*)ptNull;
    switch (pNullCmd->cmd) 
    {
        case Cmd::CMD_SERVER_INIT:
            return ServerInitMessageParase(pNullCmd, nCmdLen);

        default:break;
    }

    return false;
}

void CWGateConnectClient::CallBackConnectSuccessImp()
{
    Cmd::t_Server_Regist_Req send;
    send.info.serverId = g_serverId;
    send.info.port = g_serverPort;
    strncpy(send.info.serverName, eagle::global["ServerName"].c_str(), sizeof(send.info.serverName));
    strncpy(send.info.serverIP, eagle::global["WGateServerTcpIP"].c_str(), sizeof(send.info.serverIP));
    send.info.serverType = SERVER_TYPE_WGATE_SERVER;
    SendCmd(&send, sizeof(send));
}

void CWGateConnectClient::CallBackConnectErrorImp()
{
    if (GetServerType() == SERVER_TYPE_PROXY_SERVER)
    {
		ServerImp()->ClearProxyServer();
    }

}

bool CWGateConnectClient::ServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch (pNullCmd->para) 
    {
        case Cmd::PARA_SERVER_REGIST_RES:
            {
                Cmd::t_Server_Regist_Res *recv = (Cmd::t_Server_Regist_Res*)pNullCmd;
                if (SUCCESS == recv->res)
                {
                    LOGI("CWGateConnectClient Regist SUCCESS ServerName = " << recv->info.serverName << " !!!");

                    if (GetServerType() == SERVER_TYPE_PROXY_SERVER)
                    {
						ServerImp()->SetProxyServer(recv->info);
                    }
                }
                else
                {
                    LOGI("CWGateConnectClient Regist ERROR ServerName = " << recv->info.serverName << " !!!");
					if (SERVER_TYPE_WGAME_SERVER == recv->info.serverType)
					{
						ServerImp()->PushNeedRemoveConnect(this);
					}
                }
                    
            }
            return true;
        case Cmd::PARA_SERVER_INFO_NOTIFY:
            {
                Cmd::t_Server_Info_Notify *recv = (Cmd::t_Server_Info_Notify*)pNullCmd;
                Cmd::ServerInfoEx *infos = (Cmd::ServerInfoEx *)recv->data;
                for (uint32_t i = 0; i < recv->count; ++i)
                {
                    if (SERVER_TYPE_WGAME_SERVER == infos[i].serverType)
                    {
                        CServerConnectClient *old = ServerImp()->GetConnectClient(infos[i].serverType, infos[i].serverId);
                        if (old)
                            ServerImp()->RemoveConnectClient(old);

                        ServerImp()->DynamicAddConnectClient(new CWGateConnectClient(infos[i].serverName, infos[i].serverType, infos[i].serverId, infos[i].serverIP, infos[i].port), true);
                    }

                    if (SERVER_TYPE_PROXY_SERVER == infos[i].serverType)
                    {
                        std::map<uint32_t, CServerConnectClient *> *map = ServerImp()->GetServerConnectByType(infos[i].serverType);
                        if (map)
                        {
                            for (auto itr = map->begin(); itr != map->end();)
                            {
                                CServerConnectClient *conn = itr->second;
                                itr++;
                                ServerImp()->RemoveConnectClient(conn);
                            }
                        }

						ServerImp()->SetProxyServer(infos[i]);
                        ServerImp()->DynamicAddConnectClient(new CWGateConnectClient(infos[i].serverName, infos[i].serverType, infos[i].serverId, infos[i].serverIP, infos[i].port), true);
                    }

                }

            }
            return true;
        case Cmd::PARA_SERVER_NOTIFY_REREGIST_MATCH:
        {
            Cmd::t_Server_Regist_Req send;
            send.info.serverId = g_serverId;
            send.info.port = g_serverPort;
            send.info.gameServerId = g_serverUdpPort;    //特殊处理 做UDP端口用
            strncpy(send.info.serverName, eagle::global["ServerName"].c_str(), sizeof(send.info.serverName));
            strncpy(send.info.serverIP, eagle::global["WGateServerTcpIP"].c_str(), sizeof(send.info.serverIP));
            send.info.serverType = SERVER_TYPE_WGATE_SERVER;
            ServerImp()->ProxySendCmd(&send, sizeof(send), SERVER_TYPE_WMATCH_SERVER, 0);
        }
        return true;
        default:
            break;
    }

    return false;
}
