#include "LoginClientTask.h"
#include "ClientMsg.h"
#include "Stream.h"
#include "Defs.h"
#include "LoginServerCommand.h"
#include "ServerCommand.h"
#include "LogicLoginCommand.h"
#include "ToolsFun.h"
#include "TimeTick.h"
#include "AccountManager.h"
#include "ServeListManager.h"
#include "LoginService.h"
#include "LoginTask.h"

char g_sdkstr[SDK_TYPE_MAX][MAX_ACCOUNT_LENGHT] = {
    "eagle_",
    "eagle_"
};

CLoginClientTask::~CLoginClientTask()
{
}

void CLoginClientTask::Clear()
{
    m_connectTime = 0;
    m_accountInfo = NULL;

    return CClientTask::Clear();
}

bool CLoginClientTask::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
{
    //protocol::PackageNet stream;
    //stream.ParseFromArray(ptNull, (int)nCmdLen);
    //uint32_t id = stream.id() / PROTOCOL_ID_MASK;

    //switch (stream.id())
    //{
    //case protocol::cs_heartBeat:
    //    break;
    //case protocol::cs_login:
    //    {
    //        C2SLoginAccountReq((void *)stream.body().c_str(), (int)stream.body().size());
    //    }
    //    break;
    //case protocol::cs_selectGameServer:
    //    {
    //        C2SSelectServerReq((void *)stream.body().c_str(), (int)stream.body().size());
    //    }
    //    break;
    //default:
    //    break;
    //}


    BinaryReadStream stream((const char*)ptNull, nCmdLen);
    ClientMsg::Message message;
    if (message.Unserialize(&stream) != 0)
    {
        LOGFMTE("msg Unserialize Error, len :%d", nCmdLen);
        return false;
    }

    switch (message.majorCmd)
    {

    case ClientMsg::LoginCommand::MAJOR_CMD:
    {
        switch (message.minorCmd)
            {
            //case ClientMsg::RegistAccountReq::MINOR_CMD:    
            //    {
            //        stream.Reset();
            //        ClientMsg::RegistAccountReq msg;
            //        if (msg.Unserialize(&stream) != 0)
            //        {
            //            LOGFMTE("ClientMsg::RegistAccountReq msg Unserialize Error, len :%d", nCmdLen);
            //            return false;
            //        }
            //        LOGFMTD("ClientMsg::RegistAccountReq success %s, %s", msg.account.c_str(), msg.passwd.c_str());

            //        C2SRegistAccountReq(msg);
            //    }
            //    break;
            case ClientMsg::LoginSessionReq::MINOR_CMD:
                {
                    stream.Reset();
                    ClientMsg::LoginSessionReq msg;
                    if (msg.Unserialize(&stream) != 0)
                    {
                        LOGFMTE("ClientMsg::LoginAccountReq msg Unserialize Error, len :%d", nCmdLen);
                        return false;
                    }
                    LOGFMTT("ClientMsg::LoginAccountReq success %s, %s", msg.openid.c_str(), msg.openkey.c_str());

                    if (msg.sdkType >= SDK_TYPE_MAX)
                        return false;

                    std::string account(g_sdkstr[msg.sdkType]);
                    account.append(msg.openid);

                    SAccountInfo* pInfo = CAccountManager::instance()->GetAccountInfo(account);
                    if (pInfo)
                    {
                        pInfo->task = this;
                        m_accountInfo = pInfo;

                        if (pInfo->isVerify)
                        {
                            ClientMsg::LoginSessionAccountRes res;
                            res.ret = SUCCESS;
                            res.account = pInfo->account;
                            SendClientMsg(&res);

                            break;
                        }
                    }
                    else
                    {
                        pInfo = new SAccountInfo();
                        pInfo->account = account;
                        pInfo->skdId = msg.openid;
                        pInfo->token = msg.openkey;
                        pInfo->task = this;
                        m_accountInfo = pInfo;
                        CAccountManager::instance()->AddAccountInfo(pInfo);
                    }

                    Cmd::t_Login_Account_Req send;
                    strncpy(send.account, pInfo->account.c_str(), MAX_ACCOUNT_LENGHT - 1);
                    strncpy(send.sdkId, pInfo->skdId.c_str(), MAX_ACCOUNT_LENGHT - 1);
                    strncpy(send.token, pInfo->token.c_str(), MAX_SDK_OPENKEY_LENGHT - 1);
                    send.sdkType = msg.sdkType;
                    SendToDB(&send, sizeof(send));
                }
                break;
            case ClientMsg::SelectServerReq::MINOR_CMD://
                {
                    stream.Reset();
                    ClientMsg::SelectServerReq msg;
                    if (msg.Unserialize(&stream) != 0)
                    {
                        LOGFMTE("ClientMsg::SelectServerReq msg Unserialize Error, len :%d", nCmdLen);
                        return false;
                    }
                    //C2SSelectServerReq(msg);

                    ClientMsg::SelectServerRes send;
                    CLoginTask *server = GetServerImp()->FindLoginTask(msg.gameServerID);
                    if (!server || !m_accountInfo)
                    {
                        send.ret = NO_SERVERID_ERROR;
                        SendClientMsg(&send);
                    }
                    else
                    {
                        Cmd::t_Send_Session_Sync send;
                        strncpy(send.account, m_accountInfo->account.c_str(), MAX_ACCOUNT_LENGHT - 1);
                        strncpy(send.session, m_accountInfo->account.c_str(), MAX_ACCOUNT_LENGHT - 1);
                        server->SendCmd(&send, sizeof(send));
                    }
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

bool CLoginClientTask::SendClientMsg(ClientMsg::Message *message)
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

bool CLoginClientTask::SendClientMsg(::google::protobuf::Message *message, int id)
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

//
bool CLoginClientTask::C2SLoginAccountReq(void *data, int size)
{
    protocol::LoginReqNet stream;
    stream.ParseFromArray(data, size);

    protocol::LoginRspNet res;
    if (stream.uid().length() >= MAX_ACCOUNT_LENGHT)
    {
        res.set_ret(INPUT_CHARACTER_LENGTH_MAX);
        SendClientMsg(&res, protocol::sc_login);
        return true;
    }

    if (stream.logintype() >= SDK_TYPE_MAX)
    {
        res.set_ret(SDKTYPE_ERROR);
        SendClientMsg(&res, protocol::sc_login);
        return true;
    }

    std::string account(g_sdkstr[stream.logintype()]);
    account.append(stream.uid());
    SAccountInfo* pInfo = CAccountManager::instance()->GetAccountInfo(account);
    if (pInfo)
    {
        pInfo->task = this;
        m_accountInfo = pInfo;
        res.set_ret(SUCCESS);
        res.set_account(account);
        SendClientMsg(&res, protocol::sc_login);
    }
    else
    {
        pInfo = new SAccountInfo();
        pInfo->account = account;
        pInfo->skdId = stream.uid();
        pInfo->token = stream.sdktoken();
        pInfo->session = stream.sdksession();
        pInfo->task = this;
        m_accountInfo = pInfo;
        CAccountManager::instance()->AddAccountInfo(pInfo);

        Cmd::t_Login_Account_Req send;
        strncpy(send.account, pInfo->account.c_str(), MAX_ACCOUNT_LENGHT - 1);
        strncpy(send.sdkId, pInfo->skdId.c_str(), MAX_ACCOUNT_LENGHT - 1);
        strncpy(send.token, pInfo->token.c_str(), MAX_SDK_OPENKEY_LENGHT - 1);
        send.sdkType = stream.logintype();
        SendToDB(&send, sizeof(send));
        
    }

    //if (msg.account.size() >= MAX_ACCOUNT_LENGHT || msg.passwd.size() >= MAX_PASSWD_LENGHT)
    //{
    //    ClientMsg::RegistAccountRes res;
    //    res.ret = INPUT_CHARACTER_LENGTH_MAX;
    //    SendClientMsg(&res);
    //    return false;
    //}
    //
    //if (msg.sdkType >= SDK_TYPE_MAX)
    //{
    //    ClientMsg::RegistAccountRes res;
    //    res.ret = SDKTYPE_ERROR;
    //    SendClientMsg(&res);
    //    return true;
    //}

    //std::string account(g_sdkstr[msg.sdkType]);
    //account.append(msg.account);

    //SAccountInfo* pinfo = CAccountManager::instance()->GetAccountInfo(account);
    //if (pinfo)
    //{
    //    ClientMsg::LoginSessionAccountRes res;
    //    res.ret = SUCCESS;
    //    //if (pinfo->passwd.compare(msg.passwd) != 0)
    //    //{
    //        ////�������
    //        //res.ret = PASSWD_NOT_TRUE;
    //    //}
    //    res.account = account;
    //    SendClientMsg(&res);
    //}
    //else
    //{
    //    Cmd::t_Login_Account_Req send;
    //    strncpy(send.account, account.c_str(), MAX_ACCOUNT_LENGHT - 1);
    //    strncpy(send.passwd, msg.passwd.c_str(), MAX_PASSWD_LENGHT - 1);
    //    send.uid = GetUid();
    //    SendToDB(&send, sizeof(send));
    //}
    return true;
}

//ѡ�������
bool CLoginClientTask::C2SSelectServerReq(void *data, int size)
{
    protocol::SelectGameServerReqNet stream;
    stream.ParseFromArray(data, size);

    protocol::SelectGameServerRspNet res;
    res.set_ret(SUCCESS);
    if (!m_accountInfo)
    {
        res.set_ret(NO_LOGIN_ERROR);
        SendClientMsg(&res, protocol::sc_selectGameServer);
    }
    else
    {
        CLoginTask *server = GetServerImp()->FindLoginTask(stream.gameserverid());
        if (!server)
        {
            res.set_ret(NO_SERVERID_ERROR);
            SendClientMsg(&res, protocol::sc_selectGameServer);
        }
        else
        {
            Cmd::t_Send_Session_Sync send;
            strncpy(send.account, m_accountInfo->account.c_str(), MAX_ACCOUNT_LENGHT - 1);
            strncpy(send.session, m_accountInfo->account.c_str(), MAX_ACCOUNT_LENGHT - 1);
            server->SendCmd(&send, sizeof(send));
        }
    }


    return true;
}
