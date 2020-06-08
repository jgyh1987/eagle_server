#ifndef _LOGICDATA_PLAYER_H_
#define _LOGICDATA_PLAYER_H_

#include "Sys.h"
#include "Singleton.h"
#include "LogicDataCommand.h"
#include "PlayerInfo.h"

class CLogicDataTask;

struct DBRoleAllInfo : public RoleInfoBase
{
    uint32_t status;
    uint64_t createTime;
    bool needSave;
    uint32_t dataLen;
    char *data;
    std::map<uint64_t, ItemChangeData *> items;
    std::map<uint64_t, ItemChangeData *> newItems;

    DBRoleAllInfo()
    {
        status = 0;
        createTime = 0;
        needSave = false;
        dataLen = 0;
        data = NULL;
    }

    ~DBRoleAllInfo()
    {
        if (data)
            delete[]data;

        for (auto &v : items)
        {
            delete v.second;
        }
        items.clear();

        for (auto &v : newItems)
        {
            delete v.second;
        }
        newItems.clear();
    }

    ItemChangeData *FindItem(ItemChangeData *data)
    {
        auto itr = items.find(data->itemId);
        if (itr != items.end())
            return itr->second;

        itr = newItems.find(data->uid);
        if (itr != newItems.end())
            return itr->second;

        return NULL;
    }

};

class DataPlayer
{
public:
    DataPlayer();
    ~DataPlayer();

	void UpdateSelectServer(uint32_t serverType, uint32_t serverId);
    bool IsSelectServer(uint32_t serverType, uint32_t serverId);
    void Update();

    bool LoadDB(PlayerInfoBase &playerInfo);
    bool SaveDB(bool removeNewItem = false);

    void SendPlayerInfoToLogic(CLogicDataTask *task, uint32_t funType, uint64_t srcPlayer);
    void SerializeRoleSimpleInfo(uint8_t *ptr, uint32_t &len);
    void GetRoleInfo(uint64_t roleId, CLogicDataTask *task, uint32_t funType, uint64_t srcPlayer);
    DBRoleAllInfo *FindRoleById(uint64_t roleId);
    void UpdatePlayerInfo(PlayerInfoBase *info, uint8_t *data, uint32_t dataLen);
    DBRoleAllInfo *CreateRoleInfo(Cmd::t_Data_Create_RoleInfo_Req *recv);
    void UpdateRoleStatus(uint64_t roleId, uint32_t status);
    bool UpdateRoleInfo(Cmd::t_Data_Save_RoleInfo_Req *recv);

    //item
    bool CheckItems(DBRoleAllInfo *, uint8_t *ptr, uint32_t count, uint32_t len);
    bool CheckItem(DBRoleAllInfo *, ItemChangeData *);
    bool ChangeItems(DBRoleAllInfo *, uint8_t *ptr, uint32_t count, uint32_t len);
    bool ChangeItem(DBRoleAllInfo *, ItemChangeData *);
    bool HaveItem(DBRoleAllInfo *, ItemChangeData *);

protected:
    bool CreatePlayer(PlayerInfoBase &createPlayerInfo);

    bool SavePlayerInfoDB();
    bool SaveRoleInfoDB();

    ItemChangeData *FindItem(ItemChangeData *data, DBRoleAllInfo *role)
    {

        if (role)
            return role->FindItem(data);

        return NULL;
    }


public:
    PlayerInfoBase m_playerInfo;
    std::vector<DBRoleAllInfo *> m_roleInfos;
    uint32_t m_dataLen;
    char *m_data;
    uint32_t m_serverType;
    uint32_t m_serverId;
    uint64_t m_lastSaveTime;
    bool m_needSavePlayer;
};

class DataPlayerManager : public CSingleton<DataPlayerManager>
{
public:

    void AddPlayer(DataPlayer *player);
    DataPlayer *FindPlayerById(uint64_t id);
    DataPlayer *FindPlayerByAccount(std::string account);
    void SaveAllPlayer();

    void Update5Sec();

private:

    std::map<uint64_t, DataPlayer *> m_players;
    eagle_hash_map<std::string, DataPlayer *> m_playersByAccount;
};


#endif

