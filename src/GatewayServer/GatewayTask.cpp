#include "GatewayTask.h"
#include "Stream.h"
#include "ClientMsg.h"
#include "SessionManager.h"
#include "Defs.h"
#include "PlayerManager.h"
#include "TimeTick.h"
#include "LogicLoginCommand.h"
#include "GatewayService.h"
#include "ServerCommand.h"

CGatewayTask::~CGatewayTask()
{
    m_player = NULL;
}

void CGatewayTask::Clear()
{
    m_player = NULL;
    m_hreatTime = 0;
    m_lockTime = 0;

    return CClientTask::Clear();
}

void check_sockname(struct sockaddr* addr, const char* compare_ip, int compare_port, const char* context, char *check_ip)
{
    struct sockaddr_in check_addr = *(struct sockaddr_in*) addr;

    //char check_ip[MAX_IP_LENGTH];  

    struct sockaddr_in compare_addr;
    uv_ip4_addr(compare_ip, compare_port, &compare_addr);

    /* Both addresses should be ipv4 */
    if (check_addr.sin_family == AF_INET) {
        //printf("src sin_family is AF_INET.\n");  
    }

    if (compare_addr.sin_family == AF_INET) {
        // printf("compare sin_family is AF_INET.\n");  
    }

    /* Check if the ip matches */
    if (memcmp(&check_addr.sin_addr, &compare_addr.sin_addr,
        sizeof compare_addr.sin_addr) == 0) {
        //printf("ip matches.\n");  
    }

    /* Check if the port matches. If port == 0 anything goes. */
    if (compare_port == 0 || check_addr.sin_port == compare_addr.sin_port) {
        //printf("port matches.\n");  
    }
    //网络字节序转换成主机字符序  
    uv_ip4_name(&check_addr, (char*)check_ip, MAX_IP_LENGTH);

    //或者像下面这样获得ip地址  
    //char* check_ip = inet_ntoa(check_addr.sin_addr);  

    // printf("%s: %s:%d\n", context, check_ip, ntohs(check_addr.sin_port));  
}

bool CGatewayTask::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
{

    //protocol::PackageNet stream;
    //stream.ParseFromArray(ptNull, (int)nCmdLen);
    //uint32_t id = stream.id() / PROTOCOL_ID_MASK;

    //switch (stream.id())
    //{
    //case protocol::cs_heartBeat:
    //    break;
    //case protocol::cs_loginGame:
    //    {
    //        LoginGame((void *)stream.body().c_str(), (int)stream.body().size());
    //    }
    //break;
    //default:
    //    return TransMsgToLogic(ptNull, nCmdLen);
    //    break;
    //}

    //LOGFMTT(" CGatewayTask::cmdMsgParse :%d", nCmdLen);

    BinaryReadStream stream((const char*)ptNull, nCmdLen);
    ClientMsg::Message message;
    if(message.Unserialize(&stream) != 0)
    {
        LOGFMTE("msg Unserialize Error, len :%d", nCmdLen);
        return false;
    }

    LOGFMTT("  ClientMsg::Message cmd :%d--%d", message.majorCmd, message.minorCmd);

    switch(message.majorCmd)    
    {
    case ClientMsg::LoginCommand::MAJOR_CMD:
        {
            switch(message.minorCmd)
            {
                case ClientMsg::SelectLogicReq::MINOR_CMD:
                    {
                        stream.Reset();
                        ClientMsg::SelectLogicReq msg;
                        if( msg.Unserialize( &stream ) != 0 )
                        {
                            LOGFMTE("ClientMsg::SelectLogicReq msg Unserialize Error, len :%d", nCmdLen);
                            return false;
                        }

                        LOGFMTT("ClientMsg::SelectLogicReq success %s, %s", msg.account.c_str(), msg.session.c_str());

                        if (msg.account.size() >= MAX_ACCOUNT_LENGHT || msg.account.size() <= 0)
                        {
                            break;
                        }

                        AccountSession *session = AccountSessionManager::instance()->GetAccountSession(msg.account);
                        if (!session)
                        {
                            ClientMsg::SelectLogicRes send;
                            send.ret = NO_ACCOUNT;
                            SendClientMsg(&send);
                        }
                        else
                        {
                            if (session->session.compare(msg.session))
                            {
                                ClientMsg::SelectLogicRes send;
                                send.ret = NO_SESSION;
                                SendClientMsg(&send);
                            }
                            else
                            {
                                session->TickOldPlayer();

                                Cmd::t_Get_PlayerInfo_Req serverSend;
                                strncpy(serverSend.account, session->account.c_str(), MAX_ACCOUNT_LENGHT - 1);

                                SendToLogicServer(&serverSend, sizeof(serverSend));

                                session->task = this;
                            }
                        }

                        //SyncTimeToClinet();
                    }
                    break;
                case ClientMsg::ServerHreatRes::MINOR_CMD:
                    {
                        stream.Reset();
                        ClientMsg::ServerHreatRes msg;
                        if (msg.Unserialize(&stream) != 0)
                            return false;

                        ClientMsg::ServerHreatSync notify;
                        notify.time = msg.time;
                        notify.uid = msg.uid;
                        SendClientMsg(&notify);
                    }
                    break;                    
                default:
                    return TransMsgToLogic(ptNull, nCmdLen);
                    break;
            }
        }
        break;
    case ClientMsg::ChatMessageCommand::MAJOR_CMD:
        {
            return TransMsgToLogic(ptNull, nCmdLen);
        }
        break;
    case ClientMsg::WorldMessageCommand::MAJOR_CMD:
        {

            return TransMsgToLogic(ptNull, nCmdLen);

        }
        break;
    case ClientMsg::ClientExInfoMessageCommand::MAJOR_CMD:
        {
            //switch(message.minorCmd)
   //         {
   //             case ClientMsg::ClientErrorMsgNotify::MINOR_CMD:
            //    {
            //        stream.Reset();
            //        ClientMsg::ClientErrorMsgNotify msg;
   //                 if( msg.Unserialize( &stream ) != 0 )
            //        {
            //            LOGFMTE("ClientMsg::ClientErrorMsgNotify msg Unserialize Error, len :%d", nCmdLen);
   //                     return false;
            //        }
            //        LOGA("ClientErrorMsg  msg = \" " << msg.errorInfo.c_str() << "\" !!!");
            //    }
            //}
        }
        break;
    default:
        {
            return TransMsgToGame(ptNull, nCmdLen);
        }
        break;
    }

    return true;
}

bool CGatewayTask::TransMsgToLogic(void *ptNull,const uint32_t nCmdLen)
{
    if (!m_player)
        return false;

    Cmd::t_Server_Send_Trans_Msg *send;
    ((CGatewayServer *)g_pServerImp)->ServerCmdBuffer(send);
    send->uid = m_player->Id();
    memcpy(send->data, ptNull, nCmdLen);
    send->dataLen = nCmdLen;
    send->targetServer.serverType = SERVER_TYPE_LOGIC_SERVER;
    send->srcServer.serverType = CLIENT_TYPE;
    SendToLogicServer(send, send->Size());

    return true;
}

bool CGatewayTask::TransMsgToGame(void* ptNull, const uint32_t nCmdLen)
{
	if (!m_player || !m_player->GetAgentServerId() || m_player->GetAgentLock())
		return false;

	Cmd::t_Server_Send_Trans_Msg* send;
	((CGatewayServer*)g_pServerImp)->ServerCmdBuffer(send);
	send->uid = m_player->Id();
	memcpy(send->data, ptNull, nCmdLen);
	send->dataLen = nCmdLen;
	send->targetServer.serverType = SERVER_TYPE_WGAME_SERVER;
	send->srcServer.serverType = CLIENT_TYPE;
	SendToGameServer(send, send->Size(), m_player->GetAgentServerId());

	return true;
}

bool CGatewayTask::SendClientMsg(ClientMsg::Message *message)
{
    unsigned char buff[MAX_DATASIZE];
    BinaryWriteStream stream((char*) buff, MAX_DATASIZE - PH_LEN);
    if (message->Serialize(&stream) != 0)
    {
        LOGFMTE("msg Serialize Error, （%d, %d）", message->majorCmd, message->minorCmd);
        return false;
    }
    stream.Flush();
    SendCmd(buff, (uint32_t)stream.GetSize());

    return true;
}

bool CGatewayTask::SendClientMsg(::google::protobuf::Message *message, int id)
{
    unsigned char buff[MAX_DATASIZE];
    int len = (int)message->ByteSizeLong();
    message->SerializeToArray(buff, len);

    protocol::PackageNet stream;
    stream.set_id(id);
    stream.set_body(buff, len);

    len = (int)stream.ByteSizeLong();
    stream.SerializeToArray(buff, len);
    SendCmd(buff, len);

    return true;
}

bool CGatewayTask::RegistPlayer(PlayerInfoBase &playerinfo, AccountSession *account)
{
    GatewayPlayer *tempPlayer = new GatewayPlayer(playerinfo.playerId, playerinfo.playerUid, account, this);
    if (!tempPlayer)
        return false;

    GatewayPlayer *oldPlayer = PlayerManager::instance()->GetPlayerByID(tempPlayer->Id());
    if (oldPlayer)
    {
        //ClientMsg::KickPlayerNotify send;
        //send.ret = REPEATED_LOGIN_LOGIC;
        //oldPlayer->SendClientMsg(&send);
        PlayerManager::instance()->RemovePlayer(oldPlayer);
    }

    if (!PlayerManager::instance()->AddPlayer(tempPlayer))
    {
        delete tempPlayer;
        return false;
    }

    account->player = m_player = tempPlayer;

    return true;
}

void CGatewayTask::LoginGame(void *data, int size)
{
    protocol::LoginGameReqNet stream;
    stream.ParseFromArray(data, size);

    protocol::LoginGameRspNet send;
    send.set_ret(SUCCESS);
    do
    {
        if (stream.account().size() >= MAX_ACCOUNT_LENGHT || stream.account().size() <= 0)
        {
            send.set_ret(INPUT_CHARACTER_LENGTH_MAX);
            break;
        }

        AccountSession *session = AccountSessionManager::instance()->GetAccountSession(stream.account());
        if (!session)
        {
            send.set_ret(NO_ACCOUNT);
            break;
        }
        else
        {
            if (session->session.compare(stream.gametoken()))
            {
                send.set_ret(NO_SESSION);
                break;
            }
            else
            {
                session->TickOldPlayer();

                Cmd::t_Get_PlayerInfo_Req serverSend;
                strncpy(serverSend.account, session->account.c_str(), MAX_ACCOUNT_LENGHT - 1);

                SendToLogicServer(&serverSend, sizeof(serverSend));

                session->task = this;
            }
        }

    } while (false);

    if (send.ret() != SUCCESS)
        SendClientMsg(&send, protocol::sc_loginGame);

    return;
}



