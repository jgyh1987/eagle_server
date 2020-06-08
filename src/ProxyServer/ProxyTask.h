#ifndef _PROXYTASK_H_
#define _PROXYTASK_H_

#include "GameBaseTask.h"
#include "ServerCommand.h"

class CProxyTask : public CServerTaskEx
{
public:
    CProxyTask(CListenTCPServer *listenServer)
        :CServerTaskEx(listenServer)
    {

    }

    bool cmdMsgParse(void *,const uint32_t);


private:
    bool ServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);
    bool ServerRegistReq(Cmd::t_Server_Regist_Req *recv);

    bool TransMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);
    

};

#endif
