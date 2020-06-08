#ifndef _LOGIC_ACTION_H_ 
#define    _LOGIC_ACTION_H_

#include "SharedEvent.h"
#include "CommonType.h"

class LogicPlayer;
class Quest;

class CompleteDungeonAction : public EagleAction
{
    uint32_t m_questMapId;
public:
    CompleteDungeonAction(void * ptr1, void* ptr2)
        :EagleAction(ptr1), m_questMapId(*(uint32_t *)ptr2)
    {
    }

    uint32_t Id() { return ACTION_TYPE_DUNGEON_COMPLETE; }

    bool DoAction(EagleEvent *_event);
};

class CompleteQuestAction : public EagleAction
{
    Quest *m_quest;
public:
    CompleteQuestAction(void * ptr1, void *ptr2)
        :EagleAction(ptr1), m_quest((Quest*)ptr2)
    {
    }

    void UpdateCondition(EagleEvent *_event);
    uint32_t Id() { return ACTION_TYPE_QUEST_COMPLETE; }

    bool DoAction(EagleEvent *_event);
};

class OpenGateAction : public EagleAction
{
    uint32_t m_openId;
public:
    OpenGateAction(void * ptr1, void *ptr2)
        :EagleAction(ptr1), m_openId(*(uint32_t*)ptr2)
    {
    }

    uint32_t Id() { return ACTION_TYPE_OPEN_GATE; }

    bool DoAction(EagleEvent *_event);
};

//
void PlayerDoAction(LogicPlayer *, uint64_t targetId, const std::vector<ConditionParm> &vecAction);

#endif    


