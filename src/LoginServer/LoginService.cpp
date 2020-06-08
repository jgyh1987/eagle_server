#include "LoginService.h"
#include "DBConnectClient.h"
#include "LoginUdpServer.h"
#include "ServeListManager.h"
#include "LoginClientTask.h"
#include "Defs.h"
#include "AccountManager.h"
#include "LoginTask.h"

extern CLoginUdpServer *g_pUdpServer;

CLoginServer *GetServerImp()
{
    return (CLoginServer *)g_pServerImp;
}

CLoginServer::CLoginServer(const std::string &name)
    :CImpServer(SERVER_TYPE_MAX, name)
{

}
    
CLoginServer::~CLoginServer()
{

}

bool CLoginServer::CallBack()
{
    return true;

    CServerConnectClient *conncect = GetConnectClient(SERVER_TYPE_LOGIN_DATA, 0);
    if (conncect->IsFinal())
        return false;

    return CImpServer::CallBack();
}

void CLoginServer::Update()
{
    g_pUdpServer->doCmd();

    return;
}

void CLoginServer::Update5Sec()
{
    CServeListManager::instance()->UpdateServerStatus();
    CAccountManager::instance()->Update5Sec();

    uint64_t curTime = CImpServerTimeTick::currentTime.msec();
    for (auto itr = m_players.begin(); itr != m_players.end();)
    {
        if (curTime >= itr->second->GetConnectTime() + LOGINSERVER_CONNECT_MAXTIME)
        {
            if (itr->second->GetAccountInfo())
                itr->second->GetAccountInfo()->task = NULL;
            itr->second->ClearAccountInfo();
            itr->second->SetNeedClose();
            m_players.erase(itr++);
        }
        else
        {
            ++itr;
        }
    }

    return;
}

void CLoginServer::UpdateMin()
{
    CServeListManager::instance()->ReLoadConfig();

    return;
}

void CLoginServer::AddClientTask(CLoginClientTask *task)
{
    m_players[task->GetClientID()] = task;

    return ;
}

void CLoginServer::RemoveClientTask(CLoginClientTask *task)
{
    T_PlayerMap::iterator itr = m_players.find(task->GetClientID());
    if (itr != m_players.end())
    {
        if (itr->second->GetAccountInfo())
            itr->second->GetAccountInfo()->task = NULL;
        itr->second->ClearAccountInfo();
        m_players.erase(itr);
    }

    return ;
}

CLoginClientTask *CLoginServer::FindPlayer(uint32_t clientId)
{
    T_PlayerMap::iterator itr = m_players.find(clientId);
    if (itr != m_players.end())
    {
        return itr->second;
    }

    return NULL;
}

CLoginTask *CLoginServer::FindLoginTask(uint32_t gameServerId)
{
    auto itr = m_servers.find(gameServerId);
    if (itr != m_servers.end())
    {
        for (auto &itr1 : itr->second)
        {
            return itr1.second;
        }
    }

    return NULL;
}

void CLoginServer::AddLoginTask(CLoginTask *t)
{
    CLoginTask *task = FindLoginTask(t->GetGameServerId());
    if (task)
    {
        task->SetNeedClose();
    }

    m_servers[t->GetGameServerId()][0] = t;
}

void CLoginServer::RemoveLoginTask(CLoginTask *t)
{
    auto itr = m_servers.find(t->GetGameServerId());
    if (itr != m_servers.end())
    {
        for (auto itr1 = itr->second.begin(); itr1 != itr->second.end(); ++itr1)
        {
            if (itr1->second->GetClientID() == t->GetClientID())
            {
                itr->second.erase(itr1);
                return;
            }
        }
    }

    return;
}


