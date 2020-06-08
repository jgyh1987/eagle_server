#include "HoldServerManager.h"
#include "ServerCommand.h"
#include "ProxyTask.h"
#include "ProxyConnectClient.h"
#include "ProxyService.h"

HoldServerManager::HoldServerManager()
{

}

HoldServerManager::~HoldServerManager()
{

}

void HoldServerManager::HoldServerNotify(CProxyTask *task)
{
    Cmd::t_HoldServer_Notify *notify;
    ServerCmdBuffer(notify);
    Cmd::ServerInfoEx *ptr = (Cmd::ServerInfoEx *)notify->data;
    *ptr = *task->GetServerInfo();
    ((Cmd::ServerInfoEx *)notify->data)->gameServerId = task->GetGameServerId();
    notify->count = 1;
    notify->len = (uint32_t)sizeof(Cmd::ServerInfoEx);

    ServerImp()->SendCmdToConnect(notify, notify->Size(), SERVER_TYPE_PROXY_SERVER);

    return;
}

void HoldServerManager::HoldServerNotify(CProxyConnectClient *conn)
{
    Cmd::t_HoldServer_Notify *notify;
    ServerCmdBuffer(notify);
    uint32_t serverInfoSize = (uint32_t)sizeof(Cmd::ServerInfoEx);
    Cmd::ServerInfoEx *ptr = (Cmd::ServerInfoEx *)notify->data;
    std::map<uint32_t, CServerTask *> *map = ServerImp()->GetServerTaskByType(SERVER_TYPE_LOGIC_SERVER);
    if (map)
    {
        for (auto &v : *map)
        {    
            ptr[notify->count] = *v.second->GetServerInfo();
            ptr[notify->count].gameServerId = ((CProxyTask *)v.second)->GetGameServerId();
            ++notify->count;
        }
    }

    map = ServerImp()->GetServerTaskByType(SERVER_TYPE_WGAME_SERVER);
    if (map)
    {
        for (auto &v : *map)
        {
            ptr[notify->count] = *v.second->GetServerInfo();
            ptr[notify->count].gameServerId = ((CProxyTask *)v.second)->GetGameServerId();
            ++notify->count;
        }
    }

    map = ServerImp()->GetServerTaskByType(SERVER_TYPE_CHAT_SERVER);
    if (map)
    {
        for (auto &v : *map)
        {
            ptr[notify->count] = *v.second->GetServerInfo();
            ptr[notify->count].gameServerId = ((CProxyTask *)v.second)->GetGameServerId();
            ++notify->count;
        }
    }

    notify->len = notify->count * serverInfoSize;

    conn->SendCmd(notify, notify->Size());


    return;
}

bool HoldServerManager::UpdateHoldMap(Cmd::t_HoldServer_Notify *recv, CProxyTask *holdTask)
{
    Cmd::ServerInfoEx *infos = (Cmd::ServerInfoEx *)recv->data;
    for (uint32_t i = 0; i < recv->count; ++i)
    {
        if (SingleProxyConnectServerType(infos[i].serverType))
        {
            m_proxyHoldMap[infos[i].serverType][infos[i].serverId] = holdTask;
        }
    }

    return true;
}

void HoldServerManager::HoldMapDelTask(CProxyTask *task)
{
    for (auto &v : m_proxyHoldMap)
    {
        for (auto itr = v.second.begin(); itr != v.second.end();)
        {
            if (itr->second == task)
            {
                v.second.erase(itr++);
            }
            else
            {
                ++itr;
            }
        }
        
    }

    return;
}

void HoldServerManager::SendCmd(Cmd::t_Server_Send_Trans_Msg *recv, uint32_t len)
{
    if (recv->targetServer.serverId)
    {
        CProxyTask *task = (CProxyTask *)ServerImp()->GetServerTask(recv->targetServer.serverType, recv->targetServer.serverId);
        if (task)
            task->SendCmd(recv->data, recv->dataLen);
        else
        {
            auto itr = m_proxyHoldMap.find(recv->targetServer.serverType);
            if (itr != m_proxyHoldMap.end())
            {
                auto itr1 = itr->second.find(recv->targetServer.serverId);
                if (itr1 != itr->second.end())
                {
                    itr1->second->SendCmd(recv, len);
                }
            }
        }
    }
    else
    {
        auto map = ServerImp()->GetServerTaskByType(recv->targetServer.serverType);
        for (auto &itr : *map)
        {
            itr.second->SendCmd(recv->data, recv->dataLen);
        }

        auto itr = m_proxyHoldMap.find(recv->targetServer.serverType);
        if (itr != m_proxyHoldMap.end())
        {
            for (auto &v : itr->second)
            {
                recv->targetServer.serverId = v.first;
                v.second->SendCmd(recv, len);
            }
        }

    }

    return;
}

bool HoldServerManager::TransMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch (pNullCmd->para)
    {
    case Cmd::PARA_SERVER_SEND_TRANS_MSG:
    {
        Cmd::t_Server_Send_Trans_Msg *recv = (Cmd::t_Server_Send_Trans_Msg *)pNullCmd;
        switch (recv->targetServer.serverType)
        {
        case SERVER_TYPE_WMATCH_SERVER:
        {
            ServerImp()->SendCmdToConnect(recv->data, recv->dataLen, SERVER_TYPE_WMATCH_SERVER);
        }
        break;
		case SERVER_TYPE_LOGIC_DATA:
		{
			ServerImp()->SendCmdToConnect(recv->data, recv->dataLen, SERVER_TYPE_LOGIC_DATA, recv->targetServer.serverId);
		}
		break;
        case SERVER_TYPE_WGAME_SERVER:
        case SERVER_TYPE_LOGIC_SERVER:
        case SERVER_TYPE_CHAT_SERVER:
        {
            HoldServerManager::instance()->SendCmd(recv, nCmdLen);
        }
        break;
        default:
            break;
        }
    }
    return true;
    default:
        return false;
    }

    return false;
}

void HoldServerManager::CheckHoldMapByServerType(uint32_t serverType)
{
    auto itr = m_proxyHoldMap.find(serverType);
    if (itr == m_proxyHoldMap.end())
    {
        m_proxyHoldMap[serverType] = std::map<uint32_t, CProxyTask *>();
    }

    return;
}

