#include "LogDBConnectClient.h"
#include "ServerCommand.h"
#include "Defs.h"

bool CLogDBConnectClient::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
{
    Cmd::t_NullCmd *pNullCmd = (Cmd::t_NullCmd*)ptNull;
    switch (pNullCmd->cmd) 
    {
        case Cmd::CMD_SERVER_INIT:
            return ServerInitMessageParase((Cmd::t_NullCmd*)pNullCmd, nCmdLen);
        default:break;
    }

    return false;
}

void CLogDBConnectClient::CallBackConnectSuccessImp()
{
    Cmd::t_Server_Regist_Req send;
    SendCmd(&send, sizeof(send));

    return;
}

void CLogDBConnectClient::CallBackConnectErrorImp()
{

    return;
}

bool CLogDBConnectClient::ServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch (pNullCmd->para) 
    {
        case Cmd::PARA_SERVER_REGIST_RES:
            {
                LOGI("LogicServer LogDBConnectClient verify success !!!");

                return true;
            }
        default:
            break;
    }

    return false;
}

