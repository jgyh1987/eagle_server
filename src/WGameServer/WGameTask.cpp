#include "WGameTask.h"
#include "Defs.h"
#include "TransMap.h"
#include "WGameService.h"
#include "WGamePlayer.h"

bool CWGameTask::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
{
    Cmd::t_NullCmd *pNullCmd = (Cmd::t_NullCmd*)ptNull;
    switch (pNullCmd->cmd) 
    {
        case Cmd::CMD_SERVER_INIT:
            return ServerInitMessageParase(pNullCmd, nCmdLen);
		case Cmd::CMD_MESSAGE_TRANS:
		{
			switch (pNullCmd->para)
			{
			case Cmd::PARA_SERVER_SEND_TRANS_MSG:
				return TransMsgParase((Cmd::t_Server_Send_Trans_Msg*)pNullCmd, nCmdLen);
			default:break;
			}
		}
		break;
		case Cmd::CMD_WORLD_MESSAGE:
			return WorldMessageParase(pNullCmd, nCmdLen);
        default:break;
    }

    return true;
}

bool CWGameTask::ServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch ( pNullCmd->para )
    {
    case Cmd::PARA_SERVER_REGIST_REQ:
        {
            Cmd::t_Server_Regist_Req *recv = (Cmd::t_Server_Regist_Req *)pNullCmd;
            return ServerRegistReq(recv);
        }
        return true;
	case Cmd::PARA_AGENT_SCENEID_NOTIFY:
	{
		Cmd::t_Agent_SceneId_Notify *recv = (Cmd::t_Agent_SceneId_Notify *)pNullCmd;
		return AgentSceneIdNotify(recv);
	}
	return true;
    default:
        return false;
    }

    return false;
}
    
bool CWGameTask::ServerRegistReq(Cmd::t_Server_Regist_Req *recv)
{
    Cmd::t_Server_Regist_Res send;
    send.res = SUCCESS;
    send.info.serverType = SERVER_TYPE_WGAME_SERVER;
    send.info.serverId = g_serverId;
    strncpy(send.info.serverName, eagle::global["ServerName"].c_str(), sizeof(send.info.serverName));
    do
    {
		if (!ServerImp()->UseDungeon() && SERVER_TYPE_WGATE_SERVER == recv->info.serverType)
		{
			send.res = SERVER_REGIST_ERROR;
			break;
		}
		UpdateGameServerInfo(&recv->info);
		ServerImp()->AddServerTask(this);
    }
    while (false);

    SendCmd(&send, sizeof(send));

    LOGI("CWGameTask ServerRegistReq ServerName = " << recv->info.serverName << " Res " << send.res <<  " !!!");

    return true;
}

bool CWGameTask::AgentSceneIdNotify(Cmd::t_Agent_SceneId_Notify *recv)
{
	uint64_t *ptr = (uint64_t *)recv->data;
	for (uint32_t i = 0; i < recv->count; ++i)
	{
		WGameWorldManager::instance()->RegisterServerAgentSceneId(ptr[i], recv->serverId);
	}

	return true;
}


bool CWGameTask::TransMsgParase(const Cmd::t_Server_Send_Trans_Msg* ptNull, const unsigned int nCmdLen)
{
	if (SERVER_TYPE_WGAME_SERVER == ptNull->targetServer.serverType && CLIENT_TYPE == ptNull->srcServer.serverType)
	{
		auto player = World::instance()->FindPlayerByUid((uint32_t)ptNull->uid);
		if (!player)
			return false;

		//protocol::PackageNet stream;
		//stream.ParseFromArray(ptNull->data, ptNull->dataLen);
		//uint32_t id = stream.id() / PROTOCOL_ID_MASK;

		//switch (id)
		//{
		//case 1:
		//    {
		//        return player->ParaseLoginMessage(&stream);
		//    }
		//    break;
		//case 2:
		//    {
		//        return player->ParasePlayerInfoMessage(&stream);
		//    }
		//    break;
		//case 3:
		//{
		//    return player->ParaseChatMessage(&stream);
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
		case ClientMsg::PlayerInfoCommand::MAJOR_CMD:
		{
			return GamePlayerSystem::instance()->ParasePlayerInfoMessage(player->GetEntity(), stream, message.minorCmd);
		}
		break;
		case ClientMsg::MapCommand::MAJOR_CMD:
		{
			return GamePlayerSystem::instance()->ParaseMapMessage(player->GetEntity(), stream, message.minorCmd);
		}
		break;
		default:
			break;
		}
	}

	return false;
}


bool CWGameTask::WorldMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
	switch (pNullCmd->para)
	{
	case Cmd::PARA_SCENE_AGENT_LOCK_RES:
	{
		Cmd::t_Scene_Agent_Lock_Res *recv = (Cmd::t_Scene_Agent_Lock_Res *)pNullCmd;
		
		WGamePlayer* player = World::instance()->FindPlayerByUid(recv->playerUid);
		if (player)
		{
			if (SUCCESS == recv->ret)
			{
				if (recv->lock)
					WGameWorldManager::instance()->RoamWGameServer(player, recv->serverId);
			}
			else
			{
				//todo notify player error msg
			}
		}
			
	}
	return true;
	default:
		return false;
	}


	return false;
}


