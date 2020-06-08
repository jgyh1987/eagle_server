#include "CentralService.h"
#include "Defs.h"
#include "TransMap.h"
#include "ServerCommand.h"
#include "CentralTask.h"

#define CLOSE_SERVER_HEARTTIME 300

CCentralServer *ServerImp()
{
    return (CCentralServer *)g_pServerImp;
}

CCentralServer::CCentralServer(const std::string &name)
    :CImpServer(SERVER_TYPE_MAX, name)
{

}
    
CCentralServer::~CCentralServer()
{

}

void CCentralServer::Update5Sec()
{
	return;
	
    uint64_t curTime = CImpServerTimeTick::currentTime.sec();
    for (auto &v : m_serverTasks)
    {
        for (auto itr = v.second.begin(); itr != v.second.end();)
        {
            if (curTime - itr->second->GetUpdateHreatTime() > CLOSE_SERVER_HEARTTIME)
            {
                LOGI("Update5Sec HreatTime Out ServerName = " << itr->second->GetServerName() << "  !!!");
                itr->second->SetNeedClose();
                CTransMapManager::instance()->RemoveTask(itr->second);
                v.second.erase(itr++);

                
            }
            else
                ++itr;
        }
    }

    return;
}
    
void CCentralServer::UpdateMin()
{
    CTransMapManager::instance()->UpdataMin();

    
    return;
}

void CCentralServer::AddCentralTask(CServerTask *task)
{
    auto itr = m_serverTasks.find(task->GetServerType());
    if (itr == m_serverTasks.end())
        m_serverTasks[task->GetServerType()][task->GetServerId()] = (CCentralTask *)task;
    else
    {
        auto itr1 = itr->second.find(task->GetServerId());
        if (itr1 != itr->second.end() && itr1->second->GetServerId() == task->GetServerId())
        {
            itr1->second->SetNeedClose();
        }

        m_serverTasks[task->GetServerType()][task->GetServerId()] = (CCentralTask *)task;
    }

    CTransMapManager::instance()->AddTask((CCentralTask *)task);

    return;
}

void CCentralServer::RemoveCentralTask(CServerTask *task)
{
    auto itr = m_serverTasks.find(task->GetServerType());
    if (itr != m_serverTasks.end())
    {
        auto itr1 = itr->second.find(task->GetServerId());
        if (itr1 != itr->second.end() && itr1->second->GetClientID() == task->GetClientID())
        {
            itr->second.erase(itr1);
            CTransMapManager::instance()->RemoveTask((CCentralTask *)task);
        }

    }

    return;
}

void CCentralServer::NotifyProxyToServer(CCentralTask *task)
{
    auto itr = m_serverTasks.find(SERVER_TYPE_PROXY_SERVER);
    if (itr == m_serverTasks.end())
        return;

    CCentralTask *server = NULL;
    for (auto &v : itr->second)
    {
        if (NULL == server)
            server = v.second;
        else
        {
            if (server->GetLoadInfo() > v.second->GetLoadInfo())
                server = v.second;
        }
    }

    if (server)
    {
        Cmd::t_Server_Info_Notify *needServer;
        ServerCmdBuffer(needServer);
        needServer->count = 1;
        needServer->len = (uint32_t)sizeof(Cmd::ServerInfoEx);
        Cmd::ServerInfoEx *ptr = (Cmd::ServerInfoEx *)needServer->data;
        *ptr = *server->GetServerInfo();
        ((Cmd::ServerInfoEx *)needServer->data)->gameServerId = ((CServerTaskEx *)task)->GetGameServerId();
        task->SendCmd(needServer, needServer->Size());

    }

    return;
}


