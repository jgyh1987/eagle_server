#include "LogicEvent.h"
#include "LogicDataManager.h"

//OnKillLogicEvent
OnKillLogicEvent::OnKillLogicEvent(uint64_t id, void *ptr)
    :EagleEvent(ptr), m_monsterId(id)
{

}

//OnLevelUpLogicEvent
OnLevelUpLogicEvent::OnLevelUpLogicEvent(void *ptr)
    :EagleEvent(ptr)
{

}

void OnLevelUpLogicEvent::DoEvent(void *ptr)
{

}

//OnGetItemLogicEvent
OnGetItemLogicEvent::OnGetItemLogicEvent(TypeIdCount *, void *ptr)
    :EagleEvent(ptr)
{

}

//OnCmpQuestEvent
OnCmpQuestEvent::OnCmpQuestEvent(uint64_t id, void *ptr)
    :EagleEvent(ptr), m_questId(id)
{
}

void OnCmpQuestEvent::DoEvent(void *ptr)
{
    //WorldRole *role = (WorldRole *)m_exParam;
    //role->GetQuestManager()->UpdateLvAcceptQuest();

    return;
}

//OnClientLogicEvent
OnClientLogicEvent::OnClientLogicEvent(uint64_t id, void *ptr)
    :EagleEvent(ptr)
{

    m_questId = id;
}

//OnPassDungeonLogicEvent
OnPassDungeonLogicEvent::OnPassDungeonLogicEvent(uint64_t id, bool isTeam, void *ptr)
    :EagleEvent(ptr), m_dungeonId(id), m_isTeam(isTeam)
{
}


