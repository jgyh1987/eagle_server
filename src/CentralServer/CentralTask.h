#ifndef _CENTRALTASK_H_
#define _CENTRALTASK_H_

#include "GameBaseTask.h"
#include "ServerCommand.h"

class CCentralTask : public CServerTaskEx
{
public:
    CCentralTask(CListenTCPServer *listenServer)
        :CServerTaskEx(listenServer)
    {
        m_hreatTime = 0;
        m_highLoad = 0;
    }

    void Clear();
    bool cmdMsgParse(void *,const uint32_t);

    void UpdateHreatTime();
    uint64_t GetUpdateHreatTime() { return m_hreatTime; }
    uint32_t GetLoadInfo() { return m_highLoad; }

private:
    bool ServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);
    bool ServerRegistReq(Cmd::t_Server_Regist_Req *recv);

private:
    uint64_t m_hreatTime;
    uint32_t m_highLoad;
};

#endif
