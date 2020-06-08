#include "ProxyTask.h"
#include "Defs.h"
#include "TransMap.h"
#include "ProxyService.h"
#include "HoldServerManager.h"
#include "ProxyConnectClient.h"

bool CProxyTask::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
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

    return true;
}

bool CProxyTask::ServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch ( pNullCmd->para )
    {
    case Cmd::PARA_SERVER_REGIST_REQ:
        {
            Cmd::t_Server_Regist_Req *recv = (Cmd::t_Server_Regist_Req *)pNullCmd;
            return ServerRegistReq(recv);
        }
        return true;
    case Cmd::PARA_HOLDSERVER_NOTIFY:
        {
            Cmd::t_HoldServer_Notify *recv = (Cmd::t_HoldServer_Notify *)pNullCmd;
            return HoldServerManager::instance()->UpdateHoldMap(recv, this);
        }
        return true;
	case Cmd::PARA_SERVER_INFO_NOTIFY:
	{
		Cmd::t_Server_Info_Notify* recv = (Cmd::t_Server_Info_Notify*)pNullCmd;
		Cmd::ServerInfoEx* infos = (Cmd::ServerInfoEx*)recv->data;
		for (uint32_t i = 0; i < recv->count; ++i)
		{
			if (SERVER_TYPE_LOGIC_DATA == infos[i].serverType)
			{
				CServerConnectClient* old = ServerImp()->GetConnectClient(infos[i].serverType, infos[i].serverId);
				if (old)
					ServerImp()->RemoveConnectClient(old);

				ServerImp()->DynamicAddConnectClient(new CProxyConnectClient(infos[i].serverName, infos[i].serverType, infos[i].serverId, infos[i].serverIP, infos[i].port), true);
			}

		}

	}
	return true;
    default:
        return false;
    }

    return false;
}
    
bool CProxyTask::ServerRegistReq(Cmd::t_Server_Regist_Req *recv)
{
    Cmd::t_Server_Regist_Res send;
    send.res = SUCCESS;
    send.info.serverType = SERVER_TYPE_PROXY_SERVER;
    send.info.serverId = g_serverId;
    strncpy(send.info.serverName, eagle::global["ServerName"].c_str(), sizeof(send.info.serverName));
    do
    {
		UpdateGameServerInfo(&recv->info);

        ServerImp()->AddServerTask(this, true);

        LOGI("CProxyTask ServerRegistReq ServerName = " << recv->info.serverName << " !!!");
    }
    while (false);

    SendCmd(&send, sizeof(send));

	if (SERVER_TYPE_WGAME_SERVER == GetServerType())
	{
		Cmd::t_Server_Notify_Notify_RegistMatch send1;
		SendCmd(&send1, sizeof(send1));

		Cmd::t_Server_Notify_RegistLogic send2;
		SendCmd(&send2, sizeof(send2));
	}

	if (SERVER_TYPE_WGATE_SERVER == GetServerType())
	{
		Cmd::t_Server_Notify_Notify_RegistMatch send1;
		SendCmd(&send1, sizeof(send1));
	}

	if (SERVER_TYPE_LOGIC_SERVER == GetServerType())
	{
		Cmd::t_Server_Notify_RegistLogic send2;
		auto map = ServerImp()->GetServerTaskByType(SERVER_TYPE_WGAME_SERVER);
		if (map)
		{
			for (auto& v : *map)
			{
				v.second->SendCmd(&send2, sizeof(send2));
			}
		}
	}

    if (SingleProxyConnectServerType(GetServerType()))
    {
        HoldServerManager::instance()->HoldServerNotify(this);
    }

    return true;
}

bool CProxyTask::TransMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    return HoldServerManager::instance()->TransMessageParase(pNullCmd, nCmdLen);
}



