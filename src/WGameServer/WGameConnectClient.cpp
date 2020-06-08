#include "WGameConnectClient.h"
#include "Defs.h" 
#include "WGameService.h"
#include "WorldCommand.h"
#include "WGamePlayer.h"

bool CWGameConnectClient::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
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

void CWGameConnectClient::CallBackConnectSuccessImp()
{
    Cmd::t_Server_Regist_Req send;
    send.info.serverId = g_serverId;
    send.info.port = g_serverPort;
    strncpy(send.info.serverName, eagle::global["ServerName"].c_str(), sizeof(send.info.serverName));
    strncpy(send.info.serverIP, eagle::global["WGameServerTcpIP"].c_str(), sizeof(send.info.serverIP));
    send.info.serverType = SERVER_TYPE_WGAME_SERVER;
	send.info.gameServerId = g_gameServerId;
    SendCmd(&send, sizeof(send));
}

void CWGameConnectClient::CallBackConnectErrorImp()
{
    if (GetServerType() == SERVER_TYPE_PROXY_SERVER)
    {
        ServerImp()->ClearProxyServer();
    }

    return;
}

bool CWGameConnectClient::ServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch (pNullCmd->para) 
    {
        case Cmd::PARA_SERVER_REGIST_RES:
            {
                Cmd::t_Server_Regist_Res *recv = (Cmd::t_Server_Regist_Res*)pNullCmd;
                if (SUCCESS == recv->res)
                {
                    LOGI("CWGameConnectClient Regist SUCCESS ServerName = " << recv->info.serverName << " !!!");

                    if (GetServerType() == SERVER_TYPE_PROXY_SERVER)
                    {
						ServerImp()->SetProxyServer(recv->info);

						//test code
						ServerImp()->DynamicAddConnectClient(new CWGameConnectClient(eagle::global["ServerName"].c_str(), SERVER_TYPE_WGAME_SERVER, g_serverId, eagle::global["WGameServerTcpIP"].c_str(), g_serverPort), true);
                    }
					else if (GetServerType() == SERVER_TYPE_WGAME_SERVER)
					{
						WGameWorldManager::instance()->NotityServerAgentSceneId(this);
					}
                }
                else
                {
                    LOGI("CWGameConnectClient Regist ERROR ServerName = " << recv->info.serverName << " !!!");
                }
                    
            }
            return true;
        case Cmd::PARA_SERVER_INFO_NOTIFY:
            {
                Cmd::t_Server_Info_Notify *recv = (Cmd::t_Server_Info_Notify*)pNullCmd;
                Cmd::ServerInfoEx *infos = (Cmd::ServerInfoEx *)recv->data;
                for (uint32_t i = 0; i < recv->count; ++i)
                {
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
                        ServerImp()->DynamicAddConnectClient(new CWGameConnectClient(infos[i].serverName, infos[i].serverType, infos[i].serverId, infos[i].serverIP, infos[i].port), true);
                    }
					else if (SERVER_TYPE_WGAME_SERVER == infos[i].serverType)
					{
						if (infos[i].serverId != g_serverId && g_gameServerId && infos[i].gameServerId == g_gameServerId)
						{
							CServerConnectClient* old = ServerImp()->GetConnectClient(infos[i].serverType, infos[i].serverId);
							if (old)
								ServerImp()->RemoveConnectClient(old);

							ServerImp()->DynamicAddConnectClient(new CWGameConnectClient(infos[i].serverName, infos[i].serverType, infos[i].serverId, infos[i].serverIP, infos[i].port), true);
						}	
					}

                }

            }
            return true;
        case Cmd::PARA_SERVER_INIT_TEST_MSG:
            {
                Cmd::t_ServerInit_Test_Msg *recv = (Cmd::t_ServerInit_Test_Msg *)pNullCmd;
                ServerImp()->ProxySendCmd(recv, nCmdLen, SERVER_TYPE_LOGIC_SERVER, recv->serverId);

                LOGI("t_ServerInit_Test_Msg WFIGHT SERVER !!!");
            }
            break;
        case Cmd::PARA_SERVER_NOTIFY_REREGIST_MATCH:
        {
			if (ServerImp()->UseDungeon())
			{
				Cmd::t_Server_Regist_Req send;
				send.info.serverId = g_serverId;
				send.info.port = g_serverPort;
				strncpy(send.info.serverName, eagle::global["ServerName"].c_str(), sizeof(send.info.serverName));
				strncpy(send.info.serverIP, eagle::global["WGameServerTcpIP"].c_str(), sizeof(send.info.serverIP));
				send.info.serverType = SERVER_TYPE_WGAME_SERVER;
				ServerImp()->ProxySendCmd(&send, sizeof(send), SERVER_TYPE_WMATCH_SERVER, 0);
			}
        }
        return true;
		case Cmd::PARA_SERVER_NOTIFY_REREGIST_LOGIC:
		{
			if (ServerImp()->UseBigWorld())
				WGameWorldManager::instance()->NotityServerAgentSceneId(NULL, SERVER_TYPE_LOGIC_SERVER);
		}
		return true;
        default:
            break;
    }

    return false;
}

bool CWGameConnectClient::WorldMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
	switch (pNullCmd->para)
	{
	case Cmd::PARA_ENTER_WORD_REQ:
	{
		Cmd::t_Enter_World_Req* recv = (Cmd::t_Enter_World_Req*)pNullCmd;

		WGamePlayer* player = World::instance()->CreatePlayer(recv->playerinfo, SERVER_TYPE_LOGIC_GATEWAY);
		ClientMsg::EnterWorldRes send;
		if (!player->UnSerializeWithWorld(recv))
		{
			send.ret = DEFAULT_ERROR;
			GamePlayerSystem::instance()->SendClientMsg(player->GetEntity(), &send);
			SAFE_DELETE(player);

			return false;
		}

		WGameWorldManager::instance()->AgentUnLockGate(player, g_serverId);

		if (recv->enterType)
		{
			send.ret = SUCCESS;
			player->SerializeEnterWorldRes(&send);
			GamePlayerSystem::instance()->SendClientMsg(player->GetEntity(), &send);
			player->SyncEnterWorldMsg();
		}

		WGameWorldManager::instance()->EnterWorld(player);

	}
	return true;
	case Cmd::PARA_RES_SCENESERVER:
	{
		Cmd::t_Res_SceneServer* recv = (Cmd::t_Res_SceneServer*)pNullCmd;
		WGamePlayer* player = World::instance()->FindPlayerByUid(recv->playerUid);
		//eagle 需要处理无缝
		if (player)
			WGameWorldManager::instance()->ResSceneServer(player, recv->serverId, recv->funType);
	}
	return true;
	default:
		break;
	}

	return false;
}


