#ifndef _SHARED_EVENT_H_ 
#define    _SHARED_EVENT_H_

#include "CommonType.h"
#include "Action.h"
#include "Event.h"
#include "Condition.h"
#include "LogicDataManager.h"

class EagleCondition;
class EagleAction;
class Character;
class Effect;

EagleAction* CreateAction(uint32_t type, void *ptr, void *param);
EagleAction* CreateAction(uint32_t type, void *ptr, const std::vector<double> &param);
EagleCondition* CreateCondition(EagleAction *action, uint32_t type, const char *param);
EagleCondition* CreateCondition(EagleAction *action, uint32_t type, const std::vector<double> &param);

extern std::vector<uint32_t> g_condition_to_event;
void InitConditionToEventArray();

enum EVENT_TYPE
{
    EVENT_TYPE_TIME = 1,
    EVENT_TYPE_CAST_SKILL = 2,
    EVENT_TYPE_ATK = 3,
    EVENT_TYPE_BE_ATK = 4,
	EVENT_TYPE_MOVE = 5,

    EVENT_TYPE_ONKILL = 21,
    EVENT_TYPE_GET_ITEM = 22,
    EVENT_TYPE_CLIENT_CMP_QUEST = 23,
    EVENT_TYPE_PASS_DUNGEON = 24,
    EVENT_TYPE_LEVEL_UP = 25,
    EVENT_TYPE_CMP_QUEST = 26,

    EVENT_TYPE_MAX
};

enum ACTION_TYPE
{
    ACTION_TRIGGER_EFFECT = 1, 

    ACTION_TYPE_DUNGEON_COMPLETE = 2,
    ACTION_TYPE_QUEST_COMPLETE = 3,
    ACTION_TYPE_OPEN_GATE = 4,//开启关卡

	ACTION_TYPE_OPEN_WIDGET = 9,
	ACTION_HIDE_MAP_NPC = 10,
	ACTION_TRIGGER_PLAYER_POSTEFFECT = 11,
	ACTION_TRIGGER_CREATE_MONSTER = 12,
	ACTION_TRIGGER_CREATE_PARTNER = 13,

    ACTION_TYPE_MAX
};

enum CONDITION_TYPE
{
	CONDITION_TYPE_DUNGEON = 1,    //副本
	//CONDITION_TYPE_DUNGEON_TEAM = 2,    //组队副本
	CONDITION_TYPE_KILL_MONSTER = 3,    //杀怪
	CONDITION_TYPE_NPC_DIALOGUE = 4,    //对话
	CONDITION_TYPE_LEVEL = 5,        //升级
	CONDITION_TYPE_COMMIT_ITEM = 6,        //上交物品
	CONDITION_TYPE_QUEST_COMPLETE = 7,    //完成任务
	//CONDITION_TYPE_COMMIT_Q_EQUIP = 8,        //上交品质装备
	CONDITION_TYPE_CLIENT_CMP_QUEST = 9,			        //client
	CONDITION_TYPE_MOVETO = 10,				//移动到某个范围


    CONDITION_TYPE_MAX
};

//action
class TiggerEffect : public EagleAction
{
    Effect *m_effect;
public:
    TiggerEffect(void * ptr1, void *ptr2)
        :EagleAction(ptr1), m_effect((Effect *)ptr2)
    {
    }
    ~TiggerEffect();

    uint32_t Id() { return ACTION_TRIGGER_EFFECT; }

    bool DoAction(EagleEvent *_event);
};

//event
class OnTimeEvent : public EagleEvent
{
    uint64_t m_curTime;
public:
    OnTimeEvent(uint64_t time, void *ptr = NULL);

    uint32_t Id(){return EVENT_TYPE_TIME;}

public:
    inline uint64_t CurTime(){return m_curTime;}
};

class OnBeAtkEvent : public EagleEvent
{
    const SkillConfigData *m_data;
    Character *m_caster;
    uint32_t m_hitType; //enum Hit_Type
    uint64_t m_skillId;
    uint32_t m_weaponType;
public:
    OnBeAtkEvent(const SkillConfigData *data, Character *caster, uint32_t hitType, uint64_t skillId, uint32_t weaponType);

    uint32_t Id(){return EVENT_TYPE_BE_ATK;}

public:
    inline const SkillConfigData *GetSkillConfigData(){return m_data;}
    inline const Character *GetCaster(){return m_caster;}
    inline uint32_t HitType(){return m_hitType;}
    inline uint64_t SkillId(){return m_skillId;}
    inline uint32_t WeaponType(){return m_weaponType;}
};

class OnAtkEvent : public EagleEvent
{
    const SkillConfigData *m_data;
    Character *m_caster;
    Character *m_targer;
    uint32_t m_weaponType;
    uint32_t m_weaponSubId;
    uint32_t m_hitType; //enum Hit_Type

public:
    OnAtkEvent(const SkillConfigData *data, Character *caster, Character *targer, uint32_t weaponType, uint32_t weaponSubId, uint32_t hitType);

    uint32_t Id(){return EVENT_TYPE_BE_ATK;}

public:
    inline const SkillConfigData *GetSkillConfigData(){return m_data;}
    inline const Character *GetCaster(){return m_caster;}
    inline const Character *GetTarger(){return m_targer;}
    inline uint32_t HitType(){return m_hitType;}
    inline uint32_t WeaponType(){return m_weaponType;}
    inline uint32_t WeaponSubId(){return m_weaponSubId;}
};


#endif