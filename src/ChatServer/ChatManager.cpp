#include "ChatManager.h"
#include "ChatClientTask.h"

bool ChatManager::AddTask(CChatClientTask *task)
{
	return false;
}

bool ChatManager::DelTask(CChatClientTask *task)
{	
	for (std::list<std::string>::iterator channelItr = task->m_listChannel.begin(); channelItr != task->m_listChannel.end(); ++channelItr)
	{
		std::map< std::string, std::map<uint32_t, CChatClientTask*> >::iterator itr1 = m_channelMap.find(*channelItr);
		if (itr1 != m_channelMap.end())
		{
			std::map<uint32_t, CChatClientTask*>::iterator itr2 = itr1->second.find(task->GetClientID());
			if (itr2 != itr1->second.end())
			{
				itr1->second.erase(itr2);
			}

			if (0 == itr1->second.size())
				m_channelMap.erase(itr1);
		}
	}

	task->m_listChannel.clear();

	return true;
}

bool ChatManager::TaskAddChannel(CChatClientTask *task, std::string channel)
{
	//for (std::list<std::string>::iterator itr = task->m_listChannel.begin(); itr != task->m_listChannel.end(); ++itr)
	//{
	//	if (*itr == channel)
	//	{
	//		return true;
	//	}
	//}

	std::map< std::string, std::map<uint32_t, CChatClientTask*> >::iterator itr1 = m_channelMap.find(channel);
	if (itr1 != m_channelMap.end())
	{
		std::map<uint32_t, CChatClientTask*>::iterator itr2 = itr1->second.find(task->GetClientID());
		if (itr2 != itr1->second.end())
		{
			return true;
		}
		else
		{
			itr1->second[task->GetClientID()] = task;
		}
	}
	else
	{
		std::map<uint32_t, CChatClientTask*> temp;
		temp[task->GetClientID()] = task;
		m_channelMap[channel] = temp;
	}

	task->m_listChannel.push_back(channel);

	return true;
}

bool ChatManager::AddChannel(std::string  channel)
{
	std::map< std::string, std::map<uint32_t, CChatClientTask*> >::iterator itr1 = m_channelMap.find(channel);
	if (itr1 == m_channelMap.end())
	{
		std::map<uint32_t, CChatClientTask*> temp;
		m_channelMap[channel] = temp;
	}

	return true;
}

bool ChatManager::RemoveChannel(std::string  channel, CChatClientTask *task)
{
	std::map< std::string, std::map<uint32_t, CChatClientTask*> >::iterator itr1 = m_channelMap.find(channel);
	if (itr1 != m_channelMap.end())
	{
		std::map<uint32_t, CChatClientTask*>::iterator itr2 = itr1->second.find(task->GetClientID());
		if (itr2 != itr1->second.end())
		{
			itr1->second.erase(itr2);
		}

		if (0 == itr1->second.size())
			m_channelMap.erase(itr1);
	}

	for (std::list<std::string>::iterator channelItr = task->m_listChannel.begin(); channelItr != task->m_listChannel.end(); ++channelItr)
	{
		if (channel == *channelItr)
		{
			task->m_listChannel.erase(channelItr);
			break;
		}
	}

	return true;
}

bool ChatManager::Notify(ClientMsg::ChatMessageReq *msg)
{
	std::map< std::string, std::map<uint32_t, CChatClientTask*> >::iterator itr = m_channelMap.find(msg->channeltype);
	if (itr == m_channelMap.end())
		return false;

	ClientMsg::ChatMessageRes send;
	send.str = msg->str;
	send.channeltype = msg->channeltype;
	send.playerName = msg->playerName;
	send.vipLevel = msg->vipLevel;
	for (std::map<uint32_t, CChatClientTask*>::iterator itr1 = itr->second.begin(); itr1 != itr->second.end(); ++itr1)
	{
		itr1->second->SendClientMsg(&send);
	}

	return true;
}

bool ChatManager::Notify(std::string channel, const char * content)
{
	std::map< std::string, std::map<uint32_t, CChatClientTask*> >::iterator itr = m_channelMap.find(channel);
	if (itr == m_channelMap.end())
		return false;

	ClientMsg::ChatMessageRes send;
	send.str = content;
	send.channeltype = channel;
	for (std::map<uint32_t, CChatClientTask*>::iterator itr1 = itr->second.begin(); itr1 != itr->second.end(); ++itr1)
	{
		itr1->second->SendClientMsg(&send);
	}

	return true;
}

