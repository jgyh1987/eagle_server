#include "LogicCondition.h"
#include "LogicPlayer.h"
#include "LogicEvent.h"
#include "LogicAction.h"
#include "ToolsFun.h"

//
EagleCondition* CreateCondition(EagleAction *action, uint32_t type, const char *param)
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

EagleCondition* CreateCondition(EagleAction *action, uint32_t type, const std::vector<double> &param)
{
    EagleCondition *temp = NULL;
    switch (type)
    {
    case CONDITION_TYPE_NONE:
        return new NoneCondition(action, param);
        break;
    case CONDITION_TYPE_DUNGEON:
        return new PassDungeonCondition(action, param);
        break;
    case CONDITION_TYPE_KILL_MONSTER:
        return new KillMonsterMoreCondition(action, param);
        break;
    case CONDITION_TYPE_NPC_DIALOGUE:
        return new NpcDialogueCondition(action, param);
        break;
    case CONDITION_TYPE_LEVEL:
        return new LevelCondition(action, param);
        break;
    case CONDITION_TYPE_COMMIT_ITEM:
        return new CommitItemCondition(action, param);
        break;
    default:
        break;
    }

    return temp;
}


//PassDungeonCondition
PassDungeonCondition::PassDungeonCondition(EagleAction *action, const std::vector<double> &param)
    :EagleCondition(action)
{
    if (param.size() >= 2)
    {
        m_dungeonId = (uint32_t)param[0];
        m_var = (int64_t)param[1];
    }
}

bool PassDungeonCondition::UpdateImp(EagleEvent *_event)
{
    OnPassDungeonLogicEvent *e = (OnPassDungeonLogicEvent *)_event;
    if (!m_dungeonId || m_dungeonId == e->DungeonId())
        ++m_curVar;

    return true;
}

bool PassDungeonCondition::operator()()
{
    if (m_curVar >= m_var)
        return true;

    return false;
}


////PassDungeonTeamCondition
//PassDungeonTeamCondition::PassDungeonTeamCondition(EagleAction *action, const std::vector<double> &param)
//    :EagleCondition(action)
//{
//    if (param.size() >= 2)
//    {
//        m_dungeonId = (uint32_t)param[0];
//        m_var = (int64_t)param[1];
//    }
//}
//
//bool PassDungeonTeamCondition::UpdateImp(EagleEvent *_event)
//{
//    OnPassDungeonLogicEvent *e = (OnPassDungeonLogicEvent *)_event;
//    if (e->IsTeam())
//        if (!m_dungeonId || m_dungeonId == e->DungeonId())
//            ++m_curVar;
//
//    return true;
//}
//
//bool PassDungeonTeamCondition::operator()()
//{
//    if (m_curVar >= m_var)
//        return true;
//
//    return false;
//}

//KillMonsterMoreCondition
KillMonsterMoreCondition::KillMonsterMoreCondition(EagleAction *action, const std::vector<double> &param)
    :EagleCondition(action)
{
    std::vector< std::string > basetemp;
    if (param.size() >= 2)
    {
        m_monsterId = (uint64_t)param[0];
        m_var = (int64_t)param[1];
    }
}

bool KillMonsterMoreCondition::UpdateImp(EagleEvent *_event)
{
    OnKillLogicEvent *e = (OnKillLogicEvent *)_event;
    if (!m_monsterId || m_monsterId == e->MonsterId())
        ++m_curVar;

    return true;
}

bool KillMonsterMoreCondition::operator()()
{
    if (m_curVar >= m_var)
        return true;

    return false;
}

//NpcDialogueCondition
NpcDialogueCondition::NpcDialogueCondition(EagleAction *action, const std::vector<double> &param)
    :EagleCondition(action)
{
    m_var = 1;
    if (param.size())
        m_questId = (uint64_t)param[param.size() - 1];
}

bool NpcDialogueCondition::UpdateImp(EagleEvent *_event)
{
    OnClientLogicEvent *e = (OnClientLogicEvent *)_event;
    if (e->QuestId() == m_questId)
    {
        m_curVar = 1;
        return true;
    }

    return false;
}

bool NpcDialogueCondition::operator()()
{
    if (m_curVar >= m_var)
        return true;

    return false;
}


//LevelCondition
LevelCondition::LevelCondition(EagleAction *action, const std::vector<double> &param)
    :EagleCondition(action)
{
    m_var = 0;
    if (param.size() >= 1)
    {
        m_var = (int64_t)param[0];
    }

}

bool LevelCondition::UpdateImp(EagleEvent *_event)
{
    //WorldRole *p = (WorldRole *)_event->ExParam();
    //m_curVar = p->RoleLevel();

    return true;
}

bool LevelCondition::operator()()
{
    if (m_curVar >= m_var)
        return true;

    return false;
}

//CommitItemCondition
CommitItemCondition::CommitItemCondition(EagleAction *action, const std::vector<double> &param)
    :EagleCondition(action)
{
    m_var = 1;
    if (param.size())
        m_questId = (uint64_t)param[param.size() - 1];
}

bool CommitItemCondition::UpdateImp(EagleEvent *_event)
{
    OnClientLogicEvent *e = (OnClientLogicEvent *)_event;
    if (e->QuestId() == m_questId)
    {
        m_curVar = 1;
        return true;
    }

    return false;
}

bool CommitItemCondition::operator()()
{
    if (m_curVar >= m_var)
        return true;

    return false;
}

////CommitEquipCondition
//CommitEquipCondition::CommitEquipCondition(EagleAction *action, const std::vector<double> &param)
//    :EagleCondition(action)
//{
//    m_var = 1;
//    if (param.size())
//        m_questId = (uint64_t)param[param.size() - 1];
//}
//
//bool CommitEquipCondition::UpdateImp(EagleEvent *_event)
//{
//    OnClientLogicEvent *e = (OnClientLogicEvent *)_event;
//    if (e->QuestId() == m_questId)
//    {
//        m_curVar = 1;
//        return true;
//    }
//
//    return false;
//}
//
//bool CommitEquipCondition::operator()()
//{
//    if (m_curVar >= m_var)
//        return true;
//
//    return false;
//}

