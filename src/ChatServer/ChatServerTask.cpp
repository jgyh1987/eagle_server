#include "ChatServerTask.h"
#include "Defs.h"
#include "Stream.h"
#include "ChatManager.h"
#include "LogicGateCommand.h"
#include "ServerCommand.h"

bool CChatServerTask::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
{
	Cmd::t_NullCmd *pNullCmd = (Cmd::t_NullCmd*)ptNull;
	switch (pNullCmd->cmd) 
    {
		case Cmd::CMD_SERVER_INIT:
			return ServerInitMessageParase(pNullCmd, nCmdLen);
		case Cmd::CMD_MESSAGE_TRANS:
			return TransMsgParase(pNullCmd, nCmdLen);
		default:break;
	}

	return false;
}

bool CChatServerTask::ServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
	switch (pNullCmd->para) 
    {
        case Cmd::PARA_REGIST_CHATMESSAGE_CHANNEL_REQ:
            {
				for (int i = 0; i < CHAT_CHANNEL_TYPE_MAX; ++i)
				{
					ChatManager::instance()->AddChannel(((Cmd::t_Regist_ChatMessage_Channel_Req*)pNullCmd)->channel[i]);

					Cmd::t_Regist_ChatMessage_Channel_Res send;
					send.ret = 1;
					SendCmd(&send, sizeof(send));
				}
            }
			return true;
        default:
			break;
	}

	return false;
}

bool CChatServerTask::TransMsgParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
	switch (pNullCmd->para) 
    {
        case Cmd::PARA_SERVER_SEND_TRANS_MSG:
            {
				const Cmd::t_NullCmd* pCmd = (const Cmd::t_NullCmd *)((Cmd::t_Server_Send_Trans_Msg*)pNullCmd)->data;
				switch (pCmd->cmd)
				{
				case Cmd::CMD_CHAT_MESSAGE:
					return ChatMessageParase(pCmd, ((Cmd::t_Server_Send_Trans_Msg*)pNullCmd)->dataLen);
				default:break;
				}
            }
			return true;
        default:
			break;
	}

	return false;
}

bool CChatServerTask::ChatMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
	switch (pNullCmd->para) 
    {
        case Cmd::PARA_SERVER_SEND_CHATMESSAGE_REQ:
            {
				Cmd::t_Server_Send_ChatMessage_Req *recv = (Cmd::t_Server_Send_ChatMessage_Req *)pNullCmd;
				ChatManager::instance()->Notify(recv->channel, recv->content);
            }
			return true;
        default:
			break;
	}

	return false;
}
