#include "LogicTask.h"
#include "Logger.h"
#include "Stream.h"
#include "World.h"
#include "PlayerManager.h"
#include "LogicDataCommand.h"
#include "Defs.h"
#include "LogicGateCommand.h"
#include "PTCommand.h"
#include "GM.h"
#include "OffLinePlayer.h"
#include "LogicLoginCommand.h"
#include "LogicService.h"
#include "LogicDataManager.h"
#include "WorldCommand.h"
#include "GameServerManager.h"

void CLogicTask::Clear()
{
    return CConnectTask::Clear();
}

bool CLogicTask::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
{
    Cmd::t_NullCmd *pNullCmd = (Cmd::t_NullCmd*)ptNull;
    switch (pNullCmd->cmd) 
    {
        case Cmd::CMD_SERVER_INIT:
                return ServerInitMessageParase(pNullCmd, nCmdLen);
        case Cmd::CMD_LOGIC_PLAYERINFO:
            return LogicPlayerInfoMessageParase((Cmd::t_NullCmd*)pNullCmd, nCmdLen);
        case Cmd::CMD_MESSAGE_TRANS:
            {
                switch(pNullCmd->para)
                {
                    case Cmd::PARA_SERVER_SEND_TRANS_MSG:
                        return TransMsgParase((Cmd::t_Server_Send_Trans_Msg*)pNullCmd, nCmdLen);
                    default:break;
                }
            }
            break;
        case Cmd::CMD_PT_MESSAGE:
            {
                return PTMessageParase(pNullCmd, nCmdLen);
            }
            break;
        case Cmd::CMD_LOGIN_LOGIC:
            {
            }
            break;
        default:break;
    }

    return true;
}

bool CLogicTask::ServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch ( pNullCmd->para )
    {
    case Cmd::PARA_SERVER_REGIST_REQ:
        {
            Cmd::t_Server_Regist_Req *recv = (Cmd::t_Server_Regist_Req *)pNullCmd;
			UpdateGameServerInfo(&recv->info);
            g_pServerImp->AddServerTask(this, true);

			Cmd::t_Server_Regist_Res send;
			send.info.serverId = g_serverId;
			send.info.port = g_serverPort;
			strncpy(send.info.serverName, eagle::global["ServerName"].c_str(), sizeof(send.info.serverName));
			strncpy(send.info.serverIP, eagle::global["LogicServerTcpIP"].c_str(), sizeof(send.info.serverIP));
			send.info.serverType = SERVER_TYPE_LOGIC_SERVER;
			send.info.gameServerId = g_gameServerId;
			send.res = SUCCESS;

			SendCmd(&send, sizeof(send));

            //CallbackGetPlayerChangeTask playerupdate;
            //playerupdate.task = this;
            //PlayerManager::instance()->ExecEveryPlayer(playerupdate);
        }
        return true;
    default:
        return false;
    }

    return false;
}

bool CLogicTask::LogicPlayerInfoMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch (pNullCmd->para) 
    {
        case Cmd::PARA_GET_PLAYERINFO_REQ:
            {
                Cmd::t_Get_PlayerInfo_Req *recv = (Cmd::t_Get_PlayerInfo_Req*)pNullCmd;
                LogicPlayer *player = PlayerManager::instance()->GetPlayerByAccount(recv->account);

                LOGD("Cmd::PARA_GET_PLAYERINFO_REQ ACCOUNT = " << recv->account);
                if (player)
                {
					World::instance()->DelRecoveryPlayer(player);
					World::instance()->RemovePlayer(player);
                }

                Cmd::t_Data_Get_PlayerInfo_Req send;
                strncpy(send.playerInfo.account, recv->account, MAX_ACCOUNT_LENGHT - 1);
				send.playerInfo.gatewayServerId = GetServerId();
                SendToDB(&send, sizeof(send));

                return true;
            }
        case Cmd::PARA_PLAYER_LEAVE_NOTIFY:
            {
                Cmd::t_Player_Leave_Notify *recv = (Cmd::t_Player_Leave_Notify*)pNullCmd;
                LogicPlayer *player = World::instance()->GetPlayerByID(recv->playerId);
                if (player)
                {
                    World::instance()->AddRecoveryPlayer(player);
                }

                return true;
            }
            break;
        default:
            break;
    }

    return false;
}

bool CLogicTask::TransMsgParase(const Cmd::t_Server_Send_Trans_Msg* ptNull, const unsigned int nCmdLen)
{
    if (SERVER_TYPE_LOGIC_SERVER == ptNull->targetServer.serverType && CLIENT_TYPE == ptNull->srcServer.serverType)
    {
        LogicPlayer *pPlayer = World::instance()->GetPlayerByID((uint32_t)ptNull->uid);
        if (!pPlayer)
            return false;

        //protocol::PackageNet stream;
        //stream.ParseFromArray(ptNull->data, ptNull->dataLen);
        //uint32_t id = stream.id() / PROTOCOL_ID_MASK;

        //switch (id)
        //{
        //case 1:
        //    {
        //        return pPlayer->ParaseLoginMessage(&stream);
        //    }
        //    break;
        //case 2:
        //    {
        //        return pPlayer->ParasePlayerInfoMessage(&stream);
        //    }
        //    break;
        //case 3:
        //{
        //    return pPlayer->ParaseChatMessage(&stream);
        //}
        //break;
        //default:
        //    break;
        //}

        BinaryReadStream stream((const char*)(ptNull->data), ptNull->dataLen);
        ClientMsg::Message message;
        if (message.Unserialize(&stream) != 0)
            return false;

        switch (message.majorCmd)
        {
        case ClientMsg::LoginCommand::MAJOR_CMD:
        {
            return pPlayer->ParaseLoginMessage(stream, message.minorCmd);
        }
        break;
        case ClientMsg::PlayerInfoCommand::MAJOR_CMD:
        {
            return pPlayer->ParasePlayerInfoMessage(stream, message.minorCmd);
        }
        break;
        case ClientMsg::ChatMessageCommand::MAJOR_CMD:
        {
            return pPlayer->ParaseChatMessage(stream, message.minorCmd);
        }
        break;
        case ClientMsg::WorldMessageCommand::MAJOR_CMD:
        {
            return pPlayer->ParaseWorldMessage(stream, message.minorCmd);
        }
        break;
        case ClientMsg::FriendMessageCommand::MAJOR_CMD:
        {
            return pPlayer->ParaseFriendMessage(stream, message.minorCmd, (uint8_t *)ptNull->data, ptNull->dataLen);
        }
        break;
        default:
            break;
        }    
    }
    else if (SERVER_TYPE_LOGIC_SERVER == ptNull->targetServer.serverType)
    {
        //LogicPlayer *player = World::instance()->GetPlayerByUID(ptNull->uid);
        //if (!player || !player->IsInit())
        //    return false;
    
        //Cmd::t_NullCmd* pNullCmd = (Cmd::t_NullCmd *)ptNull->data;
        //switch (pNullCmd->cmd)
        //{
        //case Cmd::CMD_SCENE_MESSAGE:
        //{
        //    return player->ParaseSceneCmd(pNullCmd);
        //}
        //break;
        //default:
        //    break;
        //}

    }

    return false;
}

bool CLogicTask::PTMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch (pNullCmd->para) 
    {
        case Cmd::PARA_PT_GM_CMD_REQ:
            {
                Cmd::t_PT_GmCmd_Req *recv = (Cmd::t_PT_GmCmd_Req *)pNullCmd;
                std::string str(recv->data, recv->len);
                LOGD("PTMessageParase PARA_PT_GM_CMD_REQ = " << str.c_str());  

                std::string out;
                GMCommandManager::instance()->parse(str.c_str(), out);
                LOGD("PTMessageParase  GMCommandManager RET = " << out.c_str());  
            }
            return true;
        default:
            break;
    }

    return false;
}


