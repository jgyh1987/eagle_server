#ifndef _CHATCLIENTTASK_H_
#define _CHATCLIENTTASK_H_

#include "ClientTask.h"
#include "ClientMsg.h"

class CChatClientTask : public CClientTask
{
public:
	CChatClientTask(CListenTCPServer *listenServer)
		:CClientTask(listenServer)
	{
	}

	bool cmdMsgParse(void *,const uint32_t);

	bool SendClientMsg(ClientMsg::Message *message);

public:
	std::list<std::string> m_listChannel;
	
};

#endif
