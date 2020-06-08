#include "LoginUdpServer.h"
#include "Stream.h"
#include "Defs.h"
#include "LoginServerCommand.h"
#include "ServerCommand.h"
#include "LogicLoginCommand.h"
#include "ToolsFun.h"
#include "TimeTick.h"
#include "AccountManager.h"
#include "ServeListManager.h"

#define LOGIN_INTERVAL 7


//check account is true
bool CheckAccountIsTrue(const char *str)
{
    for (uint32_t i = 0; i < strlen(str); ++i)
    {
        if (0 == i)
        {
            if (str[i] == '_' || str[i] == '@' || str[i] == '.')
                return false;
        }

        if ((str[i] >= 48 && str[i] <= 57) || (str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122) || str[i] == '_' || str[i] == '@' || str[i] == '.')
        {
        }
        else
            return false;
    }

    return true;
}

bool CLoginUdpServer::CmdMsgParseImp(void *ptNull, const uint32_t nCmdLen, sockaddr *addr, int mask)
{
    //BinaryReadStream stream((const char*)ptNull, nCmdLen);
 //   ClientMsg::Message message;
 //   if(message.Unserialize(&stream) != 0)
 //   {
 //       LOGFMTE("msg Unserialize Error, len :%d", nCmdLen);
    //    SendCmd("ASDFASDFASDF", 13, addr);
 //       return false;
 //   }

 //   switch(message.majorCmd)    
 //   {

 //       case ClientMsg::LoginCommand::MAJOR_CMD:
 //           {
 //               switch(message.minorCmd)
 //               {
 //                   case ClientMsg::RegistAccountReq::MINOR_CMD:
 //                       {
 //                           stream.Reset();
 //                           ClientMsg::RegistAccountReq msg;
 //                           if( msg.Unserialize( &stream ) != 0 )
    //                        {
    //                            LOGFMTE("ClientMsg::RegistAccountReq msg Unserialize Error, len :%d", nCmdLen);
 //                               return false;
    //                        }
    //                        LOGFMTT("ClientMsg::RegistAccountReq success %s, %s", msg.account.c_str(), msg.passwd.c_str());

    //                        if (msg.account.size() >= MAX_ACCOUNT_LENGHT || msg.passwd.size() >= MAX_PASSWD_LENGHT || msg.account.size() <= 0 || msg.passwd.size() <= 0)
    //                            break;

    //                        if (!CheckAccountIsTrue(msg.account.c_str()))
    //                        {
    //                            ClientMsg::RegistAccountRes res;
    //                            res.ret = ACCOUNT_ASIC_ERROR;

    //                            SendClientMsg(&res, addr);

    //                            break;
    //                        }

    //                        if (CAccountManager::instance()->AccountAlreadyExists(msg.account))
    //                        {
    //                            ClientMsg::RegistAccountRes res;
    //                            res.ret = ACCOUNT_ALREADY_EXISTS;

    //                            SendClientMsg(&res, addr);
    //                        }
    //                        else
    //                        {
    //                            CAccountManager::instance()->SetAccountToAddr(msg.account, addr);
    //                            Cmd::t_Regist_Account_Req send;
    //                            strncpy(send.account, msg.account.c_str(), MAX_ACCOUNT_LENGHT - 1);
    //                            strncpy(send.passwd, msg.passwd.c_str(), MAX_PASSWD_LENGHT - 1);
    //                            SendToDB(&send, sizeof(send));
    //                        }

 //                       }
 //                       break;
    //                case ClientMsg::LoginAccountReq::MINOR_CMD:
 //                       {
 //                           stream.Reset();
 //                           ClientMsg::RegistAccountReq msg;
 //                           if( msg.Unserialize( &stream ) != 0 )
    //                        {
    //                            LOGFMTE("ClientMsg::LoginAccountReq msg Unserialize Error, len :%d", nCmdLen);
 //                               return false;
    //                        }
    //                        LOGFMTT("ClientMsg::LoginAccountReq success %s, %s", msg.account.c_str(), msg.passwd.c_str());

    //                        if (msg.account.size() >= MAX_ACCOUNT_LENGHT || msg.passwd.size() >= MAX_PASSWD_LENGHT || msg.account.size() <= 0 || msg.passwd.size() <= 0)
    //                            break;

    //                        if (CAccountManager::instance()->AccountAlreadyExists(msg.account))
    //                        {
    //                            ClientMsg::LoginSessionAccountRes res;
    //                            SAccountInfo *accountInfo = NULL;
    //                            res.ret = CAccountManager::instance()->LoginAccount(msg.account, msg.passwd, &accountInfo);
    //                            if (SUCCESS == res.ret && accountInfo)
    //                            {
    //                                CServeListManager::instance()->SerializeServerList(res.data);
    //                                res.session = accountInfo->session;
    //                            }

    //                            SendClientMsg(&res, addr);
    //                        }
    //                        else
    //                        {
    //                            CAccountManager::instance()->SetAccountToAddr(msg.account, addr);
    //                            Cmd::t_Get_Account_Req send;
    //                            strncpy(send.account, msg.account.c_str(), MAX_ACCOUNT_LENGHT - 1);
    //                            strncpy(send.loginPasswd, msg.passwd.c_str(), MAX_PASSWD_LENGHT - 1);
    //                            SendToDB(&send, sizeof(send));
    //                        }
 //                       }
 //                       break;
    //                case ClientMsg::GetServerListReq::MINOR_CMD:
    //                    {
    //                        stream.Reset();
    //                        ClientMsg::GetServerListReq msg;
    //                        if( msg.Unserialize( &stream ) != 0 )
    //                        {
    //                            LOGFMTE("ClientMsg::GetServerListReq msg Unserialize Error, len :%d", nCmdLen);
    //                            return false;
    //                        }
    //                        LOGFMTD("ClientMsg::GetServerListReq cmd :%d--%d--%d", message.majorCmd, message.minorCmd, message.type);

    //                        ClientMsg::GetServerListRes serverlist;
    //                        CServeListManager::instance()->SerializeServerList(serverlist.data);
    //                        //for (uint32_t i = 0; i < serverlist.data.size(); ++i)
    //                        //{
    //                            //LOGT("ClientMsg::GetServerListReq send data" << serverlist.data[i].ip.c_str() << serverlist.data[i].port << serverlist.data[i].areaName.c_str() << serverlist.data[i].serverName.c_str() << serverlist.data[i].status);
    //                        //}

    //                        SendClientMsg(&serverlist, addr);
    //                    }
    //                    break;
    //                case ClientMsg::SelectServerReq::MINOR_CMD:
    //                    {
    //                        stream.Reset();
    //                        ClientMsg::SelectServerReq msg;
    //                        if( msg.Unserialize( &stream ) != 0 )
    //                        {
    //                            LOGFMTE("ClientMsg::SelectServerReq msg Unserialize Error, len :%d", nCmdLen);
    //                            return false;
    //                        }
    //                        ServerObject *server = ServerManager::instance()->GetServerByID(msg.serverID);
    //                        LOGD("ClientMsg::SelectServerReq serverID = " << msg.serverID << "serverPtr = " << server);
    //                        ClientMsg::SelectServerRes clientSend;
    //                        SelectServerClientMsg clientmsginfo;
    //                        if (!server)
    //                        {
    //                            clientSend.ret = DEFAULT_ERROR;
    //                        }
    //                        else
    //                        {
    //                            if (!server->ServerIsVerify())
    //                                clientSend.ret = DEFAULT_ERROR;
    //                            else
    //                            {
    //                                Cmd::t_Send_Session_Sync serverSend;
    //                                SAccountInfo *info = CAccountManager::instance()->GetAccountInfo(msg.account);
    //                                if (!info)
    //                                    break;

    //                                if (CImpServerTimeTick::currentTime.sec() - info->m_lastLoginReq < LOGIN_INTERVAL)
    //                                    break;

    //                                info->m_lastLoginReq = (uint32_t)CImpServerTimeTick::currentTime.sec();
    //                                strncpy(serverSend.session, info->session.c_str(), MAX_SESSION_LENGHT - 1);
    //                                strncpy(serverSend.account, info->account.c_str(), MAX_ACCOUNT_LENGHT - 1);
    //                                serverSend.clientmsgid = ++m_clientMsgId;
    //                                server->SendCmd(&serverSend, sizeof(serverSend));

    //                                clientSend.ret = SUCCESS;
    //                                clientmsginfo.msg.ret = SUCCESS;
    //                                clientmsginfo.addr = *(sockaddr_storage *)addr;
    //                                CAccountManager::instance()->m_selectServerRes[m_clientMsgId] = clientmsginfo;
    //                            }
    //                            

    //                            //if (1 == clientSend.ret)
    //                            //    SendClientMsg(&clientSend, addr);
    //                        }
    //                    }
    //                    break;
    //                default:
    //                    break;
 //               }
 //           }
 //           break;
    //    default:
    //        {
    //            LOGFMTT("ClientMsg :: default:%d", nCmdLen);
    //            LOGFMTT(" CLoginUdpServer::cmdMsgParse  :%s", ((char*)ptNull));

    //            SendCmd(ptNull, nCmdLen, addr);
    //        }
    //        break;
 //   }

    return true;
}

bool CLoginUdpServer::SendClientMsg(ClientMsg::Message *message, sockaddr *addr)
{
    unsigned char buff[MAX_DATASIZE];
    BinaryWriteStream stream((char*) buff, MAX_DATASIZE - PH_LEN);
    if (message->Serialize(&stream) != 0)
    {
        LOGFMTE("msg Unserialize Error %d, %d !!!", message->majorCmd, message->minorCmd);
        return false;
    }
    stream.Flush();
    SendCmd(buff, (uint32_t)stream.GetSize(), addr, 0);

    return true;
}



