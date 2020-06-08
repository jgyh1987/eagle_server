#include "WGameCondition.h"
#include "WGamePlayer.h"
#include "WGameEvent.h"
#include "WGameAction.h"
#include "ToolsFun.h"
#include "ECS_Quest.h"

//
 EagleCondition* CreateCondition(EagleAction *action, uint32_t type, const char *param)
 {
    EagleCondition *temp = NULL;
    switch (type)
    {
    case CONDITION_TYPE_NONE:
        return new NoneCondition(action, param);
        break;
	case CONDITION_TYPE_CLIENT_CMP_QUEST:
		return new ClientCmpQuestCondition(action, param);
		break;
	case CONDITION_TYPE_KILL_MONSTER:
		return new KillMonsterCondition(action, param);
		break;
    default:
        break;
    }

    return temp;
 }

 EagleCondition* CreateCondition(EagleAction *action, uint32_t type, const std::vector<double> &param)
 {
    EagleCondition *temp = NULL;
    switch (type)
    {
    case CONDITION_TYPE_NONE:
        return new NoneCondition(action, param);
        break;
    default:
        break;
    }

    return temp;
 }

 //ClientCmpQuestCondition
 ClientCmpQuestCondition::ClientCmpQuestCondition(EagleAction* action, const char* param)
	:EagleCondition(action)
 {

	m_questId = std::stoull(param);
	m_var = 1;
 }

 bool ClientCmpQuestCondition::UpdateImp(EagleEvent* _event)
 {
	 auto* e = (OnClientCmpQuestEvent*)_event;
	 if (m_questId && m_questId == e->QuestId())
	 {
		 m_curVar = 1;

		 return true;
	 }

	 return false;
 }

 bool ClientCmpQuestCondition::operator()()
 {
	 if (m_curVar == m_var)
		 return true;

	 return false;
 }

 //KillMonsterCondition
 KillMonsterCondition::KillMonsterCondition(EagleAction* action, const char* param)
	 :EagleCondition(action)
 {
	 std::vector< uint64_t > temp;
	 parseStrToVecInt64(param, temp, '|');
	 if (2 == temp.size())
	 {
		 m_monsterId = temp[1];
		 m_var = temp[0];
	 }
 }

 bool KillMonsterCondition::UpdateImp(EagleEvent* _event)
 {
	 auto* e = (OnKillLogicEvent*)_event;
	 if (m_monsterId && m_monsterId == e->MonsterId())
	 {
		 ++m_curVar;

		 return true;
	 }

	 return false;
 }

 bool KillMonsterCondition::operator()()
 {
	 if (m_curVar >= m_var)
		 return true;

	 return false;
 }


