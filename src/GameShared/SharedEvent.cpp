#include "SharedEvent.h"
#include "LogicDataManager.h"
#include "Effect.h"

std::vector<uint32_t> g_condition_to_event;
void InitConditionToEventArray()
{
    g_condition_to_event.resize(CONDITION_TYPE_MAX);
    g_condition_to_event[CONDITION_TYPE_NONE] = EVENT_TYPE_NONE;
    g_condition_to_event[CONDITION_TYPE_KILL_MONSTER] = EVENT_TYPE_ONKILL;
    //g_condition_to_event[CONDITION_TYPE_NPC_DIALOGUE] = EVENT_TYPE_CLIENT_CMP_QUEST;
    g_condition_to_event[CONDITION_TYPE_COMMIT_ITEM] = EVENT_TYPE_CLIENT_CMP_QUEST;
    g_condition_to_event[CONDITION_TYPE_LEVEL] = EVENT_TYPE_LEVEL_UP;
    g_condition_to_event[CONDITION_TYPE_DUNGEON] = EVENT_TYPE_PASS_DUNGEON;
    //g_condition_to_event[CONDITION_TYPE_DUNGEON_TEAM] = EVENT_TYPE_PASS_DUNGEON;
    //g_condition_to_event[CONDITION_TYPE_COMMIT_Q_EQUIP] = EVENT_TYPE_CLINET;
	g_condition_to_event[CONDITION_TYPE_CLIENT_CMP_QUEST] = EVENT_TYPE_CLIENT_CMP_QUEST;
}

//action
TiggerEffect::~TiggerEffect()
{

}

bool TiggerEffect::DoAction(EagleEvent *_event)
{

    return true;
}

//OnTimeEvent
OnTimeEvent::OnTimeEvent(uint64_t time, void *ptr)
    :EagleEvent(ptr), m_curTime(time)
{
}

//OnBeAtkEvent
OnBeAtkEvent::OnBeAtkEvent(const SkillConfigData *data, Character *caster, uint32_t hitType, uint64_t skillId, uint32_t weaponType)
    :EagleEvent(caster), m_data(data), m_caster(caster), m_hitType(hitType), m_skillId(skillId), m_weaponType(weaponType)
{
}

//OnAtkEvent
OnAtkEvent::OnAtkEvent(const SkillConfigData *data, Character *caster, Character *targer, uint32_t weaponType, uint32_t weaponSubId, uint32_t hitType)
    :EagleEvent(targer), m_data(data), m_caster(caster), m_targer(targer), m_weaponType(weaponType), m_weaponSubId(weaponSubId), m_hitType(hitType)
{
}

