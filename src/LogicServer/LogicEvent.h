#ifndef _LOGIC_EVENT_H_ 
#define    _LOGIC_EVENT_H_

#include "CommonType.h"
#include "SharedEvent.h"

class OnKillLogicEvent : public EagleEvent
{
    uint64_t m_monsterId;
public:
    OnKillLogicEvent(uint64_t id, void *ptr = NULL);

    uint32_t Id() { return EVENT_TYPE_ONKILL; }

public:
    inline uint64_t MonsterId() { return m_monsterId; }
};

class OnLevelUpLogicEvent : public EagleEvent
{
public:
    OnLevelUpLogicEvent(void *ptr = NULL);

    uint32_t Id() { return EVENT_TYPE_LEVEL_UP; }
    void DoEvent(void *ptr);

};

class OnGetItemLogicEvent : public EagleEvent
{
public:
    OnGetItemLogicEvent(TypeIdCount *, void *ptr = NULL);

    uint32_t Id() { return EVENT_TYPE_GET_ITEM; }

};

class OnCmpQuestEvent : public EagleEvent
{
    uint64_t m_questId;
public:
    OnCmpQuestEvent(uint64_t id, void *ptr = NULL);

    uint32_t Id() { return EVENT_TYPE_CMP_QUEST; }
    void DoEvent(void *ptr);

public:
    inline uint64_t QuestId() { return m_questId; }
};

class OnClientLogicEvent : public EagleEvent
{
    uint64_t m_questId;
public:
    OnClientLogicEvent(uint64_t id, void *ptr = NULL);

    uint32_t Id() { return EVENT_TYPE_CLIENT_CMP_QUEST; }
public:
    inline uint64_t QuestId() { return m_questId; }
};

class OnPassDungeonLogicEvent : public EagleEvent
{
    uint64_t m_dungeonId;
    bool m_isTeam;
public:
    OnPassDungeonLogicEvent(uint64_t id, bool isTeam, void *ptr = NULL);

    uint32_t Id() { return EVENT_TYPE_PASS_DUNGEON; }
public:
    inline uint64_t DungeonId() { return m_dungeonId; }
    inline bool IsTeam() { return m_isTeam; }
};


#endif    


