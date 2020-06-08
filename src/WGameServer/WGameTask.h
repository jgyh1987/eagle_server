#ifndef _WGAMETASK_H_
#define _WGAMETASK_H_

#include "GameBaseTask.h"
#include "ServerCommand.h"

class CWGameTask : public CServerTaskEx
{
public:
    CWGameTask(CListenTCPServer *listenServer)
        :CServerTaskEx(listenServer)
    {

    }

    bool cmdMsgParse(void *,const uint32_t);


private:
    bool ServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);
    bool ServerRegistReq(Cmd::t_Server_Regist_Req *recv);
	bool AgentSceneIdNotify(Cmd::t_Agent_SceneId_Notify *recv);

	bool TransMsgParase(const Cmd::t_Server_Send_Trans_Msg* pNullCmd, const unsigned int nCmdLen);

	bool WorldMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);

};

#endif
