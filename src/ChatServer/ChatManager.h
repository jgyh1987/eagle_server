#ifndef _CHATMANAGER_H_
#define _CHATMANAGER_H_

#include "Sys.h"
#include "Singleton.h"
#include "ClientMsg.h"

class CChatClientTask;

class ChatManager : public CSingleton<ChatManager>
{
public:
	bool AddTask(CChatClientTask *);
	bool DelTask(CChatClientTask *);
	bool TaskAddChannel(CChatClientTask *task, std::string  channel);
	bool AddChannel(std::string  channel);
	bool RemoveChannel(std::string  channel, CChatClientTask *task);
	bool Notify(ClientMsg::ChatMessageReq *msg);
	bool Notify(std::string channel, const char * content);

private:
	std::map< std::string, std::map<std::string, CChatClientTask*> > m_taskNameByServer;
	std::map< std::string, std::map<uint32_t, CChatClientTask*> > m_channelMap;

};



#endif

