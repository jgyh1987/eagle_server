#include "LogicConnectClient.h"
#include "Defs.h" 
#include "LogicService.h"
#include "GameServerManager.h"

bool CLogicConnectClient::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
{
    Cmd::t_NullCmd *pNullCmd = (Cmd::t_NullCmd*)ptNull;
    switch (pNullCmd->cmd) 
    {
        case Cmd::CMD_SERVER_INIT:
            return ServerInitMessageParase(pNullCmd, nCmdLen);
		case Cmd::CMD_WORLD_MESSAGE:
			return WorldMessageParase(pNullCmd, nCmdLen);

        default:break;
    }

    return false;
}

void CLogicConnectClient::CallBackConnectSuccessImp()
{
    Cmd::t_Server_Regist_Req send;
    send.info.serverId = g_serverId;
    send.info.port = g_serverPort;
    strncpy(send.info.serverName, eagle::global["ServerName"].c_str(), sizeof(send.info.serverName));
    strncpy(send.info.serverIP, eagle::global["LogicServerTcpIP"].c_str(), sizeof(send.info.serverIP));
    send.info.serverType = SERVER_TYPE_LOGIC_SERVER;
    SendCmd(&send, sizeof(send));


}

void CLogicConnectClient::CallBackConnectErrorImp()
{

}

bool CLogicConnectClient::ServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch (pNullCmd->para) 
    {
		case Cmd::PARA_SERVER_REGIST_REQ:
			{
				Cmd::t_Server_Regist_Req* recv = (Cmd::t_Server_Regist_Req*)pNullCmd;
				LOGI("CLogicConnectClient Regist ERROR ServerName = " << recv->info.serverName << " !!!");
			}
			return true;
        case Cmd::PARA_SERVER_REGIST_RES:
            {
                Cmd::t_Server_Regist_Res *recv = (Cmd::t_Server_Regist_Res*)pNullCmd;
                if (SUCCESS == recv->res)
                {
					if (SERVER_TYPE_PROXY_SERVER == recv->info.serverType)
					{
						Cmd::t_Server_Notify_RegistLogic send;
						ServerImp()->ProxySendCmd(&send, sizeof(send), SERVER_TYPE_WGAME_SERVER, 0);

						Cmd::t_Server_Info_Notify* notify;
						ServerCmdBuffer(notify);

						notify->count = 2;
						notify->len = (uint32_t)sizeof(Cmd::ServerInfoEx) * 2;
						Cmd::ServerInfoEx* ptr = (Cmd::ServerInfoEx*)notify->data;

						ptr[0].serverId = g_gameServerId;//如果是分服模式， 填逻辑服务器ID（一个逻辑服 只有一个DB DBSERVERID 即GAMESERVERID ） ， 如果是大服模式 填自己服务器ID （LOGIC和DB单线相连， SERVERID一至）。 如有特殊再改。 
						ptr[0].port = g_connectLogicDataServerPort;
						ptr[0].serverType = SERVER_TYPE_LOGIC_DATA;
						sprintf(ptr[0].serverName, "LogicDataServer%d", g_gameServerId);
						strcpy(ptr[0].serverIP, eagle::global["ConnectLogicDataServerIP"].c_str());

						ptr[1].serverId = g_gameServerId;//同上
						ptr[1].port = g_connectLogDataServerPort;
						ptr[1].serverType = SERVER_TYPE_LOG_DATA;
						sprintf(ptr[1].serverName, "LogDataServer%d", g_gameServerId);
						strcpy(ptr[1].serverIP, eagle::global["ConnectLogicLogDataServerIP"].c_str());

						SendCmd(notify, notify->Size());
					}

                }    
                else
                {
                    LOGI("CLogicConnectClient Regist ERROR ServerName = " << recv->info.serverName << " !!!");
                }
                    
            }
            return true;
        case Cmd::PARA_SERVER_INFO_NOTIFY:
            {
                Cmd::t_Server_Info_Notify *recv = (Cmd::t_Server_Info_Notify*)pNullCmd;
                Cmd::ServerInfoEx *infos = (Cmd::ServerInfoEx *)recv->data;
                for (uint32_t i = 0; i < recv->count; ++i)
                {
                    if (SERVER_TYPE_PROXY_SERVER == infos[i].serverType )
                    {
                        CServerConnectClient *old = ServerImp()->GetConnectClient(infos[i].serverType, infos[i].serverId);
                        if (old)
                            ServerImp()->RemoveConnectClient(old);

                        ServerImp()->DynamicAddConnectClient(new CLogicConnectClient(infos[i].serverName, infos[i].serverType, infos[i].serverId, infos[i].serverIP, infos[i].port), true);
                    }

                }

            }
            return true;
        case Cmd::PARA_SERVER_INIT_TEST_MSG:
            {
                LOGI("t_ServerInit_Test_Msg LOGIC SERVER !!!");
            }
			return true;;
		case Cmd::PARA_AGENT_SCENEID_NOTIFY:
			{
				Cmd::t_Agent_SceneId_Notify* recv = (Cmd::t_Agent_SceneId_Notify*)pNullCmd;

				uint64_t *ptr = (uint64_t *)recv->data;
				for (uint32_t i = 0; i < recv->count; ++i)
				{
					GameServerManager::instance()->RegisterServerAgentSceneId(ptr[i], recv->serverId);
				}
			}
			return true;
        default:
            break;
    }

    return false;
}

bool CLogicConnectClient::WorldMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
	switch (pNullCmd->para)
	{
	case Cmd::PARA_REQ_SCENESERVER:
	{
		Cmd::t_Req_SceneServer* recv = (Cmd::t_Req_SceneServer*)pNullCmd;

		Cmd::t_Res_SceneServer send;
		send.funType = recv->funType;
		send.playerUid = recv->playerUid;
		EaglePos pos(recv->pos);
		send.serverId = GameServerManager::instance()->GetServerIdByMapId(recv->mapId, pos);

		ServerImp()->ProxySendCmd(&send, sizeof(send), recv->serverType, recv->serverId);
	}
	return true;
	default:
		break;
	}

	return false;
}


