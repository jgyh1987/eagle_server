#include "ChatClientTask.h"
#include "Stream.h"
#include "ServerCommand.h"
#include "ChatManager.h"
#include "ImpService.h"
#include "Defs.h"

bool CChatClientTask::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
{
	BinaryReadStream stream((const char*)ptNull, nCmdLen);
    ClientMsg::Message message;
    if(message.Unserialize(&stream) != 0)
    {
        LOGFMTE("ChatServer Msg Unserialize Error, len :%d", nCmdLen);
        return false;
    }

    switch(message.majorCmd)	
    {
	case ClientMsg::ChatMessageCommand::MAJOR_CMD:
        {
			switch(message.minorCmd)
            {
            case ClientMsg::ChatMessageReq::MINOR_CMD:
				{
					stream.Reset();
					ClientMsg::ChatMessageReq msg;
                    if( msg.Unserialize( &stream ) != 0 )
					{
						LOGFMTE("ChatServer ClientMsg::ChatMessageReq msg Unserialize Error, len :%d", nCmdLen);
                        return false;
					}

					ChatManager::instance()->Notify(&msg);
				}
				break;
			case ClientMsg::RegisterChannelReq::MINOR_CMD:
				{
					stream.Reset();
					ClientMsg::RegisterChannelReq msg;
                    if( msg.Unserialize( &stream ) != 0 )
					{
						LOGFMTE("ChatServer ClientMsg::RegisterChannelReq msg Unserialize Error, len :%d", nCmdLen);
                        return false;
					}

					ClientMsg::RegisterChannelRes send;
					send.channeltype = msg.channeltype;
					for (uint32_t i = 0; i < msg.channeltype.size(); ++i)
					{
						if (ChatManager::instance()->TaskAddChannel(this, msg.channeltype[i]))
						{
							send.ret = SUCCESS;
						}
						else
						{
							send.ret = DEFAULT_ERROR;
						}
					}
					SendClientMsg(&send);
				}
				break;
			case ClientMsg::UnRegisterChannelReq::MINOR_CMD:
				{
					stream.Reset();
					ClientMsg::UnRegisterChannelReq msg;
                    if( msg.Unserialize( &stream ) != 0 )
					{
						LOGFMTE("ChatServer ClientMsg::RegisterChannelReq msg Unserialize Error, len :%d", nCmdLen);
                        return false;
					}

					ClientMsg::UnRegisterChannelRes send;
					send.ret = SUCCESS;
					ChatManager::instance()->RemoveChannel(msg.channeltype, this);
					SendClientMsg(&send);
				}
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
    }


	return true;
}

bool CChatClientTask::SendClientMsg(ClientMsg::Message *message)
{
	unsigned char buff[MAX_DATASIZE];
    BinaryWriteStream stream((char*) buff, MAX_DATASIZE - PH_LEN);
    if (message->Serialize(&stream) != 0)
    {
        LOGFMTE("ChatServer Msg Serialize Error, £¨%d, %d£©", message->majorCmd, message->minorCmd);
        return false;
    }
    stream.Flush();
	SendCmd(buff, (uint32_t)stream.GetSize());

	return true;
}


