#ifndef _SCENE_BASE_TASK_H_
#define _SCENE_BASE_TASK_H_

#include "ServerTask.h"
#include "ClientTask.h"
#include "ServerConnect.h"
#include "ConstructInPlace.h"
#include "ServerCommand.h"

extern uint32_t g_gameServerId;

uint64_t GetServerObjectUid();

//
class CServerTaskEx : public CServerTask
{
public:
    CServerTaskEx(CListenTCPServer *listenServer)
        :CServerTask(listenServer), m_gameServerId(0)
    {
    }

    void Clear();

    uint32_t GetGameServerId() { return m_gameServerId; }
    void SetGameServerId(uint32_t id) { m_gameServerId = id; }

	void UpdateGameServerInfo(Cmd::ServerInfoEx *info);

protected:
    uint32_t m_gameServerId;
};

class CServerConnectClientEx : public CServerConnectClient
{
public:
    CServerConnectClientEx(const std::string &name, uint32_t serverType, uint32_t serverId, uint32_t gameServerId, const std::string &ip, const unsigned short port, uint32_t queuesize = 102400);
    ~CServerConnectClientEx();

    uint32_t GetGameServerId() { return m_gameServerId; }
    void SetGameServerId(uint32_t id) { m_gameServerId = id; }

protected:
    uint32_t m_gameServerId;
};



#endif
