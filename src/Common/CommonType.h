///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Sys.h"
#include "EaglePos.h"
#include "EagleError.h"
#include "StringTool.h"

//buff fun
//buff load
#define BuffLoadByte(buff, length, out) \
    {\
        out = *(uint8_t*)buff;        \
        buff += UINT8_LEN;            \
        length -= UINT8_LEN;            \
    }\

#define BuffLoadInt16(buff, length, out) \
    {\
        out = *(uint16_t*)buff;        \
        buff += UINT16_LEN;            \
        length -= UINT16_LEN;            \
    }\

#define BuffLoadInt(buff, length, out) \
    {\
        out = *(uint32_t*)buff;        \
        buff += UINT32_LEN;            \
        length -= UINT32_LEN;            \
    }\

#define BuffLoadInt64(buff, length, out) \
    {\
        out = *(uint64_t*)buff;        \
        buff += UINT64_LEN;            \
        length -= UINT64_LEN;            \
    }\

#define BuffLoadLen(buff, length, out, len) \
    {\
        memcpy(out, buff, len);\
        buff += len;            \
        length -= len;            \
    }\

//buff load move
#define BuffLoadMoveLen(buff, length, len) \
    {\
        buff += len;            \
        length -= len;            \
    }\

//buff write
#define BuffWriteByte(buff, length, in) \
    {\
        *(uint8_t*)buff = in;        \
        buff += UINT8_LEN;            \
        length += UINT8_LEN;            \
    }\

#define BuffWriteInt16(buff, length, in) \
    {\
        *(uint16_t*)buff = in;        \
        buff += UINT16_LEN;            \
        length += UINT16_LEN;            \
    }\

#define BuffWriteInt(buff, length, in) \
    {\
        *(uint32_t*)buff = in;        \
        buff += UINT32_LEN;            \
        length += UINT32_LEN;            \
    }\

#define BuffWriteInt64(buff, length, in) \
    {\
        *(uint64_t*)buff = in;        \
        buff += UINT64_LEN;            \
        length += UINT64_LEN;            \
    }\

#define BuffWriteLen(buff, length, in, len) \
    {\
        memcpy(buff, in, len);\
        buff += len;            \
        length += len;            \
    }\

//buff write move
#define BuffWriteMoveLen(buff, length, len) \
    {\
        buff += len;            \
        length += len;            \
    }\

#define MAX_ACCOUNT_LENGHT 128        //
#define MAX_PASSWD_LENGHT 256        //
#define MAX_SDK_OPENKEY_LENGHT 512        //
#define MAX_PLAYER_NAME    32            //
#define MAX_GUILD_NAME    36            //
#define MAX_SESSION_LENGHT 256        //
#define MAX_ROLE_NUM 4        //
#define MAX_BUY_ROLE_NUM 20        //
#define PROTOCOL_ID_MASK 1000    //

struct TargetPos
{
    int64_t x;
    int64_t y;
    int64_t z;
    int64_t dirx;
    int64_t diry;
    int64_t dirz;
    uint64_t uid;

    TargetPos()
    {
        bzero(this, sizeof(*this));
    }

    void Clear()
    {
        bzero(this, sizeof(*this));
    }
};

// type  OBJECT_TYPE
struct TypeIdCount
{
    uint32_t type;
    uint64_t id;
    uint64_t count;

    TypeIdCount()
    {
        memset(this, 0, sizeof(TypeIdCount));
    }

    TypeIdCount(uint32_t _type, uint64_t _id, uint64_t _count)
        :type(_type), id(_id), count(_count)
    {
    }

    TypeIdCount(const TypeIdCount& rhs) = default;
};

struct TypeValuesInfo
{
    uint32_t type;
    std::vector<double> values;

    TypeValuesInfo()
        :type(0)
    {
    }
};

//
struct ConditionParm
{
    uint32_t type;
    std::string value;
};

//
enum HIT_TARGET_TYPE
{
    HIT_TARGET_TYPE_OWNER = 0,
    HIT_TARGET_TYPE_SELECT = 1,
    HIT_TARGET_TYPE_AREA_TEAM = 2,
    HIT_TARGET_TYPE_AREA_ENEMY = 3

};

struct HitRangeInfo
{
    uint32_t targetType;    //
    uint32_t rangeType;        //
    double para1;        //
    double para2;        //
    double para3;        //
    double para4;        //
    double para5;        //

    HitRangeInfo()
    {
        bzero(this, sizeof(*this));
    }
};

//

enum OBJECTTYPE
{
    OBJECT_NONE = 0,
    OBJECT_PLAYER = 1,
    OBJECT_CHARACTER,
    OBJECT_NPC,
    OBJECT_MONSTER,
    OBJECT_FIGHTER,
    OBJECT_DYNMIC,
    OBJECT_PARTNER,
    OBJECT_BUFF = 18,    //BUFF
    OBJECT_SKILL = 19,    //

    OBJECT_ITEM = 0,
    OBJECT_TYPE_NORMAL = 1,    //
    OBJECT_TYPE_EQUIP = 2,        //
    OBJECT_TYPE_COIN = 3,        //COIN
    OBJECT_TYPE_ITEM_MAX,

    OBJECT_BAG = 0,        //
    OBJECT_ACCOUNT_BAG = 0,
    OBJECT_NORMAL_BAG = 1,                                //
    OBJECT_EQUIP_BAG = 2,                                //
    OBJECT_COIN_BAG = 3,                                //
    OBJECT_EQUIPBYCHARACTER_BAG = 4,                                //
    OBJECT_BAG_MAX ,


    OBJECT_MMO_SKILL = 60,    //
    OBJECT_MMO_EFFECT_OBJECT = 61,

	OBJECT_WORLD = 97,
    OBJECT_LANDMASS = 98,        //
	OBJECT_DUNGEON = 99,
    OBJECT_MAP = 100,

	OBJECT_MAP_BIG = 1,
	OBJECT_MAP_LOAD,
	OBJECT_MAP_IMAGE,
	OBJECT_MAP_DUNGEON,

    OBJECT_DUNGEON_MAIN = 1,
    OBJECT_DUNGEON_SOLO,                    //    
    OBJECT_DUNGEON_TEAM,                //TEAM
    OBJECT_DUNGEON_LOGIN,    //
	OBJECT_DUNGEON_GROUP,	//团队
	OBJECT_DUNGEON_1V1,
    OBJECT_DUNGEON_3V3,
};

#define ITEMSTACKMAXCOUNT        2000000000

//
enum COIN_TYPE
{
    COIN_TYPE_DIAMOND = 1000,
    COIN_TYPE_ENERGY = 1001,    //
    COIN_TYPE_MONEY = 1002,        //
    COIN_TYPE_EXP = 1003,        //
};

enum NOTMAL_ITEM_TYPE
{
    NOTMAL_ITEM_TYPE_MATERIAL = 1,
    NOTMAL_ITEM_TYPE_CONSUM = 2,
    NOTMAL_ITEM_TYPE_QUEST = 3,

};
//
enum EQUIP_TYPE
{
    EQUIP_TYPE_NONE = 0,
    EQUIP_TYPE_WEAPON = 1, //武器
    EQUIP_TYPE_ARMOR = 2,    //防具
    EQUIP_TYPE_JABE = 3,    //玉佩

    EQUIP_TYPE_MAX = 20,    //
};

#define ROLEVERSION_1_1		1
#define SCENE_NOTIFY_PLAYER_MAXNUM 200    //
#define EYE_RANG_SIZE    5000        //
#define SERVER_CHARACTOR_UID_AV    100000000    //

#define MAX_CHANNEL_NAME_LENGHT 128        //
#define MAX_CHAT_MESSAGE_LENGHT 1024    //

#define MAIL_TITLE_LENGTH 128    //
#define MAIL_CONTENT_LENGTH 512    //
#define MAIL_MAX_COUNT    200        //
#define MAIL_ONCE_PAGE_NUM 50    //

#define MAIL_MAX_LEFT_TIME 2592000        //
#define UNLOGIN_DEL_PLAYER_TIME 30        //

#define ASYNC_LOCK_REF_TIME 30    //

#define ROLE_LEVEL_DEFUAL 1                //
#define ROLE_GOLD_DEFUAL 88888            //
#define PLAYER_VIPLEVEL_DEFUAL 0                //

#define PARTNER_MAX_NUM 3        //最大上阵伙伴数量

//SDK TYPE
enum SDK_TYPE
{
    SDK_TYPE_NONE = 0,
    SDK_TYPE_EAGLE = 1,    //


    SDK_TYPE_MAX
};

//Scene Charactor Info
struct SceneCharactorPos : public CmdPos
{
    uint64_t charactorUid;
    uint64_t sceneId;
    uint64_t time;

    SceneCharactorPos()
        :charactorUid(0), sceneId(0), time(0)
    {
    }
};

//
enum E_ATTRIBUTE_TYPE
{
    EAT_ATTACK = 0,
    EAT_DEFENSE = 1,
    EAT_MAXHP = 2,
    EAT_HP = 3,
    
    EAT_MAX,


    EAT_RESISTANT = 100,
    EAT_RESISTANT_MAX = 132,
};

struct AttrInfoType
{
    uint32_t type;
    int64_t value;
};

//
enum OPEN_FUNCTION_MASK
{
    OPEN_FUNCTION_MASK_MAGIC_BLACK_SHOP = 1,
    OPEN_FUNCTION_MASK_RUN_BUSINESS = 2,
    OPEN_FUNCTION_MASK_BOSSRUSH = 3,
};

//
enum CHARACTER_STATUS_TIMES_ARRAY
{
    CHARACTER_STATUS_TIMES_COMA = 0,            //
    CHARACTER_STATUS_TIMES_FLY = 1,            //
    CHARACTER_STATUS_TIMES_CLICKFLY = 2,            //
    CHARACTER_STATUS_TIMES_DURANCE = 3,        //
    CHARACTER_STATUS_TIMES_ICE = 4,            //
    CHARACTER_STATUS_TIMES_SLOW = 5,                //
    CHARACTER_STATUS_TIMES_NONE1 = 6,                //
    CHARACTER_STATUS_TIMES_GRAVITATION = 7,            //
    CHARACTER_STATUS_TIMES_HITBACK = 8,            //

    CHARACTER_STATUS_TIMES_DEBUFF_MAX = 40,    

    CHARACTER_STATUS_TIMES_DIE = 61,                    //
    CHARACTER_STATUS_TIMES_OVERLORD = 62,        //
    CHARACTER_STATUS_TIMES_INVINCIBLE = 63,        //

    CHARACTER_STATUS_TIMES_MAX = 64
};

#define CHARACTER_STATUS_COMA                (1 << CHARACTER_STATUS_TIMES_COMA)        //
#define CHARACTER_STATUS_FLY                0x00000002        //
#define CHARACTER_STATUS_CLICKFLY            0x00000004        //
#define CHARACTER_STATUS_DURANCE            0x00000008        //
#define CHARACTER_STATUS_ICE                0x00000010        //
#define CHARACTER_STATUS_SLOW                0x00000020        //
#define CHARACTER_STATUS_NONE1                0x00000040        //
#define CHARACTER_STATUS_GRAVITATION        0x00000080        //

#define CHARACTER_STATUS_DIE                0x2000000000000000        //
#define CHARACTER_STATUS_OVERLORD            0x4000000000000000        //
#define CHARACTER_STATUS_INVINCIBLE            0x8000000000000000        //

#define CLEAR_CHARACTER_STATUS(status, type)    (status &= ~type)
#define IS_CHARACTER_STATUS(status, type) (status & type)
#define STATUSID_TO_STATUSBIT(id)    (((uint64_t)1)<<id)
#define SET_CHARACTER_STATUS(status, type)    (status |= type)
#define KONGZHI_MIANYI_STATUS (CHARACTER_STATUS_OVERLORD | CHARACTER_STATUS_INVINCIBLE)

struct MatchBaseInfo
{
    uint32_t matchType;
    uint64_t matchUid;

    MatchBaseInfo()
    {
        bzero(this, sizeof(MatchBaseInfo));
    }
};

//
struct WDungeonBaseInfo
{
    char ip[MAX_IP_LENGTH];
    uint32_t tcpPort;
    uint32_t udpPort;
    uint32_t wServerId;
	uint64_t dungeonId;
    uint64_t dungeonUid;
    uint64_t createTime;

    WDungeonBaseInfo()
    {
        bzero(this, sizeof(WDungeonBaseInfo));
    }

    void Clear()
    {
        bzero(this, sizeof(WDungeonBaseInfo));
    }
};

//
enum SKILL_TYPE
{
    SKILL_TYPE_NONE = 0,        //
    SKILL_TYPE_NORMAL = 1,    //
    SKILL_TYPE_ATK = 2,    //
};

enum SKILL_CAST_TYPE
{
    SKILL_CAST_TYPE_NONE = 0,        //
    SKILL_CAST_TYPE_NORMAL = 1,    //
    SKILL_CAST_TYPE_LOG = 6    //
};

struct EffLocInfo
{
    double minx;
    double maxx;
    double miny;
    double maxy;
    double minz;
    double maxz;

    EffLocInfo()
    {
        bzero(this, sizeof(*this));
    }
};

struct EffectInfo
{
    uint32_t id;
    TypeValuesInfo effectAction;
    std::vector<uint32_t> nextTriggerEffectIds;
    uint32_t conditionAnd;    //0  or 1 and
    std::vector<ConditionParm> conditions;

    EffectInfo()
    {
        id = 0;
        conditionAnd = 0;
    }
};

struct TriggerInfo
{
    std::vector<HitRangeInfo> effectRangeData;
    std::vector<EffectInfo> effectData;
};

struct EffectObjectInfo
{
    uint32_t actorLifeType;    //object 
    HitRangeInfo collisionRangeData;    //
    uint64_t actorLifeTime;    //object 
    uint32_t actorSpeedType;    //0 
    double actorSpeed;        
    
    TriggerInfo endEffectData;

    uint32_t triggerType;    // 1
    uint64_t effectTime;    //
    TriggerInfo triggerInfos;    //if EffectActionInfo.type == 1  only read this
};

struct EffectActionInfo //CloseCombActionInfo LongDisActionInfo
{
    uint32_t id;    //if SkillActionInfo.type == 2 id 0  CloseCombActionInfo or LongDisActionInfo id
    uint32_t type;  //1

    uint32_t actorNum;        // object
    uint32_t actorAngleType;    //
    EffLocInfo actorAngle;        //
    uint32_t actorLocType;        // 
    EffLocInfo actorLocOff;        //
    uint32_t actionJudgeType;                //
    uint64_t continueTime;                    //

    EffectObjectInfo objectInfo; //if type == 1   only read this
};

struct SkillConfigData;
struct SkillData    // ActionInfo NormalATKInfo
{
    uint32_t id;
    uint32_t type; //1  2 
    bool canMove;
    uint64_t loadTime;    //0  
    uint64_t actionProtectTime;        //
    std::vector<uint64_t> effectTimes;
    std::vector< EffectActionInfo > effectActions;    //

    SkillConfigData *data;

};

//
enum OFF_PLAYER_FUN_TYPE
{
    OFF_PLAYER_FUN_TYPE_NONE = 0,    //
    OFF_PLAYER_FUN_TYPE_JJC = 1,        //jjc
};

//
enum CLIENT_SHOW_ACTION
{
    CLIENT_SHOW_ACTION_IDLE = 0, //
    CLIENT_SHOW_ACTION_HUG = 1,        //

    CLIENT_SHOW_ACTION_MAX
};

enum CharactorActionType
{
    CharactorActionType_None = 0,
    CharactorActionType_Idle = 1,
    CharactorActionType_Run = 2,
    CharactorActionType_Play = 3,
    CharactorActionType_Atk = 4,
    CharactorActionType_Skill = 5,

    CharactorActionType_BeAtk = 6,

    CharactorActionType_Die = 10,

    CharactorActionType_Max
};

#define DEFAULT_PLAY_ANIM_TIME 3000
#define RESET_ATK_SEG_INTERVAL_TIME 3000
#define ATK_SEG_LIST_NUM 1

struct BeAtkInfo
{
    uint64_t beginTime;
    uint64_t endTime;

    BeAtkInfo()
    {
        memset(this, 0, sizeof(*this));
    }

    void Clear()
    {
        memset(this, 0, sizeof(*this));
    }
};




