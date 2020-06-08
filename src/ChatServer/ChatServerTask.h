#ifndef _CHATSERVERTASK_H_
#define _CHATSERVERTASK_H_

#include "ServerTask.h"

class CChatServerTask : public CServerTask
{
public:
	CChatServerTask(CListenTCPServer *listenServer)
		:CServerTask(listenServer)
	{
	}

	bool cmdMsgParse(void *,const uint32_t);

public:
	//CMD_SERVER_INIT
	bool ServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);

	//CMD_MESSAGE_TRANS
	bool TransMsgParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);

	//CMD_CHAT_MESSAGE
	bool ChatMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen);

private:

};

#endif
