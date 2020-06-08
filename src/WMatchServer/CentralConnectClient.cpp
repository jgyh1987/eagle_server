#include "CentralConnectClient.h"
#include "Defs.h"

bool CCentralConnectClient::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
{
    Cmd::t_NullCmd *pNullCmd = (Cmd::t_NullCmd*)ptNull;
    switch (pNullCmd->cmd) 
    {
        case Cmd::CMD_SERVER_INIT:
            return ServerInitMessageParase(pNullCmd, nCmdLen);

        default:break;
    }

    return false;
}

void CCentralConnectClient::CallBackConnectSuccessImp()
{
    Cmd::t_Server_Regist_Req send;
    send.info.serverId = g_serverId;
    send.info.port = g_serverPort;
    strncpy(send.info.serverName, eagle::global["ServerName"].c_str(), sizeof(send.info.serverName));
    strncpy(send.info.serverIP, eagle::global["WMatchServerTcpIP"].c_str(), sizeof(send.info.serverIP));
    send.info.serverType = SERVER_TYPE_WMATCH_SERVER;
    SendCmd(&send, sizeof(send));
}

void CCentralConnectClient::CallBackConnectErrorImp()
{

}

bool CCentralConnectClient::ServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch (pNullCmd->para) 
    {
        case Cmd::PARA_SERVER_REGIST_RES:
            {
                Cmd::t_Server_Regist_Res *recv = (Cmd::t_Server_Regist_Res*)pNullCmd;
                if (SUCCESS == recv->res)
                {
                    LOGI("CCentralConnectClient Regist SUCCESS ServerName = " << recv->info.serverName << " !!!");
                }
                else
                {
                    LOGI("CCentralConnectClient Regist ERROR ServerName = " << recv->info.serverName << " !!!");

                }
                    
            }
            return true;
        default:
            break;
    }

    return false;
}
