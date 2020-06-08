#ifndef _PLAYERINFO_H_
#define _PLAYERINFO_H_

#include "CommonType.h"

struct PlayerInfoBase
{
    char account[MAX_ACCOUNT_LENGHT];
    uint64_t playerId;
    uint64_t playerUid;
    uint32_t vipLevel;
    uint32_t authority;
    uint32_t isRoBot;
    uint64_t lastOffTime;
    uint32_t roleSolt;
    uint32_t sex;
	uint32_t dbServerId;
	uint32_t gatewayServerId;

    PlayerInfoBase()
    {
        bzero(this, sizeof(*this));
    }

	void Clear()
	{
		bzero(this, sizeof(*this));
	}
};

struct RoleInfoBase
{
    uint64_t playerId;
    uint64_t roleId;
    uint32_t jobId;
    char name[MAX_PLAYER_NAME];
    uint32_t level;
    uint64_t mapId;
	CmdPos pos;
    uint32_t fight;
    uint64_t lastOffTime;
	uint64_t exp;
	uint32_t functionOpenBitMap;
	uint32_t otherFunOpenBitMap;

    RoleInfoBase()
    {
        bzero(this, sizeof(*this));
    }

    void Clear()
    {
        bzero(this, sizeof(*this));
    }
};

//

struct CharacterBaseFightInfo
{
    int64_t baseAttr1[EAT_MAX];
    int64_t baseResistant1[CHARACTER_STATUS_TIMES_MAX];
    uint32_t peace;
    uint64_t status;
    int16_t statusTimes[CHARACTER_STATUS_TIMES_MAX];

    CharacterBaseFightInfo()
    {
		bzero(this, sizeof(*this));
    }

    CharacterBaseFightInfo(CharacterBaseFightInfo &rhs)
    {
        if (this == &rhs)
            return;

        memcpy(baseAttr1, rhs.baseAttr1, sizeof(baseAttr1));
        memcpy(baseResistant1, rhs.baseResistant1, sizeof(baseResistant1));
        memcpy(statusTimes, rhs.statusTimes, sizeof(statusTimes));
        peace = rhs.peace;
        status = rhs.status;
    }

    CharacterBaseFightInfo& operator = (CharacterBaseFightInfo &rhs)
    {
        if (this == &rhs)
            return *this;

        memcpy(baseAttr1, rhs.baseAttr1, sizeof(baseAttr1));
        memcpy(baseResistant1, rhs.baseResistant1, sizeof(baseResistant1));
        memcpy(statusTimes, rhs.statusTimes, sizeof(statusTimes));
        peace = rhs.peace;
        status = rhs.status;
    
        return *this;
    }

    void ResetAttr()
    {
        bzero(this, sizeof(CharacterBaseFightInfo));
    }
};

struct CharacterFightInfo : public CharacterBaseFightInfo
{
    int64_t curAttr[EAT_MAX];
    int64_t curResistant[CHARACTER_STATUS_TIMES_MAX];

    CharacterFightInfo()
    {
        memset(curAttr, 0, sizeof(curAttr));
        memset(curResistant, 0, sizeof(curResistant));
    }

    CharacterFightInfo(CharacterFightInfo &rhs)
        :CharacterBaseFightInfo(rhs)
    {
        if (this == &rhs)
            return;
    
        memcpy(curAttr, rhs.curAttr, sizeof(curAttr));
        memcpy(curResistant, rhs.curResistant, sizeof(curResistant));
    }

    CharacterFightInfo &operator = (CharacterFightInfo &rhs)
    {
        if (this == &rhs)
            return *this;

        *(CharacterBaseFightInfo *)this = *(CharacterBaseFightInfo*)&rhs;

        memcpy(curAttr, rhs.curAttr, sizeof(curAttr));
        memcpy(curResistant, rhs.curResistant, sizeof(curResistant));

        return *this;
    }

    CharacterFightInfo &operator = (CharacterBaseFightInfo &rhs)
    {
        if (this == &rhs)
            return *this;

        *(CharacterBaseFightInfo *)this = *(CharacterBaseFightInfo*)&rhs;

        memcpy(curAttr, rhs.baseAttr1, sizeof(curAttr));
        memcpy(curResistant, rhs.baseResistant1, sizeof(curResistant));

        return *this;
    }

    void ReSetCurAttr()
    {
        memcpy(curAttr, baseAttr1, sizeof(curAttr));
        memcpy(curResistant, baseResistant1, sizeof(curResistant));
    }
};

struct WorldPlayerBaseInfo
{
    uint32_t gameServerId;
    uint32_t logicServerId;
    uint64_t playerId;

    WorldPlayerBaseInfo()
    {
        gameServerId = 0;
        logicServerId = 0;
        playerId = 0;
    }
};

struct WorldPlayerInfo : public WorldPlayerBaseInfo
{
    PlayerInfoBase playerInfo;
	RoleInfoBase roleInfo;

    WorldPlayerInfo()
    {
        
    }

    void Clear()
    {
        roleInfo.Clear();
    }
};

#define WORLDPLAYER_INFOEX_VERSION_1_1     1

struct WorldPlayerInfoEx : public WorldPlayerInfo
{
    CharacterFightInfo fighterInfo;
    std::vector<uint64_t> skillIds;

    uint32_t UnSerializeInfo(uint8_t *buffer, uint32_t len)
    {
        if (!len)
            return len;

        uint32_t length = 0;

        BuffLoadInt(buffer, length, length);
        uint32_t ret = length + UINT32_LEN;

        BuffLoadMoveLen(buffer, length, UINT32_LEN);    //version

        uint32_t num = 0;
        BuffLoadInt(buffer, length, num);
        skillIds.resize(num);
        for (uint32_t i = 0; i < num; ++i)
            BuffLoadInt64(buffer, length, skillIds[i]);

        return ret;
    }
    
    uint32_t SerializeInfo(uint8_t *buffer)
    {
        uint32_t size = 0;
        uint32_t *pLen = (uint32_t *)buffer;
        BuffWriteMoveLen(buffer, size, UINT32_LEN);

        BuffWriteInt(buffer, size, WORLDPLAYER_INFOEX_VERSION_1_1);

        BuffWriteInt(buffer, size, (uint32_t)skillIds.size());
        for (uint32_t i = 0; i < skillIds.size(); ++i)
            BuffWriteInt64(buffer, size, skillIds[i]);

        *pLen = size;

        return size;
    }

};



#endif

