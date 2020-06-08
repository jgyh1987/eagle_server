#include "WMatchTask.h"
#include "Logger.h"
#include "Stream.h"
#include "WMatchTaskManager.h"
#include "WorldCommand.h"
#include "Defs.h"
#include "WMatchManager.h"
#include "WMatchService.h"

bool CWMatchTask::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
{
    Cmd::t_NullCmd *pNullCmd = (Cmd::t_NullCmd*)ptNull;
    switch (pNullCmd->cmd) 
    {
    case Cmd::CMD_SERVER_INIT:
        return ServerInitMessageParase((Cmd::t_NullCmd*)pNullCmd, nCmdLen);
    case Cmd::CMD_WORLD_MESSAGE:
        return WorldMessageParase((Cmd::t_NullCmd*)pNullCmd, nCmdLen);
    default:break;
    }

    return false;
}

bool CWMatchTask::ServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch (pNullCmd->para) 
    {
    case Cmd::PARA_SERVER_REGIST_REQ:
        {
            Cmd::t_Server_Regist_Req *recv = (Cmd::t_Server_Regist_Req *)pNullCmd;

            if (recv->info.serverType == SERVER_TYPE_PROXY_SERVER)
            {
                Cmd::t_Server_Regist_Res send;
                send.res = SUCCESS;
                send.info.serverType = SERVER_TYPE_WMATCH_SERVER;
                send.info.serverId = g_serverId;
                strncpy(send.info.serverName, eagle::global["ServerName"].c_str(), sizeof(send.info.serverName));

				UpdateGameServerInfo(&recv->info);

                ServerImp()->AddServerTask(this, true);

                SendCmd(&send, sizeof(send));

                LOGI("CWMatchTask ServerRegistReq ServerName = " << recv->info.serverName << " !!!");
            
            }
            else if (recv->info.serverType == SERVER_TYPE_WGATE_SERVER)
            {
                WMatchManager::instance()->AddWGateServer(&recv->info);
                LOGI("CWMatchTask ServerRegistReq ServerName = " << recv->info.serverName << " ServerId = " << recv->info.serverId << " !!!");
            }
            else if (recv->info.serverType == SERVER_TYPE_WGAME_SERVER)
            {
                WMatchManager::instance()->AddWFightServer(&recv->info);
                LOGI("CWMatchTask ServerRegistReq ServerName = " << recv->info.serverName << " ServerId = " << recv->info.serverId << " !!!");
            }

            
        }
        return true;
    case Cmd::PARA_SERVER_LOAD_NOTIFY:
        {
            Cmd::t_Server_Load_Notify *recv = (Cmd::t_Server_Load_Notify *)pNullCmd;
            m_highLoad = recv->loadInfo;
        }
        break;
    case Cmd::PARA_SERVER_INIT_TEST_MSG:
    {
        Cmd::t_ServerInit_Test_Msg *recv = (Cmd::t_ServerInit_Test_Msg *)pNullCmd;
        WFightServerInfo *fightInfo = WMatchManager::instance()->GetWFightServer();
        if (fightInfo)
        {
            ServerImp()->ProxySendCmd(recv, nCmdLen, SERVER_TYPE_WGAME_SERVER, fightInfo->info.serverId);
        }
        

        LOGI("t_ServerInit_Test_Msg WMATCH SERVER !!!");
    }
    break;
    default:
        break;
    }

    return true;
}

bool CWMatchTask::WorldMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch (pNullCmd->para) 
    {
    case Cmd::PARA_WORLD_MATCH_REQ:
    {
        Cmd::t_World_Match_Req *recv = (Cmd::t_World_Match_Req *)pNullCmd;
        WMatchManager::instance()->Match(recv, this);
    }
    break;
    case Cmd::PARA_WORLD_CREATE_FIGHT_RES:
    {
        Cmd::t_World_Create_Fight_Res *recv = (Cmd::t_World_Create_Fight_Res *)pNullCmd;
        WMatchManager::instance()->CreateFightBack(recv);
    }
    break;
    default:
        break;
    }

    return true;
}



