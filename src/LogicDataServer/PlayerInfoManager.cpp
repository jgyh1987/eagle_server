#include "LogicDataTask.h"
#include "Defs.h"
#include "CommonType.h"
#include "TimeTick.h"
#include "LogicDataPlayer.h"

extern uint32_t g_gmIsOpen;

//
std::vector<SqlRoleInfo> DBGetRolesByPlayerId(const uint64_t playerId)
{
    //
    mysqlpp::Query query = DataDBConnection::instance()->query();
    query << "select * from ROLE_INFO where PLAYERID  =  " << playerId << " AND ROLESTATUS = '0';";
    LOGT("DBGetAllRoleByPlayerId " << query.str().c_str());
    std::vector<SqlRoleInfo> result;
    query.storein(result);
    return result;
}

//
std::vector<SqlPlayerItem> DBGetItemsByRoleId(const uint64_t roleId)
{
    //
    mysqlpp::Query query = DataDBConnection::instance()->query();
    query << "select * from PLAYER_ITEM where ROLEID  =  " << roleId << " AND BAGTYPE != 0 ;";
    LOGT("DBGetItemsByRoleId " << query.str().c_str());
    std::vector<SqlPlayerItem> result;
    query.storein(result);
    return result;
}

bool CLogicDataTask::DBSelectServer(Cmd::t_Data_Select_Server* recv)
{
	auto player = DataPlayerManager::instance()->FindPlayerById(recv->playerId);
	if (player)
	{
		player->UpdateSelectServer(recv->serverType, recv->serverId);
	}

	return true;
}

bool CLogicDataTask::DBGetPlayerInfoByAccount(Cmd::t_Data_Get_PlayerInfo_Req *recv)
{
    DataPlayer *player = NULL;
    if (recv->playerInfo.playerId)
        player = DataPlayerManager::instance()->FindPlayerById(recv->playerInfo.playerId);
    else
        player = DataPlayerManager::instance()->FindPlayerByAccount(recv->playerInfo.account);
        
    if (!player)
    {
        player = new DataPlayer();
        if (player)
            if (player->LoadDB(recv->playerInfo))
                DataPlayerManager::instance()->AddPlayer(player);
            else
                SAFE_DELETE(player)
        
    }

    if (player)
        player->SendPlayerInfoToLogic(this, recv->funType, recv->srcPlayer);
    else
    {
        Cmd::t_Data_Get_PlayerInfo_Res *send = NULL;
        ServerCmdBuffer(send);
		send->playerinfo = recv->playerInfo;
        send->ret = DEFAULT_ERROR;
        SendCmd(send, send->Size());
    }

    return true;
}

bool CLogicDataTask::DBSavePlayerInfo(Cmd::t_Data_Save_PlayerInfo_Req *recv)
{
    DataPlayer *player = DataPlayerManager::instance()->FindPlayerById(recv->playerinfo.playerId);
    if (player && player->IsSelectServer(recv->serverType, recv->serverId))
    {
        player->UpdatePlayerInfo(&recv->playerinfo, recv->data, recv->allBinarrayLength);
    }

    return true;
}

//
bool CLogicDataTask::DBCreateRole(Cmd::t_Data_Create_RoleInfo_Req *recv)
{
    Cmd::t_Data_Create_RoleInfo_Res send;
    send.roleinfo = recv->info;

    DataPlayer *player = DataPlayerManager::instance()->FindPlayerById(recv->info.playerId);
    if (player)
    {
        do
        {
            if (player->m_roleInfos.size() >= player->m_playerInfo.roleSolt)
            {
                send.ret = MAX_ROLE_ERROR;
                break;
            }

            //mysqlpp::Query query = DataDBConnection::instance()->query();
            //query << "select ROLEID from ROLE_INFO where NAME  =  '" << recv->info.name << "' ;";
            //LOGT("CLogicDataTask::DBCreatePlayerInfo " << query.str().c_str());

            //std::vector<SqlRoleInfo> result;
            //query.storein(result);

            //send.ret = SUCCESS;
        
            //if (!result.empty())
            //{
            //    send.ret = NAME_ALREADY_EXISTS;
            //    break;
            //}
            //mysqlpp::Transaction trans(*DataDBConnection::instance()->connection(), mysqlpp::Transaction::serializable, mysqlpp::Transaction::this_transaction);

            DBRoleAllInfo *role = player->CreateRoleInfo(recv);            //ROLE_INFO
            if (role == NULL)
            {
                send.ret = MYSQL_WRITE_ERROR;
                break;
            }
            //trans.commit();

            send.ret = SUCCESS;
            send.roleinfo.roleId = role->roleId;

        } while (false);
    }
    else
    {
        send.ret = DEFAULT_ERROR;
    }

    
    SendCmd(&send, sizeof(send));

    return true;
}

//
bool CLogicDataTask::DBGetRoleInfo(Cmd::t_Data_GetRoleInfo_Req *recv)
{
    DataPlayer *player = DataPlayerManager::instance()->FindPlayerById(recv->playerId);
    if (player)
    {
        player->GetRoleInfo(recv->roleId, this, recv->funType, recv->srcPlayer);
    }
    else
    {
        Cmd::t_Data_GetRoleInfo_Res *send = NULL;
        ServerCmdBuffer(send);
        send->roleInfo.playerId = recv->playerId;
        send->funType = recv->funType;
        send->srcPlayer = recv->srcPlayer;
        send->ret = DEFAULT_ERROR;
        SendCmd(send, send->Size());
    }

    return true;
}

//
bool CLogicDataTask::DBSetRoleStatus(const uint64_t roleId, const uint32_t status, uint32_t &ret, uint64_t playerId)
{
    mysqlpp::Query query = DataDBConnection::instance()->query();
    query << "UPDATE ROLE_INFO SET ROLESTATUS = ' " << status << " ' where ROLEID  =  '" << roleId << "' ;";
    LOGT("Cmd::DBSetRoleStatus " << query.str().c_str());

    mysqlpp::SimpleResult res = query.execute();
    ret = SUCCESS;
    if (!res)
    {
        ret = NO_ROLEINFO;
        return false;
    }

    DataPlayer *player = DataPlayerManager::instance()->FindPlayerById(playerId);
    if (player)
    {
        player->UpdateRoleStatus(roleId, status);
    }

    return true;
}

//
bool CLogicDataTask::DBSaveRoleInfo(Cmd::t_Data_Save_RoleInfo_Req *recv)
{
    Cmd::t_Data_Save_RoleInfo_Res send;
    send.playerId = recv->playerinfo.playerId;
    DataPlayer *player = DataPlayerManager::instance()->FindPlayerById(recv->playerinfo.playerId);
    if (player && player->IsSelectServer(recv->serverType, recv->serverId))
    {
        send.ret = player->UpdateRoleInfo(recv);
    }
    else
    {
        send.ret = DEFAULT_ERROR;
    }
    SendCmd(&send, sizeof(send));
    return true;
}

bool CLogicDataTask::UpdateItemReq(Cmd::t_Data_Update_Item_Req *recv)
{
    Cmd::t_Data_Update_Item_Res *send;
    ServerCmdBuffer(send);
    send->ret = DEFAULT_ERROR;
    send->playerId = recv->playerId;
    send->roleId = recv->roleId;

    DataPlayer *player = DataPlayerManager::instance()->FindPlayerById(recv->playerId);
    if (player && player->IsSelectServer(recv->serverType, recv->serverId))
    {
        DBRoleAllInfo *role = player->FindRoleById(recv->roleId);
        if (role)
        {
            if (player->CheckItems(role, recv->data, recv->itemsCount, recv->itemsDataLen))
            {
                player->ChangeItems(role, recv->data, recv->itemsCount, recv->itemsDataLen);
                send->ret = SUCCESS;
            }
        }
    }

    if (SUCCESS == send->ret)
    {
        send->itemsCount = recv->itemsCount;
        send->itemsDataLen = recv->itemsDataLen;
        memcpy(send->data, recv->data, recv->itemsDataLen);
    }

    SendCmd(send, send->Size());

    return true;
}
