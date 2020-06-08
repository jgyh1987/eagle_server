#ifndef _WGAME_ACTION_H_ 
#define    _WGAME_ACTION_H_

#include "SharedEvent.h"
#include "CommonType.h"

class Quest;
class CompleteQuestAction : public EagleAction
{
	Quest* m_quest;
public:
	CompleteQuestAction(void* ptr1, void* ptr2)
		:EagleAction(ptr1), m_quest((Quest*)ptr2)
	{
	}

	void UpdateCondition(EagleEvent* _event);
	uint32_t Id() { return ACTION_TYPE_QUEST_COMPLETE; }

	bool DoAction(EagleEvent* _event);
};

class WGameDungeon;
class CompleteDungeonAction : public EagleAction
{
	WGameDungeon* m_dungeon;
public:
	CompleteDungeonAction(void* ptr1, void* ptr2)
		:EagleAction(ptr1), m_dungeon((WGameDungeon*)ptr2)
	{
	}

	uint32_t Id() { return ACTION_TYPE_DUNGEON_COMPLETE; }

	bool DoAction(EagleEvent* _event);
};

//

#endif    


