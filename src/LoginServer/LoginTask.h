#ifndef _LOGINTASK_H_
#define _LOGINTASK_H_

#include "GameBaseTask.h"
#include "ClientMsg.h"
#include "ServerCommand.h"


class CLoginTask : public CServerTaskEx
{
public:
    CLoginTask(CListenTCPServer *listenServer)
        :CServerTaskEx(listenServer)
    {
        m_playerCount = 0;
    }

    void Clear();
    bool cmdMsgParse(void *,const uint32_t);

private:
    bool ServerCommonMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);
    bool LoginCommonMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);

public:
    void InitServerInfo(const Cmd::ServerInfoEx *pinfo);
    uint32_t GetPlayerCount() { return m_playerCount; }

private:
    uint32_t m_playerCount;

};

#endif
