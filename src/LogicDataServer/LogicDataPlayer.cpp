#include "LogicDataPlayer.h"
#include "Defs.h"
#include "LogicDataTask.h"
#include "TimeTick.h"
#include "CObject.h"
#include "CommonType.h"
#include "ImpService.h"

#define PLAYER_SAVE_INTERVAL 60 //900

std::vector<SqlRoleInfo> DBGetRolesByPlayerId(const uint64_t playerId);
std::vector<SqlPlayerItem> DBGetItemsByRoleId(const uint64_t roleId);

//

//DataPlayer
DataPlayer::DataPlayer()
    :m_dataLen(0), m_data(NULL), m_serverId(0), m_lastSaveTime(0), m_needSavePlayer(false)
{

}

DataPlayer::~DataPlayer()
{
    if (m_data)
        delete[]m_data;

    for (auto v : m_roleInfos)
    {
        delete v;
    }
    m_roleInfos.clear();
}

void DataPlayer::UpdateSelectServer(uint32_t serverType, uint32_t serverId)
{
	m_serverId = serverId;
	m_serverType = serverType;

	return;
}

bool DataPlayer::IsSelectServer(uint32_t serverType, uint32_t serverId)
{
    if (serverId == m_serverId && m_serverType == serverType)
        return true;

    return false;
}

void DataPlayer::Update()
{

}

bool DataPlayer::LoadDB(PlayerInfoBase &playerInfo)
{
    //m_playerInfo.playerId = GetObjectUid();
    //m_playerInfo.roleSolt = playerInfo.roleSolt = MAX_ROLE_NUM;
    //strncpy(m_playerInfo.account, playerInfo.account, MAX_ACCOUNT_LENGHT - 1);

    //return true;

	m_playerInfo.gatewayServerId = playerInfo.gatewayServerId;
	m_playerInfo.dbServerId = g_serverId;

    mysqlpp::Query query = DataDBConnection::instance()->query();
    if (playerInfo.playerId)
        query << "select * from PLAYER_INFO where PLAYERID  =  " << playerInfo.playerId << " ;";
    else
        query << "select * from PLAYER_INFO where ACCOUNT  =  '" << playerInfo.account << "' ;";

    LOGD("DataPlayer::LoadDB " << query.str().c_str());

    std::vector<SqlPlayerInfo> result;
    query.storein(result);

    if (result.empty())
    {
        //
        if (!CreatePlayer(playerInfo))
        {
            return false;
        }
    }
    else
    {
        std::vector<SqlRoleInfo> roleresult = DBGetRolesByPlayerId(result[0].playerId);

        if (!roleresult.empty())
        {
            //
            m_roleInfos.resize(roleresult.size(), NULL);

            for (size_t i = 0; (i < roleresult.size() && i < MAX_BUY_ROLE_NUM); ++i)
            {
                m_roleInfos[i] = new DBRoleAllInfo();
                //if(ROLESTATUS_DEFUAL == roleresult[i].status)
                {
                    //m_roleInfos[i]->status = roleresult[i].status;
                    m_roleInfos[i]->roleId = roleresult[i].roleId;
                    m_roleInfos[i]->playerId = roleresult[i].playerId;
                    m_roleInfos[i]->jobId = roleresult[i].jobId;
                    m_roleInfos[i]->level = roleresult[i].level;
                    m_roleInfos[i]->mapId = roleresult[i].mapId;
					m_roleInfos[i]->pos.x = roleresult[i].x;
					m_roleInfos[i]->pos.y = roleresult[i].y;
					m_roleInfos[i]->pos.z = roleresult[i].z;
					m_roleInfos[i]->pos.dirx = roleresult[i].dirx;
					m_roleInfos[i]->pos.diry = roleresult[i].diry;
					m_roleInfos[i]->pos.dirz = roleresult[i].dirz;
                    m_roleInfos[i]->functionOpenBitMap = roleresult[i].functionOpenBitMap;
                    m_roleInfos[i]->otherFunOpenBitMap = roleresult[i].otherFunOpenBitMap;
                    m_roleInfos[i]->exp = roleresult[i].exp;
                    m_roleInfos[i]->fight = roleresult[i].fight;
                    strncpy(m_roleInfos[i]->name, roleresult[i].name.c_str(), MAX_PLAYER_NAME - 1);

                    if (roleresult[i].allbinary.is_null() == false)
                    {
                        m_roleInfos[i]->dataLen = (uint32_t)roleresult[i].allbinary.size();
                        m_roleInfos[i]->data = new char[m_roleInfos[i]->dataLen];
                        memcpy(m_roleInfos[i]->data, (const char*)(roleresult[i].allbinary), m_roleInfos[i]->dataLen);
                    }
                }

                //
                {
                    std::vector<SqlPlayerItem> itemeresult = DBGetItemsByRoleId(m_roleInfos[i]->roleId);
                    for (size_t j = 0; j < itemeresult.size(); ++j)
                    {
                        ItemChangeData *data = NULL;
                        if (itemeresult[j].allbinary.is_null() == false)
                        {
                            data = new (new char[sizeof(ItemChangeData) + itemeresult[j].allbinary.size()])ItemChangeData();
                            data->len = (uint32_t)itemeresult[j].allbinary.size();
                            memcpy(data->data, (const char*)(itemeresult[j].allbinary), data->len);
                        }
                        else
                        {
                            data = new ItemChangeData();
                        }
                        
                        data->itemId = itemeresult[j].itemId;
                        data->roleId = itemeresult[j].roleId;
                        data->configId = itemeresult[j].configId;
                        data->type = itemeresult[j].itemType;
                        data->count = itemeresult[j].itemCount;
                        data->change = ITEM_CHANGE_STATUS_LOAD;
                        data->bagType = itemeresult[j].bagType;
                        m_roleInfos[i]->items[data->itemId] = data;
                    }
                }
            }
        }

        m_playerInfo.playerId = result[0].playerId;
        m_playerInfo.vipLevel = result[0].vipLevel;
        m_playerInfo.isRoBot = result[0].isRobot;
        m_playerInfo.lastOffTime = result[0].lastoffTime;
        m_playerInfo.authority = result[0].authority;
        m_playerInfo.roleSolt = result[0].roleSolt;

        //
        if (result[0].allbinary.is_null() == false)
        {
            m_dataLen = (uint32_t)result[0].allbinary.size();
            m_data = new char[m_dataLen];
            
            memcpy(m_data, (const char*)(result[0].allbinary), m_dataLen);
        }
    }
    
    strncpy(m_playerInfo.account, playerInfo.account, MAX_ACCOUNT_LENGHT - 1);

    return true;
}

bool DataPlayer::SaveDB(bool removeNewItem)
{
    mysqlpp::Transaction trans(*DataDBConnection::instance()->connection(), mysqlpp::Transaction::serializable, mysqlpp::Transaction::this_transaction);

    if (m_needSavePlayer)
    {
        if (!SavePlayerInfoDB())
        {
            LOGE("SavePlayerInfoDB Error Account = " << m_playerInfo.account << "  !!!");
            return false;
        }

        if (!SaveRoleInfoDB())
        {
            LOGE("SaveRoleInfoDB Error Account = " << m_playerInfo.account << "  !!!");
            return false;
        }
    }
        
    trans.commit();

    for (uint32_t i = 0; i < m_roleInfos.size(); ++i)
    {
        if (m_roleInfos[i])
        {
            for (auto itr = m_roleInfos[i]->items.begin(); itr != m_roleInfos[i]->items.end();)
            {
                if (ITEM_CHANGE_STATUS_DEL == itr->second->change)
                {
                    m_roleInfos[i]->items.erase(itr++);
                }
                else
                {
                    itr->second->change = ITEM_CHANGE_STATUS_LOAD;
                    ++itr;
                }

            }

            for (auto itr = m_roleInfos[i]->newItems.begin(); itr != m_roleInfos[i]->newItems.end();)
            {
                if (ITEM_CHANGE_STATUS_DEL == itr->second->change)
                {
                    m_roleInfos[i]->newItems.erase(itr++);
                }
                else
                {
                    itr->second->change = ITEM_CHANGE_STATUS_LOAD;

                    if (removeNewItem)
                        m_roleInfos[i]->items[itr->second->itemId] = itr->second;

                    ++itr;
                }
            }

            if (removeNewItem)
                m_roleInfos[i]->newItems.clear();
        }
    }

    return true;
}

void DataPlayer::SendPlayerInfoToLogic(CLogicDataTask *task, uint32_t funType, uint64_t srcPlayer)
{
    Cmd::t_Data_Get_PlayerInfo_Res *send = NULL;
    task->ServerCmdBuffer(send);

    send->funType = funType;
    send->srcPlayer = srcPlayer;
    send->ret = SUCCESS;

    send->playerinfo = m_playerInfo;

    memcpy(send->data, m_data, m_dataLen);
    send->allBinarrayLength = m_dataLen;
    send->playerDataLen = m_dataLen;

    uint32_t len = 0;
    SerializeRoleSimpleInfo(send->data + send->allBinarrayLength, len);
    send->allBinarrayLength += len;

    task->SendCmd(send, send->Size());

	UpdateSelectServer(task->GetServerType(), task->GetServerId());

    return;
}

void DataPlayer::SerializeRoleSimpleInfo(uint8_t *ptr, uint32_t &len)
{
    uint32_t size = 0;
    uint8_t *buff = ptr;
    uint32_t *length = (uint32_t *)buff;
    BuffWriteMoveLen(buff, size, UINT32_LEN);
    uint32_t *roleCount = (uint32_t *)buff;
    *roleCount = 0;
    BuffWriteMoveLen(buff, size, UINT32_LEN);

    for (size_t i = 0; i < m_roleInfos.size(); i++)
    {
        if (m_roleInfos[i])
        {
            ++*roleCount;

            memcpy(buff, m_roleInfos[i], sizeof(RoleInfoBase));
            BuffWriteMoveLen(buff, size, sizeof(RoleInfoBase));
        }
    }

    len = *length = size;

    return;
}

void DataPlayer::GetRoleInfo(uint64_t roleId, CLogicDataTask *task, uint32_t funType, uint64_t srcPlayer)
{
    SaveDB(true);

    Cmd::t_Data_GetRoleInfo_Res *send = NULL;
    task->ServerCmdBuffer(send);
    send->roleInfo.playerId = m_playerInfo.playerId;
    send->funType = funType;
    send->srcPlayer = srcPlayer;

    send->ret = DEFAULT_ERROR;

    DBRoleAllInfo *roleInfo = FindRoleById(roleId);
    if (roleInfo)
    {
        send->ret = SUCCESS;
        send->roleInfo = *roleInfo;

        if (roleInfo->dataLen)
        {
            memcpy(send->data, (const char*)(roleInfo->data), roleInfo->dataLen);
            send->allBinarrayLength = roleInfo->dataLen;
        }

        uint8_t *ptr = send->data + send->allBinarrayLength;
        for (auto &itr : roleInfo->items)
        {
            ItemChangeData *data = (ItemChangeData *)ptr;
            memcpy(data, itr.second, itr.second->Size());
            ++send->itemsCount;
            send->itemsLen += itr.second->Size();
            ptr += itr.second->Size();
        }

        for (auto &itr : roleInfo->newItems)
        {
            ItemChangeData *data = (ItemChangeData *)ptr;
            memcpy(data, itr.second, itr.second->Size());
            ++send->itemsCount;
            send->itemsLen += itr.second->Size();
            ptr += itr.second->Size();
        }
    }

    task->SendCmd(send, send->Size());

	UpdateSelectServer(task->GetServerType(), task->GetServerId());

    return;
}

DBRoleAllInfo *DataPlayer::FindRoleById(uint64_t roleId)
{
    for (uint32_t i = 0; i < m_roleInfos.size(); ++i)
    {
        if (m_roleInfos[i] && roleId == m_roleInfos[i]->roleId)
        {
            return m_roleInfos[i];
        }
    }

    return NULL;
}

void DataPlayer::UpdatePlayerInfo(PlayerInfoBase* info, uint8_t *data, uint32_t dataLen)
{
    m_playerInfo.lastOffTime = info->lastOffTime;

    if (dataLen)
    {
        if(m_data)
            delete[]m_data;
        m_dataLen = dataLen;
        m_data = new char[m_dataLen];
        memcpy(m_data, data, m_dataLen);
    }
    
    m_needSavePlayer = true;
}

DBRoleAllInfo *DataPlayer::CreateRoleInfo(Cmd::t_Data_Create_RoleInfo_Req *recv)
{
    DBRoleAllInfo *role = NULL;
    mysqlpp::Query query = DataDBConnection::instance()->query();
    SqlRoleInfo roleInfo;
    roleInfo.playerId = recv->info.playerId;
    roleInfo.name = recv->info.name;
    roleInfo.jobId = recv->info.jobId;
    roleInfo.level = recv->info.level;
    roleInfo.createTime = (mysqlpp::sql_int)CImpServerTimeTick::currentTime.sec();

    std::vector<bool> vb(SqlRoleInfo_NULL, false);
    vb[SqlRoleInfo_playerId] = true;
    vb[SqlRoleInfo_name] = true;
    vb[SqlRoleInfo_jobId] = true;
    vb[SqlRoleInfo_level] = true;
    vb[SqlRoleInfo_createTime] = true;

    DataDBConnection::makeInsertQuery(query, roleInfo, vb);
    LOGD("CLogicDataTask::DBCreatePlayerInfo " << query.str().c_str());
    mysqlpp::SimpleResult res = query.execute();
    if (res)
    {
        role = new DBRoleAllInfo();
        role->playerId = recv->info.playerId;
        memcpy(role->name, recv->info.name, MAX_PLAYER_NAME);
        role->jobId = recv->info.jobId;
        role->level = recv->info.level;
        role->createTime = CImpServerTimeTick::currentTime.sec();
        role->roleId = res.insert_id();

        m_roleInfos.push_back(role);
    }

    return role;
}

void DataPlayer::UpdateRoleStatus(uint64_t roleId, uint32_t status)
{
    if (status == 1)
    {
        for (auto itr = m_roleInfos.begin(); itr != m_roleInfos.end(); ++itr)
        {
            if (*itr && roleId == (*itr)->roleId)
            {
                if (SaveDB())
                {
                    delete *itr;
                    m_roleInfos.erase(itr);
                }

                break;
            }
        }

        return;
    }

    for (uint32_t i = 0; i < m_roleInfos.size(); ++i)
    {
        if (m_roleInfos[i] && roleId == m_roleInfos[i]->roleId)
        {
            m_roleInfos[i]->status = status;
        }
    }

    return;
}

bool DataPlayer::UpdateRoleInfo(Cmd::t_Data_Save_RoleInfo_Req *recv)
{
    uint8_t *ptr = recv->data;

    DBRoleAllInfo *role = FindRoleById(recv->roleInfo.roleId);
    if (!role)
        return false;

    UpdatePlayerInfo(&recv->playerinfo, ptr, recv->playerDataLen);
    ptr += recv->playerDataLen;

    role->lastOffTime = recv->roleInfo.lastOffTime;
    role->jobId = recv->roleInfo.jobId;
    role->mapId = recv->roleInfo.mapId;
	role->pos = recv->roleInfo.pos;
    role->level = recv->roleInfo.level;
    role->exp = recv->roleInfo.exp;
    role->fight = recv->roleInfo.fight;
    role->functionOpenBitMap = recv->roleInfo.functionOpenBitMap;
    role->otherFunOpenBitMap = recv->roleInfo.otherFunOpenBitMap;

    if (recv->roleDataLen)
    {
        SAFE_DELETE(role->data)

        role->data = new char[recv->roleDataLen];
        memcpy(role->data, ptr, recv->roleDataLen);
        role->dataLen = recv->roleDataLen;
    }

    role->needSave = true;

    return true;
}


bool DataPlayer::CheckItems(DBRoleAllInfo *role, uint8_t *ptr, uint32_t count, uint32_t len)
{
    uint8_t *temp = ptr;
    for (uint32_t i = 0; i > count; ++i)
    {
        ItemChangeData *info = (ItemChangeData *)temp;
        if (!CheckItem(role, info))
            return false;

        temp += info->Size();
    }


    return true;
}

bool DataPlayer::CheckItem(DBRoleAllInfo *role, ItemChangeData *info)
{
    if (info->change == ITEM_CHANGE_STATUS_SUB)
    {
        if (!HaveItem(role, info))
            return false;

        return true;
    }

    if (ITEM_CHANGE_STATUS_ADD == info->change || ITEM_CHANGE_STATUS_UPDATE == info->change || ITEM_CHANGE_STATUS_DEL == info->change || ITEM_CHANGE_STATUS_MOVE == info->change)
    {
        auto item = FindItem(info, role);
        if (!item)
            return false;

        if (ITEM_CHANGE_STATUS_DEL == item->change)
            return false;

        return true;
    }

    if (ITEM_CHANGE_STATUS_NEW == info->change)
    {
        auto item = FindItem(info, role);
        if (item)
            return false;
    }

    return true;
}

bool DataPlayer::ChangeItems(DBRoleAllInfo *role, uint8_t *ptr, uint32_t count, uint32_t len)
{
    m_needSavePlayer = true;
    if (role)
        role->needSave = true;
    uint8_t *temp = ptr;
    for (uint32_t i = 0; i < count; ++i)
    {
        ItemChangeData *info = (ItemChangeData *)temp;
        ChangeItem(role, info);
        temp += info->Size();
    }

    return true;
}

bool DataPlayer::ChangeItem(DBRoleAllInfo *role, ItemChangeData *info)
{
    m_needSavePlayer = true;
    if (role)
        role->needSave = true;

    if (ITEM_CHANGE_STATUS_NEW == info->change)
    {
        ItemChangeData *tempInfo = new (new char[info->Size()])ItemChangeData();
        memcpy(tempInfo, info, info->Size());
            role->newItems[tempInfo->uid] = tempInfo;
            tempInfo->roleId = role->roleId;

        return true;
    }


    if (ITEM_CHANGE_STATUS_SUB == info->change)
    {
        auto item = FindItem(info, role);
        if (item && item->change != ITEM_CHANGE_STATUS_DEL)
        {
            item->count -= info->count;
            if (item->change != ITEM_CHANGE_STATUS_NEW)
                item->change = ITEM_CHANGE_STATUS_UPDATE;
            return true;
        }
    
        return false;
    }

    if (ITEM_CHANGE_STATUS_ADD == info->change)
    {
        auto item = FindItem(info, role);
        if (item && item->change != ITEM_CHANGE_STATUS_DEL)
        {
            item->count += info->count;
            if (item->change != ITEM_CHANGE_STATUS_NEW)
                item->change = ITEM_CHANGE_STATUS_UPDATE;
            return true;
        }

        return false;
    }

    if (ITEM_CHANGE_STATUS_DEL == info->change)
    {
        auto item = FindItem(info, role);
        if (item && item->change != ITEM_CHANGE_STATUS_DEL)
        {
            item->change = ITEM_CHANGE_STATUS_DEL;

            return true;
        }

        return false;
    }

    if (ITEM_CHANGE_STATUS_MOVE == info->change)
    {
        auto item = FindItem(info, role);
        if (item && item->change != ITEM_CHANGE_STATUS_DEL)
        {
            item->bagType = info->bagType;
            if (item->change != ITEM_CHANGE_STATUS_NEW)
                item->change = ITEM_CHANGE_STATUS_UPDATE;

            return true;
        }

        return false;
    }

    if (ITEM_CHANGE_STATUS_UPDATE == info->change)
    {
        ItemChangeData *oldInfo = NULL;
        ItemChangeData *tempInfo = NULL;
        auto itr = role->items.find(info->itemId);
        if (itr != role->items.end())
        {
            if (itr->second->change == ITEM_CHANGE_STATUS_DEL)
            {
                return false;
            }
                    
            oldInfo = itr->second;

            tempInfo = (ItemChangeData *)new char[info->Size()];
            *tempInfo = *oldInfo;
            memcpy(tempInfo->data, info->data, info->len);
            tempInfo->change = ITEM_CHANGE_STATUS_UPDATE;
            role->items[tempInfo->itemId] = tempInfo;
            delete oldInfo;

            return true;
        }
        else
        {
            itr = role->newItems.find(info->uid);
            if (itr != role->newItems.end())
            {
                if (itr->second->change == ITEM_CHANGE_STATUS_DEL)
                {
                    return false;
                }

                oldInfo = itr->second;
                tempInfo = (ItemChangeData *)new char[info->Size()];
                *tempInfo = *oldInfo;
                memcpy(tempInfo->data, info->data, info->len);
                if (tempInfo->change != ITEM_CHANGE_STATUS_NEW)
                    tempInfo->change = ITEM_CHANGE_STATUS_UPDATE;
                role->newItems[tempInfo->uid] = tempInfo;
                delete oldInfo;

                return true;
            }
        }
    }

    return false;
}

bool DataPlayer::HaveItem(DBRoleAllInfo *role, ItemChangeData *info)
{
    auto item = FindItem(info, role);

    if (!item)
        return false;

    if (item->change == ITEM_CHANGE_STATUS_DEL)
        return false;

    if (item->count < info->count)
    {
        return false;
    }

    return true;
}

bool DataPlayer::CreatePlayer(PlayerInfoBase &createPlayerInfo)
{
    mysqlpp::Transaction trans(*DataDBConnection::instance()->connection(), mysqlpp::Transaction::serializable, mysqlpp::Transaction::this_transaction);

    mysqlpp::Query query = DataDBConnection::instance()->query();
    SqlPlayerInfo playerInfo;
    playerInfo.account = createPlayerInfo.account;
    playerInfo.authority = atoi(eagle::global["GMIsOpen"].c_str());
    playerInfo.roleSolt = MAX_ROLE_NUM;
    std::vector<bool> vb(SqlPlayerInfo_NULL, false);
    vb[SqlPlayerInfo_account] = true;
    vb[SqlPlayerInfo_authority] = true;
    vb[SqlPlayerInfo_roleSolt] = true;

    DataDBConnection::makeInsertQuery(query, playerInfo, vb);
    LOGT("DataPlayer::CreatePlayer " << query.str().c_str());
    mysqlpp::SimpleResult res = query.execute();

    if (res)
    {
        mysqlpp::Query query1 = DataDBConnection::instance()->query();
        SqlPlayerCreateInfo playerCreateInfo;
        playerCreateInfo.account = createPlayerInfo.account;
        playerCreateInfo.playerId = res.insert_id();
        playerCreateInfo.createTime = (mysqlpp::sql_int)CImpServerTimeTick::currentTime.sec();
        std::vector<bool> vb1(SqlPlayerCreateInfo_NULL, false);
        vb1[SqlPlayerCreateInfo_account] = true;
        vb1[SqlPlayerCreateInfo_playerId] = true;
        vb1[SqlPlayerCreateInfo_createTime] = true;
        DataDBConnection::makeInsertQuery(query1, playerCreateInfo, vb1);
        mysqlpp::SimpleResult res1 = query1.execute();
        if (res1)
        {
            trans.commit();

            m_playerInfo = createPlayerInfo;
            m_playerInfo.playerId = res.insert_id();
            m_playerInfo.authority = playerInfo.authority;
			m_playerInfo.roleSolt = playerInfo.roleSolt;

            return true;
        }
    }
    return false;
}

bool DataPlayer::SavePlayerInfoDB()
{
    mysqlpp::Query query = DataDBConnection::instance()->query();
    SqlPlayerInfo playerInfo;
    playerInfo.playerId = m_playerInfo.playerId;
    playerInfo.lastoffTime = m_playerInfo.lastOffTime;
    playerInfo.roleSolt = m_playerInfo.roleSolt;
    playerInfo.allbinary = std::string(m_data, m_dataLen);

    DataDBConnection::makeUpdateQuery(query, playerInfo.table(), playerInfo.equal_list(SqlPlayerInfo_lastoffTime, SqlPlayerInfo_roleSolt, SqlPlayerInfo_allbinary), playerInfo.equal_list(SqlPlayerInfo_playerId));

    LOGD("DataPlayer::SavePlayerInfoDB " << query.str().c_str());
    mysqlpp::SimpleResult res = query.execute();
    if (!res)
        return false;

    m_needSavePlayer = false;

    return true;
}

bool DataPlayer::SaveRoleInfoDB()
{
    for (uint32_t i = 0; i < m_roleInfos.size(); ++i)
    {
        if (m_roleInfos[i] && m_roleInfos[i]->needSave)
        {
            mysqlpp::Query query = DataDBConnection::instance()->query();
            SqlRoleInfo roleInfo;
            roleInfo.roleId = m_roleInfos[i]->roleId;
            roleInfo.level = m_roleInfos[i]->level;
            roleInfo.exp = m_roleInfos[i]->exp;
            roleInfo.fight = m_roleInfos[i]->fight;
            roleInfo.mapId = m_roleInfos[i]->mapId;
			roleInfo.x = m_roleInfos[i]->pos.x;
			roleInfo.y = m_roleInfos[i]->pos.y;
			roleInfo.z = m_roleInfos[i]->pos.z;
			roleInfo.dirx = m_roleInfos[i]->pos.dirx;
			roleInfo.diry = m_roleInfos[i]->pos.diry;
			roleInfo.dirz = m_roleInfos[i]->pos.dirz;
            roleInfo.functionOpenBitMap = m_roleInfos[i]->functionOpenBitMap;
            roleInfo.otherFunOpenBitMap = m_roleInfos[i]->otherFunOpenBitMap;
            roleInfo.allbinary = std::string(m_roleInfos[i]->data, m_roleInfos[i]->dataLen);

            DataDBConnection::makeUpdateQuery(query, roleInfo.table(), roleInfo.equal_list(SqlRoleInfo_level, SqlRoleInfo_exp, SqlRoleInfo_fight, SqlRoleInfo_mapId, 
				SqlRoleInfo_x, SqlRoleInfo_y, SqlRoleInfo_z, SqlRoleInfo_dirx, SqlRoleInfo_diry, SqlRoleInfo_dirz,
				SqlRoleInfo_functionOpenBitMap, SqlRoleInfo_otherFunOpenBitMap, SqlRoleInfo_allbinary), roleInfo.equal_list(SqlRoleInfo_roleId));

            LOGD("DataPlayer::SaveRoleInfoDB " << query.str().c_str());

            mysqlpp::SimpleResult res = query.execute();
            if (!res)
                return false;

            for (auto &itr : m_roleInfos[i]->items)
            {
                query.clear();
                if (ITEM_CHANGE_STATUS_DEL == itr.second->change)
                {
                    query << "delete * from PLAYER_ITEM where ITEMID  =  " << itr.second->itemId << " ;";
                    mysqlpp::SimpleResult res = query.execute();
                    if (!res)
                        return false;
                }
                else if (ITEM_CHANGE_STATUS_LOAD != itr.second->change)
                {
                    SqlPlayerItem itemInfo;
                    itemInfo.itemId = itr.second->itemId;
                    itemInfo.itemCount = itr.second->count;
                    itemInfo.bagType = itr.second->bagType;
                    itemInfo.roleId = itr.second->roleId;
                    itemInfo.allbinary = std::string(itr.second->data, itr.second->len);

                    DataDBConnection::makeUpdateQuery(query, itemInfo.table(), itemInfo.equal_list(SqlPlayerItem_itemCount, SqlPlayerItem_bagType, SqlPlayerItem_roleId, SqlPlayerItem_allbinary), itemInfo.equal_list(SqlPlayerItem_itemId));

                    LOGD("DataPlayer::PLAYER ROLE ITEM " << query.str().c_str());

                    mysqlpp::SimpleResult res = query.execute();
                    if (!res)
                        return false;
                }
            }

            for (auto &itr : m_roleInfos[i]->newItems)
            {
                query.clear();
                if (ITEM_CHANGE_STATUS_DEL == itr.second->change)
                {
                    if (itr.second->itemId)
                    {
                        query << "delete * from PLAYER_ITEM where ITEMID  =  " << itr.second->itemId << " ;";
                        mysqlpp::SimpleResult res = query.execute();
                        if (!res)
                            return false;
                    }
                }
                else if (ITEM_CHANGE_STATUS_NEW == itr.second->change)
                {
                    SqlPlayerItem itemInfo;
                    itemInfo.roleId = itr.second->roleId;
                    itemInfo.configId = itr.second->configId;
                    itemInfo.itemType = itr.second->type;
                    itemInfo.itemCount = itr.second->count;
                    itemInfo.bagType = itr.second->bagType;
                    itemInfo.allbinary = std::string(itr.second->data, itr.second->len);

                    std::vector<bool> vb1(SqlPlayerItem_NULL, false);
                    vb1[SqlPlayerItem_roleId] = true;
                    vb1[SqlPlayerItem_configId] = true;
                    vb1[SqlPlayerItem_itemType] = true;
                    vb1[SqlPlayerItem_itemCount] = true;
                    vb1[SqlPlayerItem_bagType] = true;
                    vb1[SqlPlayerItem_allbinary] = true;
                    DataDBConnection::makeInsertQuery(query, itemInfo, vb1);

                    LOGD("DataPlayer::PLAYER ROLE ITEM " << query.str().c_str());

                    mysqlpp::SimpleResult res = query.execute();
                    if (!res)
                        return false;

                    itr.second->itemId = res.insert_id();
                }
                else if (ITEM_CHANGE_STATUS_LOAD != itr.second->change)
                {
                    SqlPlayerItem itemInfo;
                    itemInfo.itemId = itr.second->itemId;
                    itemInfo.itemCount = itr.second->count;
                    itemInfo.bagType = itr.second->bagType;
                    itemInfo.roleId = itr.second->roleId;
                    itemInfo.allbinary = std::string(itr.second->data, itr.second->len);

                    DataDBConnection::makeUpdateQuery(query, itemInfo.table(), itemInfo.equal_list(SqlPlayerItem_itemCount, SqlPlayerItem_bagType, SqlPlayerItem_roleId, SqlPlayerItem_allbinary), itemInfo.equal_list(SqlPlayerItem_itemId));

                    LOGD("DataPlayer::PLAYER ROLE ITEM " << query.str().c_str());

                    mysqlpp::SimpleResult res = query.execute();
                    if (!res)
                        return false;
                }
            }
        
            m_roleInfos[i]->needSave = false;
        }
    }

    return true;
}

//DataPlayerManager
void DataPlayerManager::AddPlayer(DataPlayer *player)
{
    m_players[player->m_playerInfo.playerId] = player;
    m_playersByAccount[player->m_playerInfo.account] = player;
}

DataPlayer *DataPlayerManager::FindPlayerById(uint64_t id)
{
    auto itr = m_players.find(id);
    if (itr != m_players.end())
        return itr->second;

    return NULL;
}

DataPlayer *DataPlayerManager::FindPlayerByAccount(std::string account)
{
    auto itr = m_playersByAccount.find(account);
    if (itr != m_playersByAccount.end())
        return itr->second;

    return NULL;
}

void DataPlayerManager::SaveAllPlayer()
{
    LOGI("SaveAllPlayer Begin !!!");

    for (auto &v : m_players)
    {
        LOGD("SaveAllPlayer player account = " << v.second->m_playerInfo.account << " !!!");

        v.second->SaveDB();
    }

    LOGI("SaveAllPlayer End !!!");

    return;
}

void DataPlayerManager::Update5Sec()
{
    uint64_t curTime = CImpServerTimeTick::currentTime.sec();
    for (auto &v : m_players)
    {
        if (curTime - v.second->m_lastSaveTime >= PLAYER_SAVE_INTERVAL)
        {
            v.second->SaveDB();
            v.second->m_lastSaveTime = curTime;
        }
            
    }

    return;
}


