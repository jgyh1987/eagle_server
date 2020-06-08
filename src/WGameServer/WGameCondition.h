#ifndef _WGAME_CONDITION_H_ 
#define    _WAGME_CONDITION_H_

#include "StringTool.h"
#include "CObject.h"
#include "SharedEvent.h"
#include "LogicDataManager.h"

class ClientCmpQuestCondition : public EagleCondition
{
protected:
	bool UpdateImp(EagleEvent*);

	uint64_t m_questId;
public:
	ClientCmpQuestCondition(EagleAction* action, const char* param);

	bool operator()();
	uint32_t Id() { return CONDITION_TYPE_CLIENT_CMP_QUEST; }
};

class KillMonsterCondition : public EagleCondition
{
protected:
	bool UpdateImp(EagleEvent*);

	uint64_t m_monsterId;
public:
	KillMonsterCondition(EagleAction* action, const char* param);

	bool operator()();
	uint32_t Id() { return CONDITION_TYPE_KILL_MONSTER; }
};

#endif    


