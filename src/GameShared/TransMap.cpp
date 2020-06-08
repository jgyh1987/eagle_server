#include "TransMap.h"
#include "XMLParser.h"
#include "MD5.h"
#include "ToolsFun.h"
#include "Logger.h"
#include "Misc.h"
#include "ImpService.h"

CTransMapManager::CTransMapManager()
{

}

CTransMapManager::~CTransMapManager()
{

}

bool CTransMapManager::Init(const char *path)
{
    if (!path || !strlen(path))
        return false;

    m_filename = path;

    return LoadConfig();
}

void CTransMapManager::UpdataMin()
{
    LoadConfig();

    return;
}

std::vector<uint32_t> *CTransMapManager::GetNotifyServerType(uint32_t index)
{
    if (index < m_notifyMap.size())
        return &m_notifyMap[index];

    return NULL;
}

std::vector<uint32_t> *CTransMapManager::GetNeedServerType(uint32_t index)
{
    if (index < m_needMap.size())
        return &m_needMap[index];

    return NULL;
}

//private
bool CTransMapManager::LoadConfig()
{
    CXMLParser xml;
    if (!xml.loadFile(m_filename.c_str()))
    {
        LOGE("CentralServer::LoadConfig m_parser.loadFile ERROR");
        return false;
    }

    if (!xml.setCurNode("Config"))
    {
        LOGE("CentralServer::LoadConfig Config ERROR");
        return false;
    }

    if (!xml.setChildNode("ServerTypeMax"))
    {
        LOGE("CentralServer::LoadConfig ServerTypeMax ERROR");
        return false;
    }

    //CheckCondition( xml.getNodeAttrInt("typemax", &m_serverTypesMax, 0), false );
    m_notifyMap.clear();
    m_notifyMap.resize(SERVER_TYPE_MAX);
    m_needMap.clear();
    m_needMap.resize(SERVER_TYPE_MAX);
    xml.setUpNode();

    if (xml.setChildNode("ServerTypeList"))
    {
        if (xml.setChildNode("activelist"))
        {
            do
            {
                uint32_t servertype = 0;
                CheckCondition( xml.getNodeAttrInt("servertype", &servertype, 0), false );
                if (servertype && servertype < m_needMap.size())
                {
                    std::string temp;
                    CheckCondition( xml.getNodeAttrStr( "need_servertype", temp ), false );
                    std::vector<uint32_t> temp1;
                    parseStrToVecInt(temp, temp1);
                    for (uint32_t i = 0; i < temp1.size(); ++i)
                    {
                        if (temp1[i] < m_needMap.size())
                            m_needMap[servertype].push_back(temp1[i]);
                    }
                }
            }
            while ( xml.setNextNode() );
        }
        else
        {
            LOGE("CentralServer::LoadConfig activelist NULL");
        }
    }
    else
    {
        LOGE("CentralServer::LoadConfig ServerTypeList NULL");
    }

    for (uint32_t i = 0; i < m_needMap.size(); ++i)
    {
        for (uint32_t j = 0; j < m_needMap[i].size(); ++j)
        {
            bool isHave = false;
            for (uint32_t x = 0; x < m_notifyMap[m_needMap[i][j]].size(); ++x)
            {
                if (m_notifyMap[m_needMap[i][j]][x] == i)
                {
                    isHave = true;
                    break;
                }
            }
            if (!isHave)
                m_notifyMap[m_needMap[i][j]].push_back(i);
        }
    }

    return true;
}


void CTransMapManager::AddTask(CServerTaskEx *task)
{
    m_serverTasks[task->GetServerType()][task->GetGameServerId()][task->GetServerId()] = task;
}

void CTransMapManager::RemoveTask(CServerTaskEx *task)
{
    auto itr2 = m_serverTasks.find(task->GetServerType());
    if (itr2 != m_serverTasks.end())
    {
        auto itr = itr2->second.find(task->GetGameServerId());
        if (itr != itr2->second.end())
        {
            auto itr1 = itr->second.find(task->GetServerId());
            if (itr1 != itr->second.end())
            {
                if (itr1->second->GetClientID() == task->GetClientID())
                {
                    itr->second.erase(itr1);
                }
            }
        }
    }
}

void CTransMapManager::SendCmdToTask(void *ptr, uint32_t len, uint32_t serverType)
{
	for (auto itr2 = m_serverTasks.begin(); itr2 != m_serverTasks.end(); ++itr2)
	{
		if (itr2->first == serverType)
		{
			for (auto itr = itr2->second.begin(); itr != itr2->second.end(); ++itr)
			{
				for (auto itr1 = itr->second.begin(); itr1 != itr->second.end(); ++itr1)
				{
					itr1->second->SendCmd(ptr, len);
				}
				break;
			}
		}
    }
}

void CTransMapManager::TransNotifyServers(CServerTaskEx *task)
{
    uint32_t serverInfoSize = (uint32_t)sizeof(Cmd::ServerInfoEx);
    std::vector<uint32_t> *notifyServers = CTransMapManager::instance()->GetNotifyServerType(task->GetServerType());
    if (notifyServers)
    {
        Cmd::t_Server_Info_Notify *notify;
        ServerCmdBuffer(notify);

        notify->count = 1;
        notify->len = serverInfoSize;
        Cmd::ServerInfoEx *ptr = (Cmd::ServerInfoEx *)notify->data;
        *ptr = *task->GetServerInfo();
        ((Cmd::ServerInfoEx *)notify->data)->gameServerId = ((CServerTaskEx *)task)->GetGameServerId();
        for (uint32_t i = 0; i < (*notifyServers).size(); ++i)
        {
            SendCmdToTask(notify, notify->Size(), (*notifyServers)[i]);
        }
    }

    std::vector<uint32_t> *needServers = CTransMapManager::instance()->GetNeedServerType(task->GetServerType());
    if (needServers)
    {
        Cmd::t_Server_Info_Notify *notify;
        ServerCmdBuffer(notify);
        Cmd::ServerInfoEx *ptr = (Cmd::ServerInfoEx *)notify->data;

        for (uint32_t i = 0; i < (*needServers).size(); ++i)
        {
            for (auto itr2 = m_serverTasks.begin(); itr2 != m_serverTasks.end(); ++itr2)
            {
				if (itr2->first == (*needServers)[i])
				{
					for (auto itr = itr2->second.begin(); itr != itr2->second.end(); ++itr)
					{
						for (auto itr1 = itr->second.begin(); itr1 != itr->second.end(); ++itr1)
						{
							ptr[notify->count] = *itr1->second->GetServerInfo();
							ptr[notify->count].gameServerId = itr1->second->GetGameServerId();
							++notify->count;
						}
						break;
					}
				}
            }
        }
        notify->len = notify->count * serverInfoSize;

        task->SendCmd(notify, notify->Size());
    }

    return;
}

void CTransMapManager::TransRemoveServers(CServerTaskEx *task)
{
    std::vector<uint32_t> *notifyServers = CTransMapManager::instance()->GetNotifyServerType(task->GetServerType());
    if (notifyServers)
    {
        Cmd::t_Server_UnRegist_Notify notify;
        notify.serverId = task->GetServerId();
        notify.serverType = task->GetServerType();
        for (uint32_t i = 0; i < (*notifyServers).size(); ++i)
        {
            g_pServerImp->SendCmdToServerTask(&notify, sizeof(notify), (*notifyServers)[i]);
        }
    }

    return;
}

