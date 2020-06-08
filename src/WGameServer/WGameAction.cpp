#include "WGameAction.h"
#include "WGamePlayer.h"
#include "WGameCondition.h"
#include "Buff.h"
#include "Effect.h"
#include "ECS_Quest.h"
#include "WGameDungeon.h"

EagleAction* CreateAction(uint32_t type, void *ptr1, void *ptr2)
{
    EagleAction *temp = NULL;
    switch (type)
    {
    case ACTION_TYPE_NONE:
        return new Test1(ptr1, ptr2);
        break;
	case ACTION_TYPE_QUEST_COMPLETE:
		return new CompleteQuestAction(ptr1, ptr2);
		break;
	case ACTION_TYPE_DUNGEON_COMPLETE:
		return new CompleteDungeonAction(ptr1, ptr2);
		break;
    default:
        break;
    }

    return temp;
}

//CompleteQuestAction
void CompleteQuestAction::UpdateCondition(EagleEvent* _event)
{
	if (IsEnd())
		return;

	if (IsComplete())
		m_end = DoAction(_event);

	return;
}

bool CompleteQuestAction::DoAction(EagleEvent* _event)
{
	QuestSystem::instance()->Complete((ECS::ECSEntity*)m_object, m_quest);

	return true;
}

//CompleteDungeonAction
bool CompleteDungeonAction::DoAction(EagleEvent* _event)
{
	m_dungeon->End();

	return true;
}


