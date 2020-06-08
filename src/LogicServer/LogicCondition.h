#ifndef _LOGIC_CONDITION_H_ 
#define    _LOGIC_CONDITION_H_

#include "StringTool.h"
#include "CObject.h"
#include "SharedEvent.h"
#include "LogicDataManager.h"

class PassDungeonCondition : public EagleCondition
{
protected:
    bool UpdateImp(EagleEvent *);

    uint32_t m_dungeonId;
public:
    PassDungeonCondition(EagleAction *action, const std::vector<double> &param);

    bool operator()();
    uint32_t Id() { return CONDITION_TYPE_DUNGEON; }
};

//class PassDungeonTeamCondition : public EagleCondition
//{
//protected:
//    bool UpdateImp(EagleEvent *);
//
//    uint32_t m_dungeonId;
//public:
//    PassDungeonTeamCondition(EagleAction *action, const std::vector<double> &param);
//
//    bool operator()();
//    uint32_t Id() { return CONDITION_TYPE_DUNGEON_TEAM; }
//};


class KillMonsterMoreCondition : public EagleCondition
{
protected:
    bool UpdateImp(EagleEvent *);

public:
    uint64_t m_monsterId;

public:
    KillMonsterMoreCondition(EagleAction *action, const std::vector<double> &param);

    bool operator()();
    uint32_t Id() { return CONDITION_TYPE_KILL_MONSTER; }
};


class NpcDialogueCondition : public EagleCondition
{
    uint64_t m_questId;
protected:
    bool UpdateImp(EagleEvent *);

public:
    NpcDialogueCondition(EagleAction *action, const std::vector<double> &param);

    bool operator()();
    uint32_t Id() { return CONDITION_TYPE_NPC_DIALOGUE; }
};

class LevelCondition : public EagleCondition
{
protected:
    bool UpdateImp(EagleEvent *);

public:
    LevelCondition(EagleAction *action, const std::vector<double> &param);

    bool operator()();
    uint32_t Id() { return CONDITION_TYPE_LEVEL; }
};

class CommitItemCondition : public EagleCondition
{
    uint64_t m_questId;
protected:
    bool UpdateImp(EagleEvent *);

public:
    CommitItemCondition(EagleAction *action, const std::vector<double> &param);

    bool operator()();
    uint32_t Id() { return CONDITION_TYPE_COMMIT_ITEM; }
};

//class CommitEquipCondition : public EagleCondition
//{
//    uint64_t m_questId;
//protected:
//    bool UpdateImp(EagleEvent *);
//
//public:
//    CommitEquipCondition(EagleAction *action, const std::vector<double> &param);
//
//    bool operator()();
//    uint32_t Id() { return CONDITION_TYPE_COMMIT_Q_EQUIP; }
//};

#endif    


