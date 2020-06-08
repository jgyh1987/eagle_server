#ifndef _WMATCH_TASK_H_
#define _WMATCH_TASK_H_

#include "GameBaseTask.h"

class CWMatchTask : public CServerTaskEx
{
public:
    CWMatchTask(CListenTCPServer *listenServer)
        :CServerTaskEx(listenServer)
    {
        m_highLoad = 0;
    }

    bool cmdMsgParse(void *,const uint32_t);

public:
    inline uint32_t GetHighLoad()
    {
        return m_highLoad;
    }

private:
    bool ServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);

    bool WorldMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);

private:

    uint32_t m_highLoad;
};


#endif
