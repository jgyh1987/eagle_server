#include "LogicDataTask.h"
#include "Defs.h"
#include "CommonType.h"
#include "DelaySaveCmdQueue.h"
#include "LogicDataService.h"
#include "ServerCommand.h"

extern DelaySaveCmdQueue g_delaySaveDBCmdQueue;

bool CLogicDataTask::cmdMsgParse(void *ptNull,const uint32_t nCmdLen)
{
    try
    {
        Cmd::t_NullCmd *pNullCmd = (Cmd::t_NullCmd*)ptNull;
        switch (pNullCmd->cmd) 
        {
            case Cmd::CMD_SERVER_INIT:
                return DBServerInitMessageParase(pNullCmd, nCmdLen);
            case Cmd::CMD_LOGIC_PLAYERINFO:
                return DBLogicPlayerInfoMessageParase(pNullCmd, nCmdLen);
            default:break;
        }
    }
    catch( const mysqlpp::BadQuery& e ) 
    {
        LOGFMTE("LogicDataServer LogicDataTask mysql++ query error: %s errornum= %d", e.what(), e.errnum());
    } 
    catch (const mysqlpp::BadConversion& e ) 
    {
        LOGFMTE("LogicDataServer LogicDataTask mysql++ conversion error: %s, retrieved data size: %llu, actual size: %llu", e.what(), (unsigned long long)e.retrieved, (unsigned long long)e.actual_size);
    } 
    catch (const mysqlpp::Exception& e) 
    {
        LOGFMTE("LogicDataServer LogicDataTask mysql++ general error: %s", e.what());
    } 
    catch (...) 
    {
        LOGE("LogicDataServer LogicDataTask unknown error.");
    }
    
    return false;
}

//DBServerInitMessageParase begin
bool CLogicDataTask::DBServerInitMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch ( pNullCmd->para )
    {
    case Cmd::PARA_SERVER_REGIST_REQ:
        {
            Cmd::t_Server_Regist_Req *recv = (Cmd::t_Server_Regist_Req *)pNullCmd;
			UpdateServerInfo(&recv->info);
            g_pServerImp->AddServerTask(this);

			Cmd::t_Server_Regist_Res send;
			send.res = SUCCESS;
			send.info.serverId = g_serverId;
			strncpy(send.info.serverName, eagle::global["ServerName"].c_str(), sizeof(send.info.serverName));
			send.info.serverType = SERVER_TYPE_LOGIC_DATA;
			SendCmd(&send, sizeof(send));
        }
        return true;
    default:
        return false;
    }

    return false;
}
//DBServerInitMessageParase end

//DBLogicPlayerInfoMessageParase begin
bool CLogicDataTask::DBLogicPlayerInfoMessageParase(const Cmd::t_NullCmd* pNullCmd, const unsigned int nCmdLen)
{
    switch ( pNullCmd->para )
    {
	case Cmd::PARA_DATA_SELECT_SERVER:
		{
			Cmd::t_Data_Select_Server* recv = (Cmd::t_Data_Select_Server*)pNullCmd;
			DBSelectServer(recv);
		}
		return true;
    case Cmd::PARA_DATA_GET_PLAYERINFO_REQ:
        {
            Cmd::t_Data_Get_PlayerInfo_Req *recv = (Cmd::t_Data_Get_PlayerInfo_Req *)pNullCmd;
            DBGetPlayerInfoByAccount(recv);
        }
        return true;
    case Cmd::PARA_DATA_CREATE_ROLEINFO_REQ:
        {
            Cmd::t_Data_Create_RoleInfo_Req *recv = (Cmd::t_Data_Create_RoleInfo_Req *)pNullCmd;
            DBCreateRole(recv);
        }
        return true;
    case Cmd::PARA_DATA_SAVE_PLAYERINFO_REQ:
        {
            Cmd::t_Data_Save_PlayerInfo_Req *recv = (Cmd::t_Data_Save_PlayerInfo_Req *)pNullCmd;
            DBSavePlayerInfo(recv);
        }
        return true;
    //case Cmd::PARA_DATA_SEND_MAIL_REQ:
    //case Cmd::PARA_DATA_DELETE_MAIL_REQ:
    //case Cmd::PARA_DATA_GET_MAIL_LIST_REQ:
    //case Cmd::PARA_DATA_SEND_MAIL_TO_ALL_REQ:
    //    {
    //        g_delaySaveDBCmdQueue.msgParase((void *)pNullCmd, nCmdLen);
    //    }
    //    return true;
    case Cmd::PARA_DATA_GETROLEINFO_REQ:
        {
            Cmd::t_Data_GetRoleInfo_Req *recv = (Cmd::t_Data_GetRoleInfo_Req *)pNullCmd;
            DBGetRoleInfo(recv);
        }
        return true;

    case Cmd::PARA_DATA_DELETEROLE_REQ://
        {
            Cmd::t_Data_DeleteRole_Req *recv = (Cmd::t_Data_DeleteRole_Req *)pNullCmd;
            uint32_t ret = 0;
            Cmd::t_Data_DeleteRole_Res send;
            send.roleId = recv->roleId;
            send.playerId = recv->playerId;
            send.slot = recv->slot;
            if(!DBSetRoleStatus(recv->roleId, ROLESTATUS_DELETE, ret, recv->playerId))
            {
                //TODO 
                LOGE("ERROR------ t_Data_DeleteRole_Req failed ");
            }
            send.ret = ret;
            SendCmd(&send, sizeof(send));
        }
        return true;
    case Cmd::PARA_DATA_SAVE_ROLEINFO_REQ:
        {
            Cmd::t_Data_Save_RoleInfo_Req *recv = (Cmd::t_Data_Save_RoleInfo_Req *)pNullCmd;
            DBSaveRoleInfo(recv);
        }
        return true;
    case Cmd::PARA_DATA_UPDATE_ITEM_REQ:
        {
            Cmd::t_Data_Update_Item_Req *recv = (Cmd::t_Data_Update_Item_Req *)pNullCmd;
            UpdateItemReq(recv);
        }
        return true;
    default:
        return false;
    }

    return false;
}
//DBLogicPlayerInfoMessageParase end


