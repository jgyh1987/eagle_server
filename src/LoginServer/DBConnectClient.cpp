#include "DBConnectClient.h"
#include "Stream.h"
#include "ServerCommand.h"
#include "LoginServerCommand.h"
#include "ClientMsg.h"
#include "LogicLoginCommand.h"
#include "LoginTask.h"
#include "Defs.h"
#include "AccountManager.h"
#include "ServeListManager.h"
#include "LoginService.h"
#include "LoginClientTask.h"

bool CDBConnectClient::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
{
    Cmd::t_NullCmd *pNullCmd = (Cmd::t_NullCmd*)ptNull;
    switch (pNullCmd->cmd) 
    {
        case Cmd::CMD_LOGIN_SERVER:
            return LoginAccountMessageParase((Cmd::t_NullCmd*)pNullCmd, nCmdLen);
        case Cmd::CMD_SERVER_INIT:
            return LoginDataMessageParase((Cmd::t_NullCmd*)pNullCmd, nCmdLen);
        case Cmd::CMD_LOGIN_LOGIC:
            return LoginSessionMessageParase((Cmd::t_NullCmd*)pNullCmd, nCmdLen);
        default:break;
    }

    return false;
}

void CDBConnectClient::CallBackConnectSuccessImp()
{
    Cmd::t_Server_Regist_Req send;
    send.info.serverId = g_serverId;
    strncpy(send.info.serverName, eagle::global["ServerName"].c_str(), sizeof(send.info.serverName));
    strncpy(send.info.serverIP, eagle::global["LoginServerTcpIP"].c_str(), sizeof(send.info.serverIP));
    send.info.serverType = SERVER_TYPE_LOGIN_SERVER;
    SendCmd(&send, sizeof(send));

    return;
}

void CDBConnectClient::CallBackConnectErrorImp()
{

    return;
}

bool CDBConnectClient::LoginDataMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch (pNullCmd->para) 
    {
        case Cmd::PARA_SERVER_REGIST_RES:
            {
                LOGI("LoginServer DBConnectClient verify success !!!");

                m_isRegist = true;

                return true;
            }
        default:
            break;
    }

    return false;
}

bool CDBConnectClient::LoginAccountMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch (pNullCmd->para) 
    {
        case Cmd::PARA_LOGIN_SESSIONACCOUNT_RES:        //
            {
                Cmd::t_Login_SessionAccount_Res *recv = (Cmd::t_Login_SessionAccount_Res*)pNullCmd;
                std::string account(recv->account);
                SAccountInfo* pInfo = CAccountManager::instance()->GetAccountInfo(account);
                if (pInfo)
                {
                    if (SUCCESS == recv->ret)
                        pInfo->isVerify = true;

                    //protocol::LoginRspNet res;

                    //res.set_ret(recv->ret);
                    //res.set_account(account);
                    //if (pInfo->task)
                    //    pInfo->task->SendClientMsg(&res, protocol::sc_login);

                    if (pInfo->task)
                    {
                        ClientMsg::LoginSessionAccountRes res;
                        res.ret = recv->ret;
                        res.account = account;
                        pInfo->task->SendClientMsg(&res);
                    }
                }

                return true;
            }
        default:
            break;
    }

    return false;
}

bool CDBConnectClient::LoginSessionMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch (pNullCmd->para) 
    {
        case Cmd::PARA_GET_PACKAGECODE_RES:
            {
                Cmd::t_Get_PackageCode_Res *recv = (Cmd::t_Get_PackageCode_Res*)pNullCmd;
                //ServerObject *server = ServerManager::instance()->GetServerByID(recv->packageInfo.serverId);
                //if (server && server->Task())
                //{
                //    server->Task()->SendCmd(recv, nCmdLen);
                //}

                return true;
            }
            break;
        default:
            break;
    }

    return false;
}


