#include "LoginDataTask.h"
#include "Defs.h"
#include "LoginServerCommand.h"
#include "ServerCommand.h"
#include "InnerCommand.h"
#include "QQSdk.h"
#include "LoginDataService.h"

bool CLoginDataTask::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
{
    try
    {
        Cmd::t_NullCmd *pNullCmd = (Cmd::t_NullCmd*)ptNull;
        switch (pNullCmd->cmd) 
        {
            case Cmd::CMD_LOGIN_SERVER:
                return DBLogicPlayerInfoMessageParase(pNullCmd, nCmdLen);
            case Cmd::CMD_SERVER_INIT:
                return DBServerInitMessageParase(pNullCmd, nCmdLen);
            case Cmd::CMD_LOGIN_LOGIC:
                return DBLoginSessionMessageParase(pNullCmd, nCmdLen);
            default:break;
        }
    }
    catch( const mysqlpp::BadQuery& e ) 
    {
        LOGFMTE("LoginDataServer LoginDataTask mysql++ query error: %s errornum= %d", e.what(), e.errnum());
        LOGE("LoginDataServer LoginDataTask mysql reconnect error");
    } 
    catch (const mysqlpp::BadConversion& e ) 
    {
        LOGFMTE("LoginDataServer LoginDataTask mysql++ conversion error: %s, retrieved data size: %llu, actual size: %llu", e.what(), (unsigned long long)e.retrieved, (unsigned long long)e.actual_size);
        LOGE("LoginDataServer LoginDataTask mysql reconnect error");
    } 
    catch (const mysqlpp::Exception& e) 
    {
        LOGFMTE("LoginDataServer LoginDataTask mysql++ general error: %s", e.what());
        LOGE("LoginDataServer LoginDataTask mysql reconnect error");
    } 
    catch (...) 
    {
        LOGE("LoginDataServer LoginDataTask unknown error.");
        LOGE("LoginDataServer LoginDataTask mysql reconnect error");
    }
    
    return false;
}

bool CLoginDataTask::DBServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch ( pNullCmd->para )
    {
    case Cmd::PARA_SERVER_REGIST_REQ:
        {
            Cmd::t_Server_Regist_Res send;
            SendCmd(&send, sizeof(send));

            Cmd::t_Server_Regist_Req *recv = (Cmd::t_Server_Regist_Req *)pNullCmd;
			UpdateServerInfo(&recv->info);
            g_pServerImp->AddServerTask(this);
        }
        return true;
    default:
        return false;
    }

    return false;
}

bool CLoginDataTask::DBLogicPlayerInfoMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch ( pNullCmd->para )
    {
        case Cmd::PARA_REGIST_ACCOUNT_REQ://
            {
                Cmd::t_Regist_Account_Req *recv = (Cmd::t_Regist_Account_Req*)pNullCmd;

                Cmd::t_Regist_Account_Res send;
                send.ret = SUCCESS;
                memcpy(send.account, recv->account, MAX_ACCOUNT_LENGHT);
                if (DBGetAccountPasswdByAccount(recv->account))
                {
                    send.ret = ACCOUNT_ALREADY_EXISTS;
                }
                else
                {
                    mysqlpp::Query query = DataDBConnection::instance()->query();
                    SqlAccount info;
                    info.account = recv->account;
                    info.sdkId = recv->account;
                    info.passwd = recv->passwd;
                    std::vector<bool> vb(SqlAccount_NULL, true);
                    vb[SqlAccount_id] = false;
                    DataDBConnection::makeInsertQuery(query, info, vb);
                    mysqlpp::SimpleResult res = query.execute();
                    LOGD("Cmd::PARA_REGIST_ACCOUNT_REQ " << query.str().c_str());

                    if (!res)
                    {
                        send.ret = REGIST_ACCOUNT_ERROR;
                    }
                }
                SendCmd(&send, sizeof(send));
            }
            return true;
        case Cmd::PARA_LOGIN_ACCOUNT_REQ://
            {
                Cmd::t_Login_Account_Req *recv = (Cmd::t_Login_Account_Req*)pNullCmd;

                Cmd::t_Login_SessionAccount_Res send;
                bcopy(recv->account, send.account, MAX_ACCOUNT_LENGHT);
                send.ret = SUCCESS;
                if (SDK_TYPE_NONE == recv->sdkType)
                {
                    if (DBGetAccountByAccountPasswd(recv->account, recv->token))
                    {
                        
                    }
                    else
                    {
                        send.ret = REGIST_ACCOUNT_ERROR;
                    }
                }
                else
                {
                    if (DBGetAccountPasswdByAccount(recv->account))
                    {
                        Cmd::t_Verify_Session_Req send;
                        strncpy(send.account, recv->account, MAX_ACCOUNT_LENGHT - 1);
                        strncpy(send.openid, recv->sdkId, MAX_ACCOUNT_LENGHT - 1);
                        strncpy(send.openkey, recv->token, MAX_SDK_OPENKEY_LENGHT - 1);
                        send.sdkType = recv->sdkType;
                        CQQSdkManager::instance()->PushRecvCmd(&send, sizeof(send));
                    }
                    else
                    {
                        send.ret = NO_ACCOUNT;
                    }
                }
                
                SendCmd(&send, sizeof(send));
                break;
            }
            return true;
        default:
            return false;
    }

    return false;
}

bool CLoginDataTask::DBGetAccountPasswdByAccount(char *account)
{
    mysqlpp::Query query = DataDBConnection::instance()->query();
    query << "select * from ACCOUNT_INFO where ACCOUNT  =  '" << account << "' ;";
    LOGD("Cmd::DBGetAccountPasswdByAccount " << query.str().c_str());

    std::vector<SqlAccount> result;
    query.storein(result);
    if (result.empty())
    {
        return false;
    }

    return true;
}

bool CLoginDataTask::DBGetAccountByAccountPasswd(char *account, char *passwd)
{
    mysqlpp::Query query = DataDBConnection::instance()->query();
    query << "select * from ACCOUNT_INFO where ACCOUNT  =  '" << account << "' ;";
    LOGD("Cmd::DBGetAccountByAccountPasswd " << query.str().c_str());

    std::vector<SqlAccount> result;
    query.storein(result);
    if (result.empty())
    {
        query.clear();
        SqlAccount info;
        info.account =account;
        info.sdkId = account;
        info.passwd = passwd;
        std::vector<bool> vb(SqlAccount_NULL, true);
        vb[SqlAccount_id] = false;
        DataDBConnection::makeInsertQuery(query, info, vb);
        mysqlpp::SimpleResult res = query.execute();
        LOGD("Cmd::PARA_REGIST_ACCOUNT_REQ " << query.str().c_str());

        if (!res)
        {
            return false;
        }
    }


    return true;
}

bool CLoginDataTask::DBLoginSessionMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch ( pNullCmd->para )
    {
    case Cmd::PARA_GET_PACKAGECODE_REQ:
            {
                Cmd::t_Get_PackageCode_Req *recv = (Cmd::t_Get_PackageCode_Req*)pNullCmd;
                return DBGetPackageCodeReq(recv);
            }
            return true;
    case Cmd::PARA_PACKAGECODE_REWARD_RES:
        {
            Cmd::t_PackageCode_Reward_Res *recv = (Cmd::t_PackageCode_Reward_Res*)pNullCmd;
            return DBPackageCodeRewardRes(recv);
        }
        return true;
    default:
        return false;
    }

    return false;
}

bool CLoginDataTask::DBGetPackageCodeReq(Cmd::t_Get_PackageCode_Req *recv)
{
    

    return true;
}

bool CLoginDataTask::DBPackageCodeRewardRes(Cmd::t_PackageCode_Reward_Res *recv)
{


    return true;
}


