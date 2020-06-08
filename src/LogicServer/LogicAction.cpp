#include "LogicAction.h"
#include "LogicPlayer.h"
#include "LogicCondition.h"
#include "Buff.h"
#include "Effect.h"

EagleAction* CreateAction(uint32_t type, void *ptr1, void *ptr2)
{
    EagleAction *temp = NULL;
    switch (type)
    {
    case ACTION_TYPE_NONE:
        return new Test1(ptr1, ptr2);
        break;
    case ACTION_TYPE_DUNGEON_COMPLETE:
        return new CompleteDungeonAction(ptr1, ptr2);
        break;
    case ACTION_TYPE_QUEST_COMPLETE:
        return new CompleteQuestAction(ptr1, ptr2);
        break;
    case ACTION_TYPE_OPEN_GATE:
        return new OpenGateAction(ptr1, ptr2);
        break;
    default:
        break;
    }

    return temp;
}

void PlayerDoAction(LogicPlayer *player, uint64_t srcId, const std::vector<ConditionParm> &vecAction)
{
    for (uint32_t i = 0; i < vecAction.size(); ++i)
    {
        switch (vecAction[i].type)
        {
        case ACTION_TYPE_OPEN_GATE:
        {
            uint32_t id = atoi((char *)vecAction[i].value.c_str());
            OpenGateAction action(player, &id);
            action.DoAction(NULL);
        }
        break;
        default:
            break;
        }
    }

    return;
}

//CompleteDungeonAction
bool CompleteDungeonAction::DoAction(EagleEvent *_event)
{

    return true;
}

//CompleteQuestAction
void CompleteQuestAction::UpdateCondition(EagleEvent *_event)
{
    if (IsEnd())
        return;

    if (IsComplete())
        m_end = DoAction(_event);
    //else
    //    ((LogicPlayer*)m_object)->GetWorldRole()->GetQuestManager()->NotifyQuest(m_quest);

    return;
}

bool CompleteQuestAction::DoAction(EagleEvent *_event)
{
    //((LogicPlayer*)m_object)->GetWorldRole()->GetQuestManager()->Complete(m_quest);

    return true;
}


//OpenGateAction
bool OpenGateAction::DoAction(EagleEvent *_event)
{


    return true;
}



