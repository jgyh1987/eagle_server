#include "GatewayConnectClient.h"
#include "Stream.h"
#include "Defs.h"
#include "ServerCommand.h"
#include "LogicLoginCommand.h"
#include "ClientMsg.h"
#include "SessionManager.h"
#include "PlayerManager.h"
#include "LogicGateCommand.h"
#include "GatewayTask.h"
#include "ImpService.h"
#include "GatewayService.h"
#include "WorldCommand.h"

class PlayerSendCmdCB : public CEntryCallback<GatewayPlayer>
{
public:
    void *data;
    uint32_t len;

    bool exec(GatewayPlayer* player)
    {
        player->SendCmd(data, len);
        return true;
    }
};

bool CGatewayConnectClient::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
{
    Cmd::t_NullCmd *pNullCmd = (Cmd::t_NullCmd*)ptNull;
    switch (pNullCmd->cmd) 
    {
        case Cmd::CMD_SERVER_INIT:
            return ServerInitMessageParase(pNullCmd, nCmdLen);
        case Cmd::CMD_LOGIN_LOGIC:
            return LoginServerMessageParase(pNullCmd, nCmdLen);
        case Cmd::CMD_LOGIC_PLAYERINFO:
            return LogicServerMessageParase(pNullCmd, nCmdLen);
        case Cmd::CMD_MESSAGE_TRANS:
            return TransMsgParase(pNullCmd, nCmdLen);
        case Cmd::CMD_WORLD_MESSAGE:
            return WorldMessageParase(pNullCmd, nCmdLen);
        default:break;
    }

    return false;
}

void CGatewayConnectClient::SendPlayerCountToLoginServer()
{
    Cmd::t_Send_Server_PlayerCount_Notify send;
    send.serverId = g_serverId;
    send.playerCount = PlayerManager::instance()->Size();
    SendCmd(&send, sizeof(send));
    
    return;
}

void CGatewayConnectClient::CallBackConnectSuccessImp()
{
    Cmd::t_Server_Regist_Req send;
    send.info.serverId = g_serverId;
    send.info.port = g_serverPort;
    strncpy(send.info.serverName, eagle::global["ServerName"].c_str(), sizeof(send.info.serverName));
    strncpy(send.info.serverIP, eagle::global["GateServerTcpIP"].c_str(), sizeof(send.info.serverIP));
    send.info.serverType = SERVER_TYPE_LOGIC_GATEWAY;
    send.info.gameServerId = g_gameServerId;

    switch (GetServerType())
    {
    case SERVER_TYPE_LOGIC_SERVER:
        break;
    case SERVER_TYPE_LOGIN_SERVER:
        break;
    default:
        break;
    }

    SendCmd(&send, sizeof(send));

    return;
}
    
void CGatewayConnectClient::CallBackConnectErrorImp()
{

    return;
}

bool CGatewayConnectClient::ServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch (pNullCmd->para) 
    {
        case Cmd::PARA_SERVER_REGIST_RES:
            {
                //
                Cmd::t_Server_Regist_Res *recv = (Cmd::t_Server_Regist_Res *)pNullCmd;
                if (SUCCESS == recv->res)
                    LOGI("GateServer PARA_SERVER_REGIST_RES SUCCESS = " << recv->info.serverName << "   !!!");
                else
                    LOGE("GateServer PARA_SERVER_REGIST_RES ERROR SERVERNAME = " << recv->info.serverName << "   !!!");
            }
            return true;
		case Cmd::PARA_SERVER_INFO_NOTIFY:
		{
			Cmd::t_Server_Info_Notify* recv = (Cmd::t_Server_Info_Notify*)pNullCmd;
			Cmd::ServerInfoEx* infos = (Cmd::ServerInfoEx*)recv->data;
			for (uint32_t i = 0; i < recv->count; ++i)
			{
				if (SERVER_TYPE_WGAME_SERVER == infos[i].serverType && g_gameServerId == infos[i].gameServerId)
				{
					CServerConnectClient* old = ServerImp()->GetConnectClient(infos[i].serverType, infos[i].serverId);
					if (old)
						ServerImp()->RemoveConnectClient(old);

					ServerImp()->DynamicAddConnectClient(new CGatewayConnectClient(infos[i].serverType, infos[i].serverId, infos[i].serverName, infos[i].serverIP, infos[i].port), true);
				}
			}

		}
		return true;
        default:
            break;
    }

    return false;
}

bool CGatewayConnectClient::LoginServerMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch (pNullCmd->para) 
    {
        case Cmd::PARA_SEND_SESSION_SYNC:        //login选择服务器需要发送session到gateway(验证用)
            {
                Cmd::t_Send_Session_Sync *recv = (Cmd::t_Send_Session_Sync *)pNullCmd;

                AccountSession *oldSession = AccountSessionManager::instance()->GetAccountSession(recv->account);
                if (oldSession)
                {
                    oldSession->session = recv->session;
                    oldSession->TickOldPlayer();    
                }
                else
                {
                    AccountSession *session = new AccountSession(recv->session, recv->account);
                    if (!session)
                    {
                        return false;
                    }
                    AccountSessionManager::instance()->AddSessionAccount(session);
                }

                Cmd::t_Send_Session_Sync_Res send;
                bcopy(recv->account, send.account, MAX_ACCOUNT_LENGHT);
                SendCmd(&send, sizeof(send));
            }
            return true;
        case Cmd::PARA_PACKAGECODE_REWARD_RES:
            {
                SendToLoginServer((void *)pNullCmd, nCmdLen);
            }
            return true;
        default:
            break;
    }

    return false;
}

bool CGatewayConnectClient::TransMsgParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch (pNullCmd->para)
    {
    case Cmd::PARA_SERVER_SEND_TRANS_MSG:
    {
        Cmd::t_Server_Send_Trans_Msg *recv = (Cmd::t_Server_Send_Trans_Msg *)pNullCmd;

        if (CLIENT_TYPE == recv->targetServer.serverType)
        {
            if (recv->uid)
            {
                GatewayPlayer *player = PlayerManager::instance()->GetPlayerByTempID(recv->uid);
                if (!player)
                    return false;

                player->SendCmd(recv->data, recv->dataLen);
            }
            else
            {
                PlayerSendCmdCB cb;
                cb.data = recv->data;
                cb.len = recv->dataLen;
                PlayerManager::instance()->ExecEveryPlayer(cb);
            }
        }
        else if (SERVER_TYPE_CHAT_SERVER == recv->targetServer.serverType)
        {
        }

        return true;
    }
    break;
    default:
        break;
    }

    return false;
}


bool CGatewayConnectClient::LogicServerMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch (pNullCmd->para)
    {
    case Cmd::PARA_GET_PLAYERINFO_RES:
        return GetPlayerInfoRes(pNullCmd, nCmdLen);
    case Cmd::PARA_PLAYER_KICK_NOTIFY:
    {
        return PlayerKickNotify(pNullCmd, nCmdLen);
    }
    break;
    default:
        break;
    }

    return false;
}

bool CGatewayConnectClient::GetPlayerInfoRes(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    Cmd::t_Get_PlayerInfo_Res *recv = (Cmd::t_Get_PlayerInfo_Res *)pNullCmd;

    LOGD("CLogicConnectClient::GetPlayerInfoRes");
    ////test code begin
    //AccountSession *session1 = new AccountSession(recv->account, recv->account);
    //AccountSessionManager::instance()->AddSessionAccount(session1);
    //GatewayPlayer *tempPlayer = new GatewayPlayer(recv->playerinfo.playerId, recv->playerinfo.playerUid, recv->playerinfo.account, recv->playerinfo.account, NULL);
    //if (!tempPlayer)
    //    return false;

    //if (!PlayerManager::instance()->AddPlayer(tempPlayer))
    //{
    //    delete tempPlayer;
    //    return false;
    //}

    ////test code end

    AccountSession *session = AccountSessionManager::instance()->GetAccountSession(recv->playerinfo.account);
    if (!session || !session->task)
    {
        LOGFMTE("CLogicConnectClient::GetPlayerInfoRes error session null");
        return false;
    }

    if (session->task->RegistPlayer(recv->playerinfo, session))
    {
        if (SUCCESS == recv->ret)
        {

        }
    }
    else
    {
    }

    return true;
}


//
bool CGatewayConnectClient::PlayerKickNotify(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    Cmd::t_Player_Kick_Notify *recv = (Cmd::t_Player_Kick_Notify *)pNullCmd;
    LOGFMTE("gateway t_Player_kick_Res playerId:%llu", recv->playerId);

    GatewayPlayer *player = PlayerManager::instance()->GetPlayerByID(recv->playerId);
    if (!player)
    {
        LOGFMTT("t_Player_kick_Res  player null, playerId:%llu", recv->playerId);
        return false;
    }

    //ClientMsg::KickPlayerNotify send;
    //send.ret = recv->ret;
    //player->SendClientMsg(&send);

    PlayerManager::instance()->RemovePlayer(player, false);

    return true;
}


bool CGatewayConnectClient::WorldMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch (pNullCmd->para)
    {
	case Cmd::PARA_SCENE_AGENT_LOCK:
	{
		Cmd::t_Scene_Agent_Lock_Req* recv = (Cmd::t_Scene_Agent_Lock_Req*)pNullCmd;
		GatewayPlayer* player = PlayerManager::instance()->GetPlayerByTempID(recv->playerUid);
		Cmd::t_Scene_Agent_Lock_Res send;
		send.lock = recv->lock;
		send.ret = DEFAULT_ERROR;
		do
		{
			if (player)
			{
				if (recv->lock)
				{
					if (player->GetAgentLock())
						break;

					player->SetAgentServerId(recv->serverId);
					player->SetAgentLock(true);

					send.ret = SUCCESS;
					break;
				}
				else
				{
					if (player->GetAgentServerId() != recv->serverId && player->GetAgentServerId())
						break;

					player->SetAgentLock(false);
					player->SetAgentServerId(recv->serverId);

					send.ret = SUCCESS;
				}
			}

		} while (false);

		send.playerUid = recv->playerUid;
		send.serverId = recv->serverId;
		SendCmd(&send, sizeof(send));

		return true;
	}
    default:
        break;
    }

    return false;
}

