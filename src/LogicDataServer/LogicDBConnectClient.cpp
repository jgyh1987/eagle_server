#include "LogicDBConnectClient.h"
#include "Defs.h" 
#include "LogicDataService.h"
#include "ServerCommand.h"

bool CLogicDBConnectClient::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
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

void CLogicDBConnectClient::CallBackConnectSuccessImp()
{
    Cmd::t_Server_Regist_Req send;
    send.info.serverId = g_serverId;
    strncpy(send.info.serverName, eagle::global["ServerName"].c_str(), sizeof(send.info.serverName));
    strncpy(send.info.serverIP, eagle::global["ProxyServerTcpIp"].c_str(), sizeof(send.info.serverIP));
    send.info.serverType = SERVER_TYPE_LOGIC_DATA;
    SendCmd(&send, sizeof(send));


}

void CLogicDBConnectClient::CallBackConnectErrorImp()
{

}

bool CLogicDBConnectClient::ServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch (pNullCmd->para) 
    {
        case Cmd::PARA_SERVER_REGIST_RES:
            {
                Cmd::t_Server_Regist_Res *recv = (Cmd::t_Server_Regist_Res*)pNullCmd;
                if (SUCCESS == recv->res)
                {
					LOGI("CLogicDBConnectClient Regist SUCCESS ServerName = " << recv->info.serverName << " !!!");
                }    
                else
                {
                    LOGI("CLogicDBConnectClient Regist ERROR ServerName = " << recv->info.serverName << " !!!");
                }
                    
            }
            return true;

        default:
            break;
    }

    return false;
}
