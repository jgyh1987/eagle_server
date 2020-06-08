#include "LoginTask.h"
#include "Stream.h"
#include "Defs.h"
#include "ServerCommand.h"
#include "AccountManager.h"
#include "LogicLoginCommand.h"
#include "LoginClientTask.h"
#include "LoginService.h"

void CLoginTask::Clear()
{
    m_playerCount = 0;

    return CServerTaskEx::Clear();
}

bool CLoginTask::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
{
    Cmd::t_NullCmd *pNullCmd = (Cmd::t_NullCmd*)ptNull;
    switch (pNullCmd->cmd) 
    {
        case Cmd::CMD_SERVER_INIT:
            return ServerCommonMessageParase((Cmd::t_NullCmd*)pNullCmd, nCmdLen);
        case Cmd::CMD_LOGIN_LOGIC:
            return LoginCommonMessageParase((Cmd::t_NullCmd*)pNullCmd, nCmdLen);
        default:break;
    }

    return true;
}

bool CLoginTask::ServerCommonMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch (pNullCmd->para) 
    {
        case Cmd::PARA_SERVER_REGIST_REQ:
            {
                Cmd::t_Server_Regist_Req *recv = (Cmd::t_Server_Regist_Req*)pNullCmd;
                Cmd::t_Server_Regist_Res send;
                send.res = DEFAULT_ERROR;
                if (SERVER_TYPE_LOGIC_GATEWAY != recv->info.serverType)
                {
                    LOGE("gateway regist loginserver falied  type error: TYPE = " << recv->info.serverType << "NAME = " << recv->info.serverName << "NAMELEN = " << strlen(recv->info.serverName));

                }
                else
                {
                    InitServerInfo(&recv->info);
                    GetServerImp()->AddLoginTask(this);
                    send.res = SUCCESS;
                }

                SendCmd(&send, sizeof(send));
            }
            return true;
        default:
            break;
    }

    return false;
}

bool CLoginTask::LoginCommonMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch (pNullCmd->para) 
    {
        case Cmd::PARA_SEND_SESSION_SYNC_RES:
            {
                Cmd::t_Send_Session_Sync_Res *recv = (Cmd::t_Send_Session_Sync_Res*)pNullCmd;
                std::string account(recv->account);
                SAccountInfo* pInfo = CAccountManager::instance()->GetAccountInfo(account);
                if (pInfo && pInfo->task)
                {
                    //protocol::SelectGameServerRspNet res;
                    //res.set_ret(SUCCESS);
                    //res.set_gametoken(pInfo->account);
                    //protocol::ServerInfo *tcpInfo = res.mutable_server();
                    //tcpInfo->set_serverip(this->GetServerIp());
                    //tcpInfo->set_serverport(this->GetServerPort());
                    //protocol::ServerInfo *udpInfo = res.mutable_udpserver();
                    //udpInfo->set_serverip(this->GetServerIp());
                    //udpInfo->set_serverport(this->GetServerPort() + 1);
                    //pInfo->task->SendClientMsg(&res, protocol::sc_selectGameServer);

                    ClientMsg::SelectServerRes send;
                    send.ret = SUCCESS;
                    pInfo->task->SendClientMsg(&send);
                }

            }
            return true;
        case Cmd::PARA_SEND_SERVER_PLAYERCOUNT_NOTIFY:
            {
                Cmd::t_Send_Server_PlayerCount_Notify *recv = (Cmd::t_Send_Server_PlayerCount_Notify*)pNullCmd;
                
                m_playerCount = recv->playerCount;
            }
            return true;
        case Cmd::PARA_GET_PACKAGECODE_REQ:
            {
                SendToDB((void *)pNullCmd, nCmdLen);
            }
            return true;
        case Cmd::PARA_PACKAGECODE_REWARD_RES:
            {
                SendToDB((void *)pNullCmd, nCmdLen);
            }
            return true;
        default:
            break;
    }

    return false;
}


void CLoginTask::InitServerInfo(const Cmd::ServerInfoEx *pinfo)
{
    m_serverInfo.serverId = pinfo->serverId;                                //    
    m_serverInfo.serverType = pinfo->serverType;                            //
    bcopy(pinfo->serverName, m_serverInfo.serverName, MAX_SERVERNAME_LENGTH);//
    bcopy(pinfo->serverIP, m_serverInfo.serverIP, MAX_IP_LENGTH);        //ip
    m_serverInfo.port = pinfo->port;                                        //
    m_gameServerId = pinfo->gameServerId;
}


