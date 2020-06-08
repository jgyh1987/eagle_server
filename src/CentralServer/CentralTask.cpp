#include "CentralTask.h"
#include "Defs.h"
#include "TransMap.h"
#include "CentralService.h"


void CCentralTask::Clear()
{
    m_hreatTime = 0;
    m_highLoad = 0;
    return CServerTaskEx::Clear();
}

bool CCentralTask::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
{
    Cmd::t_NullCmd *pNullCmd = (Cmd::t_NullCmd*)ptNull;
    switch (pNullCmd->cmd) 
    {
        case Cmd::CMD_SERVER_INIT:
            return ServerInitMessageParase(pNullCmd, nCmdLen);
        default:break;
    }

    return true;
}

void CCentralTask::UpdateHreatTime()
{
    m_hreatTime = CImpServerTimeTick::currentTime.sec();

    return;
}

bool CCentralTask::ServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch ( pNullCmd->para )
    {
    case Cmd::PARA_SERVER_REGIST_REQ:
        {
            Cmd::t_Server_Regist_Req *recv = (Cmd::t_Server_Regist_Req *)pNullCmd;
            return ServerRegistReq(recv);
        }
        return true;
    case Cmd::PARA_SERVER_LOAD_NOTIFY:
        {
            Cmd::t_Server_Load_Notify *recv = (Cmd::t_Server_Load_Notify *)pNullCmd;
            m_highLoad = recv->loadInfo;

            UpdateHreatTime();
        }
        return true;
    case Cmd::PARA_SERVER_REQ_PROXYSERVER:
    {
        ServerImp()->NotifyProxyToServer(this);
    }
    return true;
    default:
        return false;
    }

    return false;
}
    
bool CCentralTask::ServerRegistReq(Cmd::t_Server_Regist_Req *recv)
{
    Cmd::t_Server_Regist_Res send;
    send.res = SUCCESS;
    send.info.serverType = SERVER_TYPE_CENTRAL_SERVER;
    send.info.serverId = g_serverId;
    strncpy(send.info.serverName, eagle::global["ServerName"].c_str(), sizeof(send.info.serverName));
    do
    {
        if (GetServerId())
        {
            send.res = SERVER_REPEAT_REGIST;
            break;
        }

        if (recv->info.serverType >= SERVER_TYPE_MAX)
        {
            send.res = SERVER_TYPE_ERROR;
            break;
        }
        
		UpdateGameServerInfo(&recv->info);

		CTransMapManager::instance()->TransNotifyServers(this);
        ServerImp()->AddCentralTask(this);   

        LOGI("CCentralTask ServerRegistReq ServerName = " << recv->info.serverName << " !!!");
    }
    while (false);

    SendCmd(&send, sizeof(send));

    return true;
}




